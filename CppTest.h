/*
 * TestUtil.h
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#ifndef CPPTEST_H_
#define CPPTEST_H_

#include <string>
#include <iostream>

using namespace std;

class CppTest
{
public:
    bool assert(const char *test, bool result);

    bool assert(std::string test, bool result);

    int count() { return mCount; }

    int pass()  { return mPass; }

    int fail()  { return mFail; }

    bool ask(const string& prompt, char expected='y') const noexcept;

    double score()
    {
        return mCount > 0 ? static_cast<double>(mPass) / mCount * 10 / 10 * 100 : 0; }

    static void header(std::string s);

    virtual void runAll();

    virtual ~CppTest() {};

private:
    int mCount = 0;
    int mPass  = 0;
    int mFail  = 0;
};

#endif /* CPPTEST_H_ */
