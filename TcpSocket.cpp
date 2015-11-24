/*
 * TcpSocket.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: spatel78745
 */

#include <string>
#include <cstdio>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include "TcpSocket.h"

static void *getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

TcpSocket::TcpSocket(const string& hostname, int port) :
    mHostname(hostname), mPort(port), mSockFd(-1)
{
}

bool TcpSocket::connect()
{
    char s[INET6_ADDRSTRLEN];  // dotted-quad IP address
    int rv;

    /*
     * Get a list of struct addrinfo for (mHostname, mPort). This'll give us the
     * (ai_family, ai_socktype, ai_protocol) that we pass to socket() and the (ai_addr, ai_addrlen)
     * that we pass to connect()
     */
    struct addrinfo hints;     // parameter to getaddrinfo()
    struct addrinfo *servInfo; // linked-list returned by getaddrinfo
    struct addrinfo  *p;       // the struct addrinfo that we're connected to

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(mHostname.c_str(), to_string(mPort).c_str(), &hints, &servInfo)) != 0)
    {
        throw runtime_error(string(gai_strerror(rv)));
    }

    /*
     * Loop through the addrinfo-list and connect to the first one we can
     */
    for(p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((mSockFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("Error socket: ");
            continue;
        }

        if (::connect(mSockFd, p->ai_addr, p->ai_addrlen))
        {
            perror("Error connect: ");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        mSockFd = -1;
        return false;
    }

    inet_ntop(p->ai_family, getInAddr((struct sockaddr *)p->ai_addr), s, sizeof(s));
    cout << "connected to: " << s << endl;

    freeaddrinfo(servInfo);

    return true;
}

bool TcpSocket::readLine(string& line)
{
    int c;

    if (mSockFd == -1)
    {
        cerr << "Error: socket not connected\n";
        return false;
    }

    line.clear();
    while((c = getChar() > 0) && (c != '\n'))
        line.push_back(string::traits_type::to_int_type(c));

    return c == '\n';
}

bool TcpSocket::writeLine(const string& line)
{
    // Error if the socket isn't connected
    if (mSockFd == -1)
    {
        cerr << "Error: socket not connected\n";
        return false;
    }

    // Error if last character is not a null terminator
    if (*line.rbegin() != '\n')
    {
        cerr << "Error: last character must be a newline\n";
        return false;
    }

    if (send(mSockFd, line.c_str(), line.size(), 0) == -1)
    {
        perror("Error: send");
        return false;
    }

    return true;
}

TcpSocket::~TcpSocket() { close(); }

void TcpSocket::close()
{
    if (mSockFd == -1) return;
    ::close(mSockFd);
    mSockFd = -1;
}

/*
 * Reads a character from the socket descriptor
 * Returns:
 * - 0  if the socket is closed
 * - -1 if error
 * - a character if successful
 */
int TcpSocket::getChar()
{
    char c;
    ssize_t n;

    n = recv(mSockFd, &c, 1, 0);

    if (n == -1)
    {
        perror("Error recv:");
        return -1;
    }

    if (n < 0)
    {
        cerr << "Connection closed\n";
        return 0;
    }

    return string::traits_type::to_int_type(c);
}

