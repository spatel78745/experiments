/*
 * HashtableTest.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: spatel78745
 */

#include <iostream>
#include <vector>
#include "HashtableTest.h"

using namespace std;

namespace
{
} // Anonymous namespace

void HashtableTest::testCopyAssignment()
{
//    SequentialSearchST<keytype, valtype> st {
//            { "Sameer", 44 },
//            { "John", 32   },
//            { "Rajiv", 80  },
//            { "Gordon", 100 },
//            { "Connor McCloud", 1500 }
//    };
//
//    SequentialSearchST<keytype, valtype> st2 {
//        { "Joe", 65 },
//        { "Andy", 109   },
//        { "Chris", 34  },
//        { "Brocktoon", 92 },
//        { "Mad Max", 41 }
//    };
//
//    cout << "Before assignment st2 = st" << endl;
//    cout << "st: " << st << endl;
//    cout << "st2: " << st2 << endl;
//
//    st2 = st;
//    cout << "After assignment st2 = st" << endl;
//    cout << "st: " << st << endl;
//    cout << "st2: " << st2 << endl;
//
//    st2["Rajiv"] = 69;
//    st["Vladimir"] = 55;
//    cout << "After changes" << endl;
//    cout << "st: " << st << endl;
//    cout << "st2: " << st2 << endl;
}

void HashtableTest::testCopyConstructor()
{
//    header("testCopyConstructor");
//
//    const SequentialSearchST<keytype, valtype> st {
//            { "Sameer", 44 },
//            { "John", 32   },
//            { "Rajiv", 80  },
//            { "Gordon", 100 },
//            { "Connor McCloud", 1500 }
//    };
//
//    SequentialSearchST<keytype, valtype> stCp(st);
//
//    cout << "st: " << st << endl;
//    cout << "st copy: " << stCp << endl;
//
//    assert("Copies ==?", st == stCp) ;
}

void HashtableTest::testListInitConst()
{
//    header("testListInitConst");
//
//    const SequentialSearchST<keytype, valtype> st {
//            { "Sameer", 44 },
//            { "John", 32   },
//            { "Rajiv", 80  },
//            { "Gordon", 100 },
//            { "Connor McCloud", 1500 }
//    };
//
//    cout << "st[Sameer] = " << st["Sameer"] << endl;
//    assert("st[Sameer] = 44", st["Sameer"] == 44);
//
//    for(string& key: st)
//    {
//        cout << key << ": " << st[key] << endl;
//    }
//
//    try
//    {
//        valtype val{st["unknown"]};
//        cout << "st[unknown]=" << val << endl;
//        assert("Absent key throws exception", false);
//    }
//    catch(MyException& e)
//    {
//        cout << "Ooops! -- " << e.what() << endl;
//        assert("Absent key throws exception", true);
//    }
}

void HashtableTest::testListInit()
{
//    header("testListInit");
//
//    SequentialSearchST<keytype, valtype> st = {
//            { "Sameer", 44 },
//            { "John", 32   },
//            { "Rajiv", 80  },
//            { "Gordon", 100 },
//            { "Connor McCloud", 1500 }
//    };
//
//    for(string& key: st)
//    {
//        cout << key << ": " << st[key] << endl;
//    }
//
//    st["Sameer"] = 45;
//    cout << "st[Sameer] after change: " << st["Sameer"] << endl;
//    assert("Change", st["Sameer"] == 45);
//
}

