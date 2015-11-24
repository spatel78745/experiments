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

#include "CppTest.h"
#include "Node.h"

class BstTest : public CppTest
{
    void runAll() {}
};

BstTest T;

// TODO: Is doing this bad? Seems better then a long list of using std:: etc.
using namespace std;

typedef Bst<string, int> BstT;
typedef BstT::NodeT NodeT;
typedef BstT::key_type KeyT;
typedef BstT::value_type ValT;
typedef pair<KeyT, ValT> PairT;

template <typename T>
static void print(string title, T listOfPairs, bool printKey = true)
{

    cerr << title << ": ";
    for(PairT& p: listOfPairs)
        cerr << (printKey ? p.first : to_string(p.second));
}

void testPut()
{
	T.header("put");

	BstT bst;
	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

	for (int i = 0; i != keys.size(); ++i)
	{
		bst.put(keys[i], i);
	}

	bst.print();

	T.assert("size", bst.size() == keys.size());
	T.assert("height", bst.height() == 4);
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
//			T.assert("get", false);
//		}
//
//		if (debug)
//			cerr << "key: " << node->key() << " val: " << node->val() << endl;
//		if (node->key() != key)
//		{
//			cerr << "fail: expected key: " << key << ", got key: " << node->val() << endl;
//			T.assert("get", false);
//			return;
//		}
//
//		if (i != node->val())
//		{
//			cerr << "fail: expected val: " << key << ", got val: " << node->val() << endl;
//			T.assert("get", false);
//			return;
//		}
//	}
//
//	NodeT *node = bst.get("W");
//	if (node != nullptr)
//	{
//		cerr << "fail: expected nullptr, got " << node;
//		T.assert("get", false);
//	}
//
//	T.assert("get", true);
//}

void testNoConstIndex()
{
}

void testIsNull()
{
	NodeT a("a", 'a');

	T.header("null");


	T.assert("null == null", NodeT::null() == NodeT::null());
	T.assert("null == a", !(NodeT::null() == a));
}

void testOpEqual()
{
	NodeT a1("a", 'a');
	NodeT a2("a", 'a');
	NodeT b("b", 'b');

	T.header("equal ==");

	T.assert("a1 == a2", a1 == a2);
	T.assert("a1 == b", !(a1 == b));
}

void testOpIndex()
{
	T.header("index []");

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
			T.assert("[]", false);
		}
	}
	T.assert("[]", true);

	T.assert("[unknown]", bst["unknown"] == NodeT::null());
}

void testInitializerListConst()
{
	T.header("const initializer list");

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
	T.assert("[]", nodeE.val() == 5);

	T.assert("size", bst.size() == 9);
	T.assert("height", bst.height() == 4);
}

void testKeys()
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

	if (!T.assert("equal size: ", keyList.size() == keys.size() && keys.size() == bst.size()))
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

	T.assert("found all keys", expectedKeys.empty());
}

void testFloor()
{
	T.header("testFloor");

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
    T.assert("floor(A) == undefined", floor("A") == "undefined");

    T.assert("floor(C) == C", floor("C") == "C");
    T.assert("floor(D) == C", floor("D") == "C");
    T.assert("floor(F) == E", floor("F") == "E");
    T.assert("floor(I) == H", floor("I") == "H");
    T.assert("floor(S) == S", floor("S") == "S");
    T.assert("floor(T) == T", floor("T") == "T");
    T.assert("floor(U) == T", floor("U") == "T");
    T.assert("floor(Y) == Y", floor("Y") == "Y");
    T.assert("floor(Z) == Y", floor("Z") == "Y");
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
void testInOrder()
{
    T.header("in order");

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

    T.assert("sorted initial values == nodes in order", initialValues == nodesInOrder);

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

void testIterator()
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
    if (!T.assert("match size", ((e - b) == bst.size()) && (bst.size() == l.size())))
    {
        return;
    }

    for(auto& p: l)
    {
        if (find_if(b, e, [&p](const NodeT& n) { return n.key() == p.first; } ) == e)
        {
            T.assert(p.first + " not found", false);
            return;
        }
    }

    T.assert("all keys found", true);
}

template <typename A, typename B>
string pairStr(pair<A, B> p)
{
    stringstream ss;
    ss << "(" << p.first << ", " << p.second << ")";

    return ss.str();
}

void testIsTree()
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

    T.assert("unmodified is a BST?", bst.isTree());

    bst["X"] = NodeT("Z", 26);
    bst.print();

    T.assert("modified is a BST?", bst.isTree());
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
void testDeleteMin()
{
    T.header("delete minimum");

    typedef typename vector<PairT>::iterator iter;
    BstT emptyBst;

    try { emptyBst.deleteMin(); }
    catch(out_of_range& e)
    {
        T.assert(string("exception: ") + e.what(), true);
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

        T.assert("deletedMin " + pairStr(deletedMin) + " == expectedMin " + pairStr(expectedMin),
                deletedMin == expectedMin);

        // Was it actually deleted?
        T.assert("size decremented: size before = " + to_string(sizeBeforeDel) + " size after = " +
                to_string(bst.size()), sizeBeforeDel == (1 + bst.size()));
        T.assert("element deleted?", bst[expectedMin.first] == NodeT::null());

        /*
         * Is it still a BST?
         * - The keys from (i + 1) to end() should match the keys in an inorder traversal of the
         *   tree.
         */
        T.assert("still a BST?", bst.isTree());
    }

    // Are all the nodes deleted?
    T.assert("empty?", bst.size() == 0);

    cerr << endl;

    T.assert("size is 0", bst.size() == 0);
}

void testTree()
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
    testDeleteMin();
}
