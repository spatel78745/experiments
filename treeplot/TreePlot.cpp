/*
 * TreePlot.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: spatel78745
 */

#include "TreePlot.h"
#include "MyException.h"

TreePlot::TreePlot()
{
}

void TreePlot::drawNode(int row, int col, const string& key) const
{
    fprintf(stderr, "drawNode(%d, %d, %s)\n", row, col, key.c_str());
}

void TreePlot::drawLeftLeg(int row, int col)
{
    fprintf(stderr, "drawLeftLeg(%d, %d)\n", row, col);
}

void TreePlot::drawRightLeg(int row, int col)
{
    fprintf(stderr, "drawRightLeg(%d, %d)\n", row, col);
}
