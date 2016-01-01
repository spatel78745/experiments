/*
 * Bst_test.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Bst.h"
#include "Node.h"
#include "BstTest.h"
#include "MyException.h"

// TODO: Is doing this bad? Seems better then a long list of using std:: etc.
using namespace std;

typedef Bst<string, int> BstT;
typedef BstT::NodeT NodeT;
typedef BstT::key_type KeyT;
typedef BstT::value_type ValT;
typedef pair<KeyT, ValT> PairT;

template <typename T>
void print(string title, T listOfPairs, bool printKey = true)
{

    cerr << title << ": ";
    for(PairT& p: listOfPairs)
        cerr << (printKey ? p.first : to_string(p.second));
}

void BstTest::testPut()
{
	header("put");

	BstT bst;
	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

	for (int i = 0; i != keys.size(); ++i)
	{
		bst.put(keys[i], i);
	}

	bst.print();

	assert("size", bst.size() == keys.size());
	assert("height", bst.height() == 4);
}

// TODO: add to index-operator test
//void testGet()
//{
//	header("get");
//
//	bool debug = false;
//
//	BstT bst;
//	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };
//
//	// Insert the keys
//	for (int i = 0; i != keys.size(); ++i)
//	{
//		bst.put(keys[i], i);
//	}
//
//	for (int i = 0; i != keys.size(); ++i)
//	{
//		string key = keys[i];
//		NodeT *node = bst.get(key);
//
//		if (node == nullptr)
//		{
//			assert("get", false);
//		}
//
//		if (debug)
//			cerr << "key: " << node->key() << " val: " << node->val() << endl;
//		if (node->key() != key)
//		{
//			cerr << "fail: expected key: " << key << ", got key: " << node->val() << endl;
//			assert("get", false);
//			return;
//		}
//
//		if (i != node->val())
//		{
//			cerr << "fail: expected val: " << key << ", got val: " << node->val() << endl;
//			assert("get", false);
//			return;
//		}
//	}
//
//	NodeT *node = bst.get("W");
//	if (node != nullptr)
//	{
//		cerr << "fail: expected nullptr, got " << node;
//		assert("get", false);
//	}
//
//	assert("get", true);
//}

void BstTest::testIsNull()
{
	NodeT a("a", 'a');

	header("null");


	assert("null == null", NodeT::null() == NodeT::null());
	assert("null == a", !(NodeT::null() == a));
}

void BstTest::testOpEqual()
{
	NodeT a1("a", 'a');
	NodeT a2("a", 'a');
	NodeT b("b", 'b');

	header("equal ==");

	assert("a1 == a2", a1 == a2);
	assert("a1 == b", !(a1 == b));
}

void BstTest::testOpIndex()
{
	header("index []");

	const bool debug = true;

	BstT bst;
	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

    for (int i = 0; i != keys.size(); ++i)
    {
        bst.put(keys[i], i);
    }

	if (debug)
	{
	    bst.print();
	}

	for(int i = 0; i != keys.size(); ++i) {
		string key = keys[i];
		const NodeT& node = bst[key];
		NodeT::value_type val = node.val();
		cerr << "[ " << key << " ] = " << node.val() << endl;
		if (val != i)
		{
			assert("[]", false);
		}
	}
	assert("[]", true);

	assert("[unknown]", bst["unknown"] == NodeT::null());
}

void BstTest::testInitializerListConst()
{
	header("const initializer list");

	const BstT bst =
	{
			{ "H", 1 },
			{ "C", 2 },
			{ "S", 3 },
			{ "A", 4 },
			{ "E", 5 },
			{ "R", 6 },
			{ "X", 7 },
			{ "Z", 8 },
			{ "T", 9 },
	};

	bst.print();

	const NodeT& nodeE = bst["E"];
	assert("[]", nodeE.val() == 5);

	assert("size", bst.size() == 9);
	assert("height", bst.height() == 4);
}

void BstTest::testKeys()
{
	const initializer_list<pair<KeyT, ValT>> keyList =
	{
			{ "H", 1 },
			{ "C", 2 },
			{ "S", 3 },
			{ "A", 4 },
			{ "E", 5 },
			{ "R", 6 },
			{ "X", 7 },
			{ "Z", 8 },
			{ "T", 9 },
	};

	const BstT bst(keyList);
	vector<KeyT> keys = bst.keys();

	if (!assert("equal size: ", keyList.size() == keys.size() && keys.size() == bst.size()))
	{
		return;
	}

	vector<pair<KeyT, ValT>> expectedKeys(keyList);

	for (auto k : keys)
	{
		vector<pair<KeyT, ValT>>::iterator i;

		for (i = expectedKeys.begin(); i != expectedKeys.end(); ++i)
		{
			if (i->first == k)
			{
				expectedKeys.erase(i);
				break;
			}
		}
	}

	assert("found all keys", expectedKeys.empty());
}

void BstTest::testFloor()
{
	header("testFloor");

	const BstT bst =
	{
			{ "H", 1 },
			{ "C", 2 },
			{ "S", 3 },
			{ "B", 4 },
			{ "E", 5 },
			{ "R", 6 },
			{ "X", 7 },
			{ "Y", 8 },
			{ "T", 9 },
	};

	auto floor = [&bst](KeyT key)
	{
	    NodeT& _floor = bst.floor(key);
	    return _floor == NodeT::null() ? "undefined" : _floor.key();
	};

	/*
	 * Let's compute the floor of the successor of all the keys. This should exercise
	 * all the code paths.
	 *
	 * 123456789
	 * HCSAERXYT
	 * BCEHRSTXY (sorted)
	 * CDFISTUYZ
	 * But does it exercise all the code paths? Let's see what floor(U) = T does. This should
	 * exercise all the code paths because you need to go right and left to get to T.
	 *
	 * First we visit H, then because it's less we go to S, then because it's less we go to X,
	 * then because it's bigger we go to T, then because it's less we go to nullptr and return.
	 * Thus, at T we are at the "frs == nullptr" case, and so the function returns T.
	 */
	// All the keys in the tree are larger than "A" so there is no floor.
    assert("floor(A) == undefined", floor("A") == "undefined");

    assert("floor(C) == C", floor("C") == "C");
    assert("floor(D) == C", floor("D") == "C");
    assert("floor(F) == E", floor("F") == "E");
    assert("floor(I) == H", floor("I") == "H");
    assert("floor(S) == S", floor("S") == "S");
    assert("floor(T) == T", floor("T") == "T");
    assert("floor(U) == T", floor("U") == "T");
    assert("floor(Y) == Y", floor("Y") == "Y");
    assert("floor(Z) == Y", floor("Z") == "Y");
}

