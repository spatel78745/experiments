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

TreePlot::TreePlot()
{
    try
    {
        mImplPref = new TreePlotImplGserv();
    }
    catch(MyException& me)
    {
        cerr << me.what();
    }
}

void TreePlot::drawNode(int row, int col, const string& key) const
{
}

void TreePlot::drawLeftLeg(int row, int col) const
{
}

void TreePlot::drawRightLeg(int row, int col) const
{
}

int TreePlot:: rows() const
{
    return 0;
}

int TreePlot:: cols() const
{
    return 0;
}
