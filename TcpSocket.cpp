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
    mHostname(hostname), mPort(port)
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
        throw runtime_error(string(gai_strerror(rv)));
    }

    /*
     * Loop through the addrinfo-list and connect to the first one we can
     */
    int sockfd; // returned by socket()
    for(p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("socket: ");
            continue;
        }

        if (::connect(sockfd, p->ai_addr, p->ai_addrlen))
        {
            perror("connect: ");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        cerr << "failed to connect\n";
    }

    inet_ntop(p->ai_family, getInAddr((struct sockaddr *)p->ai_addr), s, sizeof(s));
}

void TcpSocket::readLine(const string& buf)
{

}

void TcpSocket::writeLine(const string& buf)
{

}

TcpSocket::~TcpSocket()
{

}
