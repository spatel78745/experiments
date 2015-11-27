/*
 * TreePlotImplGserv.h
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOTIMPLGSERV_H_
#define TREEPLOTIMPLGSERV_H_

#include <string>

using namespace std;

class TreePlotImplGserv
{
    virtual void drawNode(int row, int col, const string& key) const;

    virtual void drawLeftLeg(int row, int col);

    virtual void drawRightLeg(int row, int col);

    virtual int rows();

    virtual int cols();

    virtual ~TreePlotImplGserv() = 0;
};

#endif /* TREEPLOTIMPLGSERV_H_ */
