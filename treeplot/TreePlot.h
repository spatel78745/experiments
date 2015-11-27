/*
 * TreePlot.h
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOT_H_
#define TREEPLOT_H_

#include "treeplot/TreePlotImplConsole.h"
#include "treeplot/TreePlotImplGserv.h"

class TreePlot
{
public:
    TreePlot();

    virtual ~TreePlot() {}

    void drawNode(int row, int col, const string& key) const;

    void drawLeftLeg(int row, int col) const;

    void drawRightLeg(int row, int col) const;

    int rows() const;

    int cols() const;

private:
    TreePlotImpl *mImplPref;
    TreePlotImpl *mImplNoThrow;
};



#endif /* TREEPLOT_H_ */
