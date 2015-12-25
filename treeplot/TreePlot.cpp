/*
 * TreePlot.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: spatel78745
 */

#include <iostream>
#include "TreePlot.h"
#include "MyException.h"

using namespace std;

void TreePlot::drawNode(int row, int col, const string& key) const
{
    cerr << "drawNode " << row << " " << col << " " << key << endl;
}

void TreePlot::drawLeftLeg(int row1, int col1, int row2, int col2) const
{
    cerr << "drawLeftLeg " << row1 << " " << col1 << " " << row2 << " " << col2 << endl;
}

void TreePlot::drawRightLeg(int row1, int col1, int row2, int col2) const
{
    cerr << "drawRightLeg " << row1 << " " << col1 << " " << row2 << " " << col2 << endl;
}
