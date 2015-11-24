/*
 * TcpSocket_test.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#include "TcpSocket.h"
#include "TestUtil.h"

static const char *sBadHost = "badhost";
static const int sBadPort = 6969;
static const char *sGoodHost = "localhost";
static const int sGoodPort = 50006;


static void testConstructor()
{
    header("testConstructor");

    TcpSocket ts(sBadHost, sBadPort);

    pf("host ok", ts.hostname() == "badhost");
    pf("port ok", ts.port() == 50000);
    pf("not connected", !ts.isConnected());
}

static void testNotConnected()
{
    header("testNotConnected");

    TcpSocket ts = { "badhost", 50000 };
    const string outLine("all contaminated things and events are unsatisfactory");
    string inLine;


    pf("readLine", !ts.readLine(inLine));
    pf("writeLine", !ts.writeLine(outLine));
}

static void testIO()
{
    header("testIO");

    TcpSocket ts{sGoodHost, sGoodPort};
    string inLine;

    // Start server

    ts.connect();
    pf("connected", ts.isConnected());
    pf("writeLine w/o newline", !ts.writeLine("hello"));
    pf("writeLine", ts.writeLine("hello\n"));
    pf("readLine", ts.readLine(inLine));
    pf(inLine + " echo ok", inLine.compare("Echo=>hello") == 0);
    pf("writeLine stop", ts.writeLine("stop\n"));
    ts.close();
    pf("not connected", !ts.isConnected());

}

void runTcpTests()
{
//    testConstructor();
//    testNotConnected();
    testIO();
}
