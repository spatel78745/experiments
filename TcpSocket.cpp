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
#include "MyException.h"


// TODO: don't use static, use an anonymous namespace
static void *getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

TcpSocket::TcpSocket(const string& hostname, int port) noexcept :
    mHostname(hostname), mPort(port), mSockFd(-1)
{
}

void TcpSocket::connect()
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
        cerr << "getaddrinfo failed: " << strerror(rv);
        throw MyException("Error: Failed to connect");
    }

    /*
     * Loop through the addrinfo-list and connect to the first one we can
     */
    for(p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((mSockFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("socket");
            continue;
        }

        if (::connect(mSockFd, p->ai_addr, p->ai_addrlen))
        {
            perror("connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        mSockFd = -1;
        throw MyException("Error: Failed to connect");
    }

    inet_ntop(p->ai_family, getInAddr((struct sockaddr *)p->ai_addr), s, sizeof(s));
    cout << "connected to: " << s << endl;

    freeaddrinfo(servInfo);
}

void TcpSocket::readLine(string& line)
{
    int c;

    if (mSockFd == -1)
        throw MyException("Error: read failed because socket not connected");

    line.clear();
    while((c = getChar()) != 0 && c != '\n')
        line.push_back(string::traits_type::to_char_type(c));
}

void TcpSocket::writeLine(const string& line) const
{
    // Error if the socket isn't connected
    if (mSockFd == -1)
        throw MyException("Error: write failed because socket not connected");

    // Error if last character is not a null terminator
    if (*line.rbegin() != '\n')
        throw MyException("Error: last character must be a newline");

    if (send(mSockFd, line.c_str(), line.size(), 0) == -1)
    {
        perror("send");
        throw MyException("Error: send failed");
    }
}

void TcpSocket::writeChar(char c) const
{
    // Error if the socket isn't connected
    if (mSockFd == -1)
        throw MyException("Error: write failed because socket not connected");

    if (send(mSockFd, &c, 1, 0) == -1)
    {
        perror("send");
        throw MyException("Error: send failed");
    }
}


void TcpSocket::close() noexcept
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
//    fprintf(stderr, "(n = %ld, c = %c, c = %d, nl = %d)\n", n, c, string::traits_type::to_int_type(c), '\n');

    if (n == -1)
    {
        perror("recv");
        throw MyException("Error: recv failed");
    }

    if (n == 0)
    {
        cerr << "Warning: Connection closed\n";
        close();
        return 0;
    }

    return string::traits_type::to_int_type(c);
}

TcpSocket::~TcpSocket() noexcept
{
    cerr << "Closing socket" << endl;
    close();
}
