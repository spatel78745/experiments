/*
 * TcpSocket_test.h
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#ifndef TCPSOCKETTEST_H_
#define TCPSOCKETTEST_H_

#include "CppTest.h"

class TcpSocketTest : public CppTest
{
public:
    void testConstructor();

    void testNotConnected();

    void testIo();

    virtual void runAll();

private:
    static const char * mBadHost;
    static const int mBadPort;
    static const char *mGoodHost;
    static const int mGoodPort;
};

#endif /* TCPSOCKETTEST_H_ */