void HashtableTest::test()
{
    header(__func__);

    // Test insert via []
    Ht ht;

    cout << "Inserted elements via []" << endl;
    ht["Sameer"] = 44;
    ht["John"] = 32;
    ht["Rajiv Vindaloo"] = 80;
    ht["Gordon Ramsay"] = 50;
    ht["Connor McCloud"] = 1500;
    ht["Cthulu"] = 1500000;
    ht["Terminator T1000"] = 30;

    cout << "Dump using []" << endl;
    cout << "Sameer: " << ht["Sameer"] << endl;
    cout << "Rajiv Vindaloo: " << ht["Rajiv Vindaloo"] << endl;
    cout << "Gordon Ramsay: " << ht["Gordon Ramsay"] << endl;
    cout << "Connor McCloud: " << ht["Connor McCloud"] << endl;
    cout << "Cthulu: " << ht["Cthulu"] << endl;
    cout << "Terminator T1000: " << ht["Terminator T1000"] << endl;

    cout << "Dump using <<" << endl;
    cout << ht << endl;

    const Ht htConst;

//    SequentialSearchST<keytype, valtype> st;
//    st["Sameer"] = 44;
//    st["John"] = 32;
//    st["Rajiv"] = 80;
//    st["Gordon"] = 100;
//    st["Connor McCloud"] = 1500;
//
//    SequentialSearchST<keytype, valtype> st2;
//    st2["Sameer"] = 44;
//    st2["John"] = 32;
//    st2["Rajiv"] = 80;
//    st2["Gordon"] = 100;
//    st2["Connor McCloud"] = 1500;
//
//    assert("Size of ss is 5", st.size() == 5);
//    assert("Equal is equal", st == st2 && st2 == st);
//
//    SequentialSearchST<keytype, valtype> st3;
//    st3["Sameer"] = 44;
//    st3["John"] = 31;
//    st3["Rajiv"] = 80;
//    st3["Gordon"] = 100;
//    st3["Connor McCloud"] = 1500;
//
//    assert("Equal size, Unequal value", (st2 != st3) && ((st2 == st3) == false));
//
//    SequentialSearchST<keytype, valtype> st4;
//    st4["Sameer"] = 44;
//    st4["John"] = 31;
//    st4["Gordon"] = 100;
//    st4["Connor McCloud"] = 1500;
//    assert("Unequal size", (st2 != st4) && ((st2 == st4) == false));
//
//    int ageBefore = st["Sameer"];
//    st["Sameer"] = 45;
//    int ageAfter = st["Sameer"];
//    assert("Value changed", ageBefore != ageAfter && ageAfter == 45);

//    vector<keytype> keys(st.begin(), st.end());
//    for(auto key: keys)
//    {
//        cout << *key << " " << endl;
//    }
}

void HashtableTest::testIterator()
{
    header(__func__);

    // Test insert via []
    Ht ht;
    pair<string, int> res;

    cout << "Inserted elements via []" << endl;
    ht["Sameer"] = 44;
    ht["John"] = 32;
    ht["Rajiv Vindaloo"] = 80;
    ht["Gordon Ramsay"] = 50;
    ht["Connor McCloud"] = 1500;
    ht["Cthulu"] = 1500000;
    ht["Terminator T1000"] = 30;

    cout << "[Dump of hashtable]" << endl;
    ht.dump();

    cout << "[++]" << endl;
    Ht::iterator iter = ht.begin();

    for (int i = 0; i < 50; ++i) {
        cout << "(" << i << ")" << endl;
        ++iter;
    }

//    for (Ht::iterator iter = ht.begin(); iter != ht.end(); ++iter) {
//
//    }
//    Ht::iterator end = ht.end();

//    cout << ht << endl;
//    cout << ht.begin().toStr() << endl;
//    cout << ht.end().toStr() << endl;
//
//    Ht::iterator iter = ht.begin();
//    res = *iter;
//    cout << "iter:" << iter.toStr() << " key=" << res.first << " val=" << res.second << endl;
//
//    ++iter;
//    res = *iter;
//    cout << "iter:" << iter.toStr() << " key=" << res.first << " val=" << res.second << endl;
//
//    ++iter;
//    res = *iter;
//    cout << "iter:" << iter.toStr() << " key=" << res.first << " val=" << res.second << endl;



//    for(auto p: ht)
//    {
//        cout << p.first << ": " << p.second << endl;
//    }
}



void HashtableTest::runAll()
{
    testIterator();
//    test();
//    testListInit();
//    testListInitConst();
//    testCopyConstructor();
//    testCopyAssignment();
    CppTest::runAll();
}
