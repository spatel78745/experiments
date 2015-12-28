/*
 * TestUtil.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#include "CppTest.h"

#include <string>
#include <iostream>

// TODO: Is doing this bad? Seems better then a long list of using std:: etc.
using namespace std;

namespace
{
    ostream& os = cout;
}

void CppTest::header(string s)
{
    static string border("============");
    os << border << " " << s << " " << border << endl;
}

bool CppTest::assert(const char *test, bool result)
{
    const char *pass_fail;
    if (result)
    {
        pass_fail = "pass";
        mPass++;
    }
    else
    {
        pass_fail = "fail";
        mFail++;
    }

    mCount++;

    os << "(test) " << test << ": " << pass_fail << endl;

    return result;
}

bool CppTest::assert(std::string test, bool result)
{
    return assert(test.c_str(), result);
}

bool CppTest::ask(const string& prompt, char expected) const noexcept
{
    char c;

    os << prompt << endl;
    c = cin.get();

    return tolower(c) == expected;
}


void CppTest::runAll()
{
    fprintf(stderr, "Summary: count = %d, pass = %d, fail = %d, score = %.1f %%", count(), pass(),
            fail(), score());
}
