/*
 * TcpSocket.h
 *
 *  Created on: Nov 23, 2015
 *      Author: spatel78745
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <string>

using namespace std;

class TcpSocket
{
public:
    TcpSocket(const string& hostname, int port);

    bool connect();

    bool readLine(string& line);

    bool writeLine(const string& line);

    void close();

    virtual ~TcpSocket();

private:
    int getChar();
    /*
     * Forbid assignment and copying
     */
    TcpSocket(const TcpSocket &);
    TcpSocket& operator=(const TcpSocket &);

private:
    const string mHostname;
    const int mPort;
    // -1 if socket isn't connected
    int mSockFd;
};

#endif /* TCPSOCKET_H_ */
