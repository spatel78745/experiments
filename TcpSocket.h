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
    TcpSocket(const string& hostname, int port);

    void connect();

    void readLine(const string& buf);

    void writeLine(const string& buf);

    void close();

    virtual ~TcpSocket();

private:
    const string mHostname;
    const int mPort;
};

#endif /* TCPSOCKET_H_ */
