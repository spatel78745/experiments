/*
 * TcpSocket_test.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */
#include <thread>
#include "TcpSocket.h"
#include "TcpSocketTest.h"
#include "MyException.h"

const char *TcpSocketTest::mBadHost = "badhost";
const int TcpSocketTest::mBadPort = 6969;
const char *TcpSocketTest::mGoodHost = "localhost";
const int TcpSocketTest::mGoodPort = 50006;

// TODO: use an anonymous namespace instead of file-static functions
static bool readLine(TcpSocket& ts, string &inLine)
{
    try
    {
        ts.readLine(inLine);
        return true;
    }
    catch(MyException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

static bool writeLine(TcpSocket& ts, const string &outLine)
{
    try
    {
        ts.writeLine(outLine);
        return true;
    }
    catch(MyException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

static bool connect(TcpSocket& ts)
{
    try
    {
        ts.connect();
        return true;
    }
    catch(MyException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

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

    assert("readLine", !readLine(ts, inLine));
    assert("writeLine", !writeLine(ts, outLine));
}

void TcpSocketTest::testIo()
{
    header("testIO");

    TcpSocket ts{mGoodHost, mGoodPort};
    string inLine;

    // Start server

    connect(ts);
    if (!assert("connected", ts.isConnected())) return;
    assert("writeLine w/o newline", !writeLine(ts, "hello"));
    assert("writeLine", writeLine(ts, "hello\n"));
    assert("readLine", readLine(ts, inLine));
    assert(inLine + " echo ok", inLine.compare("Echo=>hello") == 0);
    assert("writeLine stop", writeLine(ts, "stop\n"));
    ts.close();
    assert("readLine after close", !readLine(ts, inLine));
    assert("not connected", !ts.isConnected());

}

void TcpSocketTest::testConnectionLost()
{
    const int delay = 1; // ms
    TcpSocket ts{mGoodHost, mGoodPort};

    if (!assert("connect", connect(ts))) return;
    if (!assert("connected", ts.isConnected())) return;

    /*
     * 1. Start the echo server
     * 2. Send it a character in a loop with a small delay. D
     * 3. Stop the echo server and see what happens
     */
    for(int i = 0; ;++i)
    {
        cerr << "Writing character " << i << endl;
        ts.writeChar('x');
        cerr << "Wrote character " << i << endl;
        std::this_thread::sleep_for(chrono::seconds(1));
    }
}

void TcpSocketTest::runAll()
{
//    testConstructor();
//    testNotConnected();
//    testIo();
    testConnectionLost();

    fprintf(stderr, "Summary: count = %d, pass = %d, fail = %d, score = %.1f %%", count(), pass(),
            fail(), score());
}
