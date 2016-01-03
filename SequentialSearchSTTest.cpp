/*
 * SequentialSearchSTTest.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: spatel78745
 */

#include <iostream>
#include <vector>
#include "SequentialSearchSTTest.h"
#include "SequentialSearchST.h"

using namespace std;

typedef string keytype;
typedef int valtype;

namespace
{
} // Anonymous namespace

void SequentialSearchSTTest::test()
{
    SequentialSearchST<keytype, valtype> st;
    st["Sameer"] = 44;
    st["John"] = 32;
    st["Rajiv"] = 80;
    st["Gordon"] = 100;
    st["Connor McCloud"] = 1500;

    SequentialSearchST<keytype, valtype> st2;
    st2["Sameer"] = 44;
    st2["John"] = 32;
    st2["Rajiv"] = 80;
    st2["Gordon"] = 100;
    st2["Connor McCloud"] = 1500;

    assert("Size of ss is 5", st.size() == 5);
    assert("Equal is equal", st == st2 && st2 == st);

    SequentialSearchST<keytype, valtype> st3;
    st3["Sameer"] = 44;
    st3["John"] = 31;
    st3["Rajiv"] = 80;
    st3["Gordon"] = 100;
    st3["Connor McCloud"] = 1500;

    assert("Equal size, Unequal value", (st2 != st3) && ((st2 == st3) == false));

    SequentialSearchST<keytype, valtype> st4;
    st4["Sameer"] = 44;
    st4["John"] = 31;
    st4["Gordon"] = 100;
    st4["Connor McCloud"] = 1500;
    assert("Unequal size", (st2 != st4) && ((st2 == st4) == false));

    int ageBefore = st["Sameer"];
    st["Sameer"] = 45;
    int ageAfter = st["Sameer"];
    assert("Value changed", ageBefore != ageAfter && ageAfter == 45);

//    vector<keytype> keys(st.begin(), st.end());
//    for(auto key: keys)
//    {
//        cout << *key << " " << endl;
//    }
}

void SequentialSearchSTTest::runAll()
{
    test();
    CppTest::runAll();
}
