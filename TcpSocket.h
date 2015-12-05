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
    TcpSocket(const string& hostname, int port) noexcept;

    /*
     * Connects this socket
     *
     * Returns true if successful, false if failed.
     */
    void connect();

    /*
     * Reads a line from the socket
     * - (out) &line : The line. Doesn't contain the delimiting '\n'.
     *
     * Precond: Socket must be connected
     *
     * Returns true if successful, false if failed
     */
    void readLine(string& line);

    /*
     * Writes a line to the socket
     *
     * Precond: Socket must be connected
     *
     * - (in) &line: The line. Must end in '\n'.
     */
    void writeLine(const string& line) const;

    /*
     * Writes a character to the socket
     *
     * Precond: Socket must be connected
     *
     * - (in) c : The character to write
     */
    void writeChar(char c) const;


    /*
     * Closes (and disconnects) the socket
     */
    void close() noexcept;

    /*
     * Returns the hostname
     */
    string hostname() const noexcept { return mHostname; }

    /*
     * Returns the port
     */
    int port() const noexcept { return mPort; }

    /*
     * Returns true if connected
     */
    bool isConnected() const noexcept { return mSockFd != -1; }

    virtual ~TcpSocket() noexcept;

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
