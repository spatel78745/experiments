/*
 * TreePlotImplConsole.h
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOTIMPLCONSOLE_H_
#define TREEPLOTIMPLCONSOLE_H_

#include <cstdio>
#include <string>
#include "TreePlotImpl.h"

using namespace std;

class TreePlotImplConsole : public TreePlotImpl
{
public:
    void drawNode(int row, int col, const string& key) const override
    {
        fprintf(stderr, "drawNode(%d, %d, %s)\n", row, col, key.c_str());
    }

    void drawLeftLeg(int row, int col) override
    {
        fprintf(stderr, "drawLeftLeg(%d, %d)\n", row, col);
    }

    void drawRightLeg(int row, int col) override
    {
        fprintf(stderr, "drawRightLeg(%d, %d)\n", row, col);
    }

    virtual int rows() override { return 800; }

    virtual int cols() override { return 800; }

    virtual ~TreePlotImplConsole() override {}

private:
    /*
     * Disable copy and copy-assignment
     */
//    TreePlotImplConsole(const TreePlotImpl &) {}
//    TreePlotImplConsole& operator=(const TreePlotImpl &)
};

#endif /* TREEPLOTIMPLCONSOLE_H_ */
