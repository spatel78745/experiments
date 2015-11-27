/*
 * TreePlotImplGserv.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include <cstdio>
#include <string>
#include "treeplot/TreePlotImplGserv.h"
#include "MyException.h"

using namespace std;

TreePlotImplGserv::TreePlotImplGserv()
{
    throw MyException("Failed to open TCP connection");
}

void TreePlotImplGserv::drawNode(int row, int col, const string& key) const
{
    fprintf(stderr, "drawNode(%d, %d, %s)\n", row, col, key.c_str());
}

void TreePlotImplGserv::drawLeftLeg(int row, int col) const
{
    fprintf(stderr, "drawLeftLeg(%d, %d)\n", row, col);
}

void TreePlotImplGserv::drawRightLeg(int row, int col) const
{
    fprintf(stderr, "drawRightLeg(%d, %d)\n", row, col);
}

int TreePlotImplGserv::rows() const { return 800; }

int TreePlotImplGserv::cols() const { return 800; }

TreePlotImplGserv::~TreePlotImplGserv() {}
