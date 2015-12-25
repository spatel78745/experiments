/*
 * TreePlotImplGserv.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include <treeplot/Gserv.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include "MyException.h"

using namespace std;

// TODO: Use an anonymous namespace instead of a static function

Gserv::Gserv(const char *host, int port): mTcpSocket(nullptr), mHost(host), mPort(port)
{
    mTcpSocket = new TcpSocket(mHost, mPort);
    mTcpSocket->connect();
}

void Gserv::drawNode(int row, int col, const string& key) const
{
    stringstream ss;
    string resp;

    TreePlot::drawNode(row, col, key);
    ss << "drawNode " << row << " " << col << " " << key << endl;
    sendCommand(ss.str());
}

void Gserv::drawLeftLeg(int row1, int col1, int row2, int col2) const
{
    stringstream ss;
    string resp;

    TreePlot::drawLeftLeg(row1, col1, row2, col2);
    ss << "drawLeftLeg " << row1 << " " << col1 << " " << row2 << " " << col2 << endl;
    sendCommand(ss.str());
}

void Gserv::drawRightLeg(int row1, int col1, int row2, int col2) const
{
    stringstream ss;
    string resp;

    TreePlot::drawRightLeg(row1, col1, row2, col2);
    ss << "drawRightLeg " << row1 << " " << col1 << " " << row2 << " " << col2 << endl;
    sendCommand(ss.str());
}

int Gserv::rows() const
{
    return 800;
}

int Gserv::cols() const
{
    return 800;
}

Gserv::~Gserv()
{
    cerr << "TreePlotImplGserv: destroying socket" << endl;
    delete mTcpSocket;
}

void Gserv::sendCommand(string cmd) const
{
    string resp;
    mTcpSocket->writeLine(cmd);

    mTcpSocket->readLine(resp);
    if (resp.compare("err") == 0)
    {
        cerr << "Error: command (" << cmd << ")" << "failed" << endl;
        throw MyException("Error: gserv exception");
    }
}
