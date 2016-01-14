/*
 * SequentialSearchSTTest.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: spatel78745
 */

#include <iostream>
#include <vector>
#include <iterator>
#include "SequentialSearchSTTest.h"
#include "SequentialSearchST.h"

using namespace std;

namespace
{
} // Anonymous namespace

void SequentialSearchSTTest::testCopyAssignment()
{
    header(__func__);

    SequentialSearchST<keytype, valtype> st {
            { "Sameer", 44 },
            { "John", 32   },
            { "Rajiv", 80  },
            { "Gordon", 100 },
            { "Connor McCloud", 1500 }
    };

    SequentialSearchST<keytype, valtype> st2 {
        { "Joe", 65 },
        { "Andy", 109   },
        { "Chris", 34  },
        { "Brocktoon", 92 },
        { "Mad Max", 41 }
    };

    cout << "Before assignment st2 = st" << endl;
    cout << "st: " << st << endl;
    cout << "st2: " << st2 << endl;

    st2 = st;
    cout << "After assignment st2 = st" << endl;
    cout << "st: " << st << endl;
    cout << "st2: " << st2 << endl;

    st2["Rajiv"] = 69;
    st["Vladimir"] = 55;
    cout << "After changes" << endl;
    cout << "st: " << st << endl;
    cout << "st2: " << st2 << endl;
}

void SequentialSearchSTTest::testCopyConstructor()
{
    header("testCopyConstructor");

    const SequentialSearchST<keytype, valtype> st {
            { "Sameer", 44 },
            { "John", 32   },
            { "Rajiv", 80  },
            { "Gordon", 100 },
            { "Connor McCloud", 1500 }
    };

    SequentialSearchST<keytype, valtype> stCp(st);

    cout << "st: " << st << endl;
    cout << "st copy: " << stCp << endl;

    assert("Copies ==?", st == stCp) ;
}

void SequentialSearchSTTest::testListInitConst()
{
    header("testListInitConst");

    const SequentialSearchST<keytype, valtype> st {
            { "Sameer", 44 },
            { "John", 32   },
            { "Rajiv", 80  },
            { "Gordon", 100 },
            { "Connor McCloud", 1500 }
    };

    cout << "st[Sameer] = " << st["Sameer"] << endl;
    assert("st[Sameer] = 44", st["Sameer"] == 44);

    for(string& key: st)
    {
        cout << key << ": " << st[key] << endl;
    }

    try
    {
        valtype val{st["unknown"]};
        cout << "st[unknown]=" << val << endl;
        assert("Absent key throws exception", false);
    }
    catch(MyException& e)
    {
        cout << "Ooops! -- " << e.what() << endl;
        assert("Absent key throws exception", true);
    }
}

void SequentialSearchSTTest::testListInit()
{
    header("testListInit");

    SequentialSearchST<keytype, valtype> st = {
            { "Sameer", 44 },
            { "John", 32   },
            { "Rajiv", 80  },
            { "Gordon", 100 },
            { "Connor McCloud", 1500 }
    };

    for(string& key: st)
    {
        cout << key << ": " << st[key] << endl;
    }

    st["Sameer"] = 45;
    cout << "st[Sameer] after change: " << st["Sameer"] << endl;
    assert("Change", st["Sameer"] == 45);

}

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

void SequentialSearchSTTest::testIteratorGetPair()
{
    header("testListInit");

    StT st =
    {
        { "Sameer", 44 },
        { "John", 32   },
        { "Rajiv", 80  },
        { "Gordon", 100 },
        { "Connor McCloud", 1500 }
    };

    for(StT::iterator iter = st.begin(); iter != st.end(); ++iter)
    {
        pairT p = iter.getPair();
        cout << p.first << ": " << p.second << endl;
    }
}

void SequentialSearchSTTest::testDel()
{
    const initializer_list<pairT> list = {
        { "Sameer", 44 },
        { "John", 32   },
        { "Rajiv", 80  },
        { "Gordon", 100 },
        { "Connor McCloud", 1500 }
    };

    const StT st_orig{list};
    StT st;
    pairT elem;
    initializer_list<pairT>::iterator iter;
    initializer_list<pairT>::iterator start;

    cout << "===================" << endl;
    cout << "Delete from head" << endl;
    st = st_orig;
    cout << st << endl;

    iter = list.end();
    start = list.begin();

    while(iter != start)
    {
        --iter;
        elem = *iter;
        cout << "Deleting " << elem.first << endl;
        st.del(elem.first);
        cout << st << endl;
    }

    cout << "Deleting again " << elem.first << endl;
    cout << st << endl;
    cout << "===================" << endl;

    cout << "===================" << endl;
    cout << "Delete interior" << endl;
    st = st_orig;
    cout << st << endl;

    iter = list.end();
    start = list.begin();
    --iter;
    while(iter != start)
    {
        --iter;
        elem = *iter;
        cout << "Deleting one past the head " << elem.first << endl;

        st.del(elem.first);
        cout << st << endl;
    }

    iter = list.end();
    --iter;
    elem = *iter;
    cout << "Deleting final element " << elem.first << endl;
    st.del(elem.first);
    cout << st << endl;

    cout << "Deleting again " << elem.first << endl;
    st.del(elem.first);
    cout << st << endl;
    cout << "===================" << endl;

    cout << "===================" << endl;
    cout << "Delete from empty" << endl;
    st = StT{};
    cout << st << endl;

    cout << "Deleting random string Sameer" << endl;
    st.del("Sameer");
    cout << st << endl;

    cout << "Deleting again random string Sameer" << endl;
    st.del("Sameer");
    cout << st << endl;
}

void SequentialSearchSTTest::runAll()
{
//    test();
//    testListInit();
//    testListInitConst();
//    testCopyConstructor();
//    testCopyAssignment();
//    testIteratorGetPair();
    testDel();
    CppTest::runAll();
}
