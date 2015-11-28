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
    TreePlot() noexcept;

    virtual ~TreePlot() noexcept {}

    void drawNode(int row, int col, const string& key) const noexcept;

    void drawLeftLeg(int row, int col) const noexcept;

    void drawRightLeg(int row, int col) const noexcept;

    int rows() const noexcept;

    int cols() const noexcept;

private:
    TreePlotImpl *mImplPref;
    TreePlotImpl *mImplNoThrow;
};



#endif /* TREEPLOT_H_ */
