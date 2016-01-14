/*
 * SequentialSearchSTTest.h
 *
 *  Created on: Jan 1, 2016
 *      Author: spatel78745
 */

#ifndef SEQUENTIALSEARCHSTTEST_H_
#define SEQUENTIALSEARCHSTTEST_H_

#include "CppTest.h"
#include "SequentialSearchST.h"

class SequentialSearchSTTest : public CppTest
{
public:
    typedef string keytype;
    typedef int valtype;
    typedef pair<keytype, valtype> pairT;
    typedef SequentialSearchST<keytype, valtype> StT;

    void test();

    void testIteratorGetPair();

    void testCopyConstructor();

    void testCopyAssignment();

    void testListInit();

    void testListInitConst();

    void testDel();

    void runAll() override;
};

#endif /* SEQUENTIALSEARCHSTTEST_H_ */
