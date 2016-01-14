/*
 * HashtableTest.h
 *
 *  Created on: Jan 1, 2016
 *      Author: spatel78745
 */

#ifndef HASHTABLETEST_H_
#define HASHTABLETEST_H_

#include "CppTest.h"
#include "Hashtable.h"

class HashtableTest : public CppTest
{
public:
    typedef string keytype;
    typedef int valtype;
    // TODO: this should be HtT
    typedef Hashtable<keytype, valtype> Ht;
    typedef pair<keytype, valtype> pairT;

    void test();

    void testIterator();

    void testCopyConstructor();

    void testCopyAssignment();

    void testListInit();

    void testListInitConst();

    void testOutputStream();

    void testDel();

    void runAll() override;
};

#endif /* HASHTABLETEST_H_ */
