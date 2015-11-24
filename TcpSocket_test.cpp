/*
 * TcpSocket_test.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#include "TcpSocket.h"
#include "TestUtil.h"

static void testConstructor()
{
    TcpSocket ts("badhost", 50000);

    pf("host ok", ts.hostname() == "badhost");
    pf("port ok", ts.port() == 50000);
    pf("not connected", !ts.isConnected());
}

void runTcpTests()
{
    testConstructor();
}