/*
 * TODO: Make this printPair.
 */
template <typename T, typename Func>
void printCollection(string title, const T& collection, Func field)
{
    cerr << title << ":";

    for(auto& elem: collection)
    {
        cerr << field(elem) << " ";
    }

    cerr << endl;
}

/*
 * Things I learned:
 * - The compiler goes crazy and spits out a huge number of error messages if you try to sort
 *   a const collection...I had "const vector<PairT> initialValues.
 * - vector has an "operator==()" (and other relational operators), so you can compaire two
 *   vectors. pair's "operator==" does "operator==" on both first and second. All of this is
 *   most convenient.
 */
void BstTest::testInOrder()
{
    header("in order");

    bool debug = true;

    vector<PairT> initialValues =
    {
            { "H", 1 },
            { "C", 2 },
            { "S", 3 },
            { "B", 4 },
            { "E", 5 },
            { "R", 6 },
            { "X", 7 },
            { "Y", 8 },
            { "T", 9 },
    };

    const BstT bst(initialValues);

    if (debug)
    {
        bst.print();
    }

    vector<PairT> nodesInOrder;
    bst.inOrder(nodesInOrder);

    sort(initialValues.begin(), initialValues.end(),
            [](const PairT& a, const PairT& b) { return a.first < b.first; });

    if (debug)
    {
        auto printFirst = [](const PairT& p) { return p.first; };
        cerr << "inorder nodes vector size: " << nodesInOrder.size() << endl;
        cerr << "sorted init values vector size: " << initialValues.size() << endl;
        printCollection("sorted keys", initialValues, printFirst);
        printCollection("inorder nodes", nodesInOrder, printFirst);
    }

    assert("sorted initial values == nodes in order", initialValues == nodesInOrder);

}

vector<KeyT> keysFromInitializerList(initializer_list<pair<KeyT, ValT>> list)
{
    vector<KeyT> ret;

    for(auto& p: list)
    {
        ret.push_back(p.first);
    }

    return ret;
}

