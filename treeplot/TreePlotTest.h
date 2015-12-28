/*
 * TreePlotTest.h
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#ifndef TREEPLOTTEST_H_
#define TREEPLOTTEST_H_

#include "CppTest.h"

class TreePlotTest: public CppTest
{
public:

    /*
     * Draws a 3-node tree and asks the user if it looks OK
     */
    void testPlot();

    void runAll() override;
};

#endif /* TREEPLOTTEST_H_ */
