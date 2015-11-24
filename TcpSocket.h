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
    /*
     * Creates a TCP socket
     * - hostname: The hostname of the server
     * - port    : The server port
     */
    TcpSocket(const string& hostname, int port);

    /*
     * Connects this socket
     *
     * Returns true if successful, false if failed.
     */
    bool connect();

    /*
     * Reads a line from the socket
     * - &line (out): The line. Doesn't contain the delimiting '\n'.
     *
     * Precond: Socket must be connected
     *
     * Returns true if successful, false if failed
     */
    bool readLine(string& line);

    /*
     * Writes a line to the socket
     *
     * Precond: Socket must be connected
     *
     * - &line(in): The line. Must end in '\n'.
     */
    bool writeLine(const string& line);

    /*
     * Closes (and disconnects) the socket
     */
    void close();

    /*
     * Returns the hostname
     */
    string hostname() { return mHostname; }

    /*
     * Returns the port
     */
    int port() { return mPort; }

    /*
     * Returns true if connected
     */
    bool isConnected() { return mSockFd != -1; }

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
