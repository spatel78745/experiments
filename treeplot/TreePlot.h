/*
 * TreePlot.h
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOT_H_
#define TREEPLOT_H_

#include <string>
using namespace std;


// TODO: make this a singleton and use a factory maybe
class TreePlot
{
public:
    TreePlot() noexcept {};

    virtual ~TreePlot() noexcept {}

    virtual void drawNode(int row, int col, const string& key) const;

    virtual void drawLeftLeg(int row1, int col1, int row2, int col2) const;

    virtual void drawRightLeg(int row1, int col1, int row2, int col2) const;

    virtual int rows() const { return 200; }

    virtual int cols() const { return 200; }
};

#endif /* TREEPLOT_H_ */
