/*
 * TcpSocket_test.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#include "TcpSocket.h"
#include "TcpSocketTest.h"

const char *TcpSocketTest::mBadHost = "badhost";
const int TcpSocketTest::mBadPort = 6969;
const char *TcpSocketTest::mGoodHost = "localhost";
const int TcpSocketTest::mGoodPort = 50006;



void TcpSocketTest::testConstructor()
{
    header("testConstructor");

    TcpSocket ts(mBadHost, mBadPort);

    assert("host ok", ts.hostname().compare("badhost") == 0);
    assert("port ok", ts.port() == mBadPort);
    assert("not connected", !ts.isConnected());
}

void TcpSocketTest::testNotConnected()
{
    header("testNotConnected");

    TcpSocket ts = { "badhost", 50000 };
    const string outLine("all contaminated things and events are unsatisfactory");
    string inLine;


    assert("readLine", !ts.readLine(inLine));
    assert("writeLine", !ts.writeLine(outLine));
}

void TcpSocketTest::testIo()
{
    header("testIO");

    TcpSocket ts{mGoodHost, mGoodPort};
    string inLine;

    // Start server

    ts.connect();
    assert("connected", ts.isConnected());
    assert("writeLine w/o newline", !ts.writeLine("hello"));
    assert("writeLine", ts.writeLine("hello\n"));
    assert("readLine", ts.readLine(inLine));
    assert(inLine + " echo ok", inLine.compare("Echo=>hello") == 0);
    assert("writeLine stop", ts.writeLine("stop\n"));
    assert("readLine after close", !ts.readLine(inLine));
    ts.close();
    assert("not connected", !ts.isConnected());

}

void TcpSocketTest::runAll()
{
    testConstructor();
    testNotConnected();
    testIo();

    fprintf(stderr, "Summary: count = %d, pass = %d, fail = %d, score = %.1f %%", count(), pass(),
            fail(), score());
}
