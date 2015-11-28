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

TreePlot::TreePlot() noexcept
{
    try
    {
        mImplPref = TreePlotImplGserv::instance();
    }
    catch(MyException& me)
    {
        cerr << me.what();
    }
}

void TreePlot::drawNode(int row, int col, const string& key) const noexcept
{
}

void TreePlot::drawLeftLeg(int row, int col) const noexcept
{
}

void TreePlot::drawRightLeg(int row, int col) const noexcept
{
}

int TreePlot:: rows() const noexcept
{
    return 0;
}

int TreePlot:: cols() const noexcept
{
    return 0;
}
