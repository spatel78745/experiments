/*
 * TreePlotImplGserv.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include <treeplot/TreePlotImplGserv.h>
#include <cstdio>
#include <string>

using namespace std;

void TreePlotImplGserv::drawNode(int row, int col, const string& key) const
{
    fprintf(stderr, "drawNode(%d, %d, %s)\n", row, col, key.c_str());
}

void TreePlotImplGserv::drawLeftLeg(int row, int col)
{
    fprintf(stderr, "drawLeftLeg(%d, %d)\n", row, col);
}

void TreePlotImplGserv::drawRightLeg(int row, int col)
{
    fprintf(stderr, "drawRightLeg(%d, %d)\n", row, col);
}

int TreePlotImplGserv::rows() { return 800; }

int TreePlotImplGserv::cols() { return 800; }

TreePlotImplGserv::~TreePlotImplGserv() {}
