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
#include "Bst.h"
#include "Node.h"

// TODO: Is doing this bad? Seems better then a long list of using std:: etc.
using namespace std;

typedef Bst<string, int> BstT;
typedef BstT::NodeT NodeT;
typedef BstT::key_type KeyT;
typedef BstT::value_type ValT;

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

void testPut()
{
	header("put");

	BstT bst;
	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

	for (int i = 0; i != keys.size(); ++i)
	{
		bst.put(keys[i], i);
	}

	bst.print();

	pf("size", bst.size() == keys.size());
	pf("height", bst.height() == 4);
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
//			pf("get", false);
//		}
//
//		if (debug)
//			cerr << "key: " << node->key() << " val: " << node->val() << endl;
//		if (node->key() != key)
//		{
//			cerr << "fail: expected key: " << key << ", got key: " << node->val() << endl;
//			pf("get", false);
//			return;
//		}
//
//		if (i != node->val())
//		{
//			cerr << "fail: expected val: " << key << ", got val: " << node->val() << endl;
//			pf("get", false);
//			return;
//		}
//	}
//
//	NodeT *node = bst.get("W");
//	if (node != nullptr)
//	{
//		cerr << "fail: expected nullptr, got " << node;
//		pf("get", false);
//	}
//
//	pf("get", true);
//}

void testNoConstIndex()
{
}

void testIsNull()
{
	NodeT a("a", 'a');

	header("null");


	pf("null == null", NodeT::null() == NodeT::null());
	pf("null == a", !(NodeT::null() == a));
}

void testOpEqual()
{
	NodeT a1("a", 'a');
	NodeT a2("a", 'a');
	NodeT b("b", 'b');

	header("equal ==");

	pf("a1 == a2", a1 == a2);
	pf("a1 == b", !(a1 == b));
}

void testOpIndex()
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
		NodeT& node = bst[key];
		NodeT::value_type val = node.val();
		cerr << "[ " << key << " ] = " << node.val() << endl;
		if (val != i)
		{
			pf("[]", false);
		}
	}
	pf("[]", true);

	pf("[unknown]", bst["unknown"] == NodeT::null());
}

void testInitializerListConst()
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
	pf("[]", nodeE.val() == 5);

	pf("size", bst.size() == 9);
	pf("height", bst.height() == 4);
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

	if (!pf("equal size: ", keyList.size() == keys.size() && keys.size() == bst.size()))
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

	pf("found all keys", expectedKeys.empty());
}

void testFloor()
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
    pf("floor(A) == undefined", floor("A") == "undefined");

    pf("floor(C) == C", floor("C") == "C");
    pf("floor(D) == C", floor("D") == "C");
    pf("floor(F) == E", floor("F") == "E");
    pf("floor(I) == H", floor("I") == "H");
    pf("floor(S) == S", floor("S") == "S");
    pf("floor(T) == T", floor("T") == "T");
    pf("floor(U) == T", floor("U") == "T");
    pf("floor(Y) == Y", floor("Y") == "Y");
    pf("floor(Z) == Y", floor("Z") == "Y");
}

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

void testInOrder()
{
    header("in order");

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

    if (debug)
    {
        bst.print();
    }

    vector<NodeT> nodesInOrder;
    bst.inOrder(nodesInOrder);

    vector<KeyT> sortedKeys;

    for (pair<KeyT, ValT> p: l)
    {
        sortedKeys.push_back(p.first);
    }

    sort(sortedKeys.begin(), sortedKeys.end());

    if (debug)
    {
        cerr << "sorted keys vector size: " << sortedKeys.size() << endl;
        cerr << "inorder nodes vector size: " << nodesInOrder.size() << endl;
        printCollection("sorted keys", sortedKeys, [](const KeyT& key) { return key; });
        printCollection("inorder nodes", nodesInOrder, [](const NodeT& node) { return node.key(); });
    }

    if (!pf("size match", sortedKeys.size() == nodesInOrder.size()))
    {
        return;
    }

    for (int i = 0; i < sortedKeys.size(); ++i)
    {
        if (!pf("order", nodesInOrder[i].key() == sortedKeys[i]))
        {
            cerr << nodesInOrder[i].key() << " != " << sortedKeys[i] << endl;
            return;
        }
    }
}


void testTree()
{
//    testPut();
//    testGet();
//    testIsNull();
//    testOpEqual();
//    testOpIndex();
//    testInitializerListConst();
//    testKeys();
//    testFloor();
    testInOrder();
}
