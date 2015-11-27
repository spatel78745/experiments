/*
 * TestTreePlotImpl.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include <treeplot/TestTreePlot.h>

void TestTreePlot::testCopy()
{
    /*
     * Pass: This line doesn't compile because TreePlotImpl is an abstract class
     */
//    TreePlotImpl tpi;

    /*
     * Pass: Doesn't compile because the superclass copy constructor is private. Compiler says
     * "call to implicitly-deleted copy constructor of 'TreePlotImplConsole'
     */
//    TreePlotImplConsole tpic1;
//    TreePlotImplConsole tpic2(tpic1);

    /*
     * Pass: Doesn't compile because the superclass copy constructor is private. Compiler says
     * "call to implicitly-deleted copy assignment operator of 'TreePlotImplConsole'
     */
//    TreePlotImplConsole tpic1;
//    TreePlotImplConsole tpic2;
//    tpic2 = tpic1;
}

void TestTreePlot::runAll()
{

}
