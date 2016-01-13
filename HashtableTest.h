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
    typedef Hashtable<keytype, valtype> Ht;

    void test();

    void testIterator();

    void testCopyConstructor();

    void testCopyAssignment();

    void testListInit();

    void testListInitConst();

    void runAll() override;
};

#endif /* HASHTABLETEST_H_ */
