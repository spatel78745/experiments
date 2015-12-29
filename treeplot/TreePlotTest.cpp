/*
 * TreePlotTest.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include "treeplot/Gserv.h"
#include "treeplot/TreePlotTest.h"
#include <iostream>
#include <MyException.h>

using namespace std;

//void TreePlotTest::testCopy()
//{
//    /*
//     * Pass: This line doesn't compile because TreePlotImpl is an abstract class
//     */
////    TreePlotImpl tpi;
//
//    /*
//     * Pass: Doesn't compile because the superclass copy constructor is private. Compiler says
//     * "call to implicitly-deleted copy constructor of 'TreePlotImplConsole'
//     */
////    TreePlotImplConsole tpic1;
////    TreePlotImplConsole tpic2(tpic1);
//
//    /*
//     * Pass: Doesn't compile because the superclass copy constructor is private. Compiler says
//     * "call to implicitly-deleted copy assignment operator of 'TreePlotImplConsole'
//     */
////    TreePlotImplConsole tpic1;
////    TreePlotImplConsole tpic2;
////    tpic2 = tpic1;
//}
//
//typedef TreePlotImplGserv Gserv;
//
//Gserv *instance()
//{
//    try
//    {
//        Gserv *gs = Gserv::instance();
//        return gs;
//    }
//    catch(MyException& me)
//    {
//        cerr << me.what() << endl;
//        return nullptr;
//    }
//}
//
//bool drawNode(Gserv *gs, int row, int col, const string& key)
//{
//    try
//    {
//        gs->drawNode(row, col, key);
//        return true;
//    }
//    catch(MyException& me)
//    {
//        cerr << me.what() << endl;
//        return false;
//    }
//}
//
//void TreePlotTest::testGservConnectionLost()
//{
//    unique_ptr<Gserv> gs(instance());
//    char input;
//
//    if (!assert("get instance", gs != nullptr))
//    {
//        return;
//    }
//
//    cerr << "Kill gserv and hit <return>" << endl;
//    cin >> input;
//}
//
//
//void TreePlotTest::testGservImpl()
//{
//    unique_ptr<Gserv> gs(instance());
//
//    assert("get instance", gs != nullptr);
//    assert("draw node", drawNode(gs.get(), 1, 10, "A"));
//}
//

void TreePlotTest::testPlot()
{
    const string& testName = "testPlot";

    header(testName);

    ask("Start gserv and press <Enter>");

    try
    {
        Gserv gs;
        int cols = gs.cols();
        int row = 0;

        // Root
        cout << "canvas: (" << cols << ", " << gs.rows() << ")" << endl;
        gs.drawNode(row, cols/2, "B");
        // Left child
        gs.drawNode(row + 1, cols/2 - 1, "A");
        // Right child´
        gs.drawNode(row + 1, cols/2 + 1, "C");
        // Legs
        gs.drawLeftLeg(row, cols/2, row + 1, cols/2 - 1);
        gs.drawRightLeg(row, cols/2, row + 1, cols/2 + 1);

        if (!ask("Do you see a tree corresponding to insert sequence b a c? (y/n)"))
            throw MyException("Error: Bad plot");

        assert(testName, true);
    }
    catch(MyException& e)
    {
        cerr << e.what() << endl;
        assert(testName, false);
    }
}

void TreePlotTest::runAll()
{
    testPlot();
    CppTest::runAll();
}
