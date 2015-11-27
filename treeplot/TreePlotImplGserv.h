/*
 * TreePlotImplGserv.h
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOTIMPLGSERV_H_
#define TREEPLOTIMPLGSERV_H_

#include <string>
#include "TreePlotImpl.h"

using namespace std;

class TreePlotImplGserv : public TreePlotImpl
{
public:
    TreePlotImplGserv();

    virtual void drawNode(int row, int col, const string& key) const override;

    virtual void drawLeftLeg(int row, int col) const override;

    virtual void drawRightLeg(int row, int col) const override;

    virtual int rows() const override;

    virtual int cols() const override;

    virtual ~TreePlotImplGserv();
};

#endif /* TREEPLOTIMPLGSERV_H_ */
