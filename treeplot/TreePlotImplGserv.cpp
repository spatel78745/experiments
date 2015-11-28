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

    ss << "drawNode " << row << " " << col << key;
    mTcpSocket->writeLine(ss.str());

    mTcpSocket->readLine(resp);
    if (resp.compare("err") == 0)
        throw new MyException("Error: gserv failure");
}

void TreePlotImplGserv::drawLeftLeg(int row, int col) const
{
}

void TreePlotImplGserv::drawRightLeg(int row, int col) const
{
    fprintf(stderr, "drawRightLeg(%d, %d)\n", row, col);
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
