/*
 * TreePlotImplGserv.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include "treeplot/TreePlotImplGserv.h"
#include "MyException.h"

using namespace std;

const char * TreePlotImplGserv::mHostname = "localhost";
const int TreePlotImplGserv::mPort = 50006;
TreePlotImplGserv *TreePlotImplGserv::mInstance = nullptr;

void TreePlotImplGserv::sendCommand(string cmd) const
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

TreePlotImplGserv *TreePlotImplGserv::instance()
{
    if (mInstance == nullptr)
    {
        mInstance = new TreePlotImplGserv();
    }

    return mInstance;
}

TreePlotImplGserv::TreePlotImplGserv()
{
    mTcpSocket = new TcpSocket(mHostname, mPort);
    mTcpSocket->connect();
}

void TreePlotImplGserv::drawNode(int row, int col, const string& key) const
{
    stringstream ss;
    string resp;

    ss << "drawNode " << row << " " << col << " " << key << endl;
    sendCommand(ss.str());
}

void TreePlotImplGserv::drawLeftLeg(int row, int col) const
{
}

void TreePlotImplGserv::drawRightLeg(int row, int col) const
{
}

int TreePlotImplGserv::rows() const
{
    return 800;
}

int TreePlotImplGserv::cols() const
{
    return 800;
}

TreePlotImplGserv::~TreePlotImplGserv()
{
    cerr << "TreePlotImplGserv: destroying socket" << endl;
    delete mTcpSocket;
}
