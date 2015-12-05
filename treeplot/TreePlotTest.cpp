/*
 * TreePlotTest.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: spatel78745
 */

#include <iostream>
#include "MyException.h"
#include "treeplot/TreePlotTest.h"
#include "treeplot/TreePlotImplGserv.h"

using namespace std;

void TreePlotTest::testCopy()
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

typedef TreePlotImplGserv Gserv;

Gserv *instance()
{
    try
    {
        Gserv *gs = Gserv::instance();
        return gs;
    }
    catch(MyException& me)
    {
        cerr << me.what() << endl;
        return nullptr;
    }
}

bool drawNode(Gserv *gs, int row, int col, const string& key)
{
    try
    {
        gs->drawNode(row, col, key);
        return true;
    }
    catch(MyException& me)
    {
        cerr << me.what() << endl;
        return false;
    }
}

void TreePlotTest::testGservConnectionLost()
{
    unique_ptr<Gserv> gs(instance());
    char input;

    if (!assert("get instance", gs != nullptr))
    {
        return;
    }

    cerr << "Kill gserv and hit <return>" << endl;
    cin >> input;
}


void TreePlotTest::testGservImpl()
{
    unique_ptr<Gserv> gs(instance());

    assert("get instance", gs != nullptr);
    assert("draw node", drawNode(gs.get(), 1, 10, "A"));
}

void TreePlotTest::runAll()
{
    testGservImpl();
    CppTest::runAll();
}
