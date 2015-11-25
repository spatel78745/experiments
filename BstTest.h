/*
 * BstTest.h
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#ifndef BSTTEST_H_
#define BSTTEST_H_

#include "CppTest.h"

class BstTest : public CppTest
{
public:
    void testPut();

    void testIsNull();

    void testOpEqual();

    void testOpIndex();

    void testInitializerListConst();

    void testKeys();

    void testFloor();

    void testInOrder();

    void testIterator();

    void testIsTree();

    void testDeleteMin();

    void testNoConstIndex() {}

    void testDraw();

    void runAll() override;
};

#endif /* BSTTEST_H_ */
