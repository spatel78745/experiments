/*
 * TestUtil.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: spatel78745
 */

#include <string>
#include <iostream>
#include "TestUtil.h"

// TODO: Is doing this bad? Seems better then a long list of using std:: etc.
using namespace std;

void header(string s)
{
    static string border("============");
    cerr << border << " " << s << " " << border << endl;
}

bool pf(string test, bool result)
{
    string pass_fail(result ? "pass" : "fail");
    cerr << test << ": " << pass_fail << endl;

    return result;
}