void BstTest::testIterator()
{
    bool debug = true;

    const initializer_list<pair<KeyT, ValT>> l =
    {
        { "H", 1 },
        { "C", 2 },
        { "S", 3 },
        { "B", 4 },
        { "E", 5 },
        { "R", 6 },
        { "X", 7 },
        { "Y", 8 },
        { "T", 9 },
    };

    const BstT bst(l);

    BstT::const_iterator b = bst.begin(), e = bst.end();

    if (debug)
    {
        bst.print();
        cerr << "end() - begin(): " << e - b << endl;
        cerr << "number of initializer pairs: " << l.size() << endl;
        cerr << "bst.size(): " << bst.size() << endl;
    }

    // Probably overkill on the conditions, but WTF.
    if (!assert("match size", ((e - b) == bst.size()) && (bst.size() == l.size())))
    {
        return;
    }

    for(auto& p: l)
    {
        if (find_if(b, e, [&p](const NodeT& n) { return n.key() == p.first; } ) == e)
        {
            assert(p.first + " not found", false);
            return;
        }
    }

    assert("all keys found", true);
}

template <typename A, typename B>
string pairStr(pair<A, B> p)
{
    stringstream ss;
    ss << "(" << p.first << ", " << p.second << ")";

    return ss.str();
}

void BstTest::testIsTree()
{
    vector<PairT> initVec =
    {
        { "H", 1 },
        { "C", 2 },
        { "S", 3 },
        { "B", 4 },
        { "E", 5 },
        { "R", 6 },
        { "X", 7 },
        { "Y", 8 },
        { "T", 9 },
    };

    BstT bst(initVec);

    assert("unmodified is a BST?", bst.isTree());

    bst["X"] = NodeT("Z", 26);
    bst.print();

    assert("modified is a BST?", bst.isTree());
}


/*
 * Things I learned:
 * - initializer_list can't be sorted
 * - for you're testing for equality by doing '==' on each field, consider using a type with an
 *   'operator=' that does this
 *
 * Design notes:
 * - After deleteMin() runs:
 *   - If run on an empty tree, it should throw an exception
 *   - There should be one less node in the tree
 *   - The minimum node shouldn't be in the tree
 *   - The tree should still be a BST
 */
void BstTest::testDeleteMin()
{
    header("delete minimum");

    typedef typename vector<PairT>::iterator iter;
    BstT emptyBst;

    try { emptyBst.deleteMin(); }
    catch(out_of_range& e)
    {
        assert(string("exception: ") + e.what(), true);
    }

    vector<PairT> initVec =
    {
        { "H", 1 },
        { "C", 2 },
        { "S", 3 },
        { "B", 4 },
        { "E", 5 },
        { "R", 6 },
        { "X", 7 },
        { "Y", 8 },
        { "T", 9 },
    };

    BstT bst(initVec);

    sort(initVec.begin(), initVec.end(), [](const PairT& a, const PairT&b) { return a < b; } );

    print("initial keys", initVec); cerr << endl;

    for(iter i = initVec.begin(); i != initVec.end(); ++i)
    {
        PairT& expectedMin = *i;
        BstT::size_type sizeBeforeDel = bst.size();

        pair<KeyT, ValT> deletedMin = bst.deleteMin();

        assert("deletedMin " + pairStr(deletedMin) + " == expectedMin " + pairStr(expectedMin),
                deletedMin == expectedMin);

        // Was it actually deleted?
        assert("size decremented: size before = " + to_string(sizeBeforeDel) + " size after = " +
                to_string(bst.size()), sizeBeforeDel == (1 + bst.size()));
        assert("element deleted?", bst[expectedMin.first] == NodeT::null());

        /*
         * Is it still a BST?
         * - The keys from (i + 1) to end() should match the keys in an inorder traversal of the
         *   tree.
         */
        assert("still a BST?", bst.isTree());
    }

    // Are all the nodes deleted?
    assert("empty?", bst.size() == 0);

    cerr << endl;

    assert("size is 0", bst.size() == 0);
}

void BstTest::testDraw()
{
    const string& testName = "testDraw";

    header(testName);

    const BstT bst =
    {
        { "H", 1 },
        { "C", 2 },
        { "S", 3 },
        { "B", 4 },
        { "E", 5 },
        { "R", 6 },
        { "X", 7 },
        { "Y", 8 },
        { "T", 9 },
    };

    try
    {
        const Gserv gs;
        bst.draw(gs);

        if (!ask("Do you see a tree corresponding to insert sequence HCSBERXYT? (y/n)"))
            assert("testDraw", false);

        assert(testName, true);
    }
    catch(MyException& e)
    {
        cout << e.what() << endl;
        assert(testName, false);
    }
}

void BstTest::runAll()
{
//    testPut();
//    testIsNull();
//    testOpEqual();
//    testOpIndex();
//    testInitializerListConst();
//    testKeys();
//    testFloor();
//    testInOrder();
//    testIterator();
//    testIsTree();
//    testDeleteMin();
    testDraw();

    CppTest::runAll();
}
