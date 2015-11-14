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

void testGet()
{
	header("get");

	bool debug = false;

	BstT bst;
	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

	// Insert the keys
	for (int i = 0; i != keys.size(); ++i)
	{
		bst.put(keys[i], i);
	}

	for (int i = 0; i != keys.size(); ++i)
	{
		string key = keys[i];
		NodeT *node = bst.get(key);

		if (node == nullptr)
		{
			pf("get", false);
		}

		if (debug)
			cerr << "key: " << node->key() << " val: " << node->val() << endl;
		if (node->key() != key)
		{
			cerr << "fail: expected key: " << key << ", got key: " << node->val() << endl;
			pf("get", false);
			return;
		}

		if (i != node->val())
		{
			cerr << "fail: expected val: " << key << ", got val: " << node->val() << endl;
			pf("get", false);
			return;
		}
	}

	NodeT *node = bst.get("W");
	if (node != nullptr)
	{
		cerr << "fail: expected nullptr, got " << node;
		pf("get", false);
	}

	pf("get", true);
}

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

	BstT bst;
	vector<KeyT> keys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

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

void testTree()
{
//	testPut();
//	testGet();
//	testIsNull();
//	testOpEqual();
//	testOpIndex();
//	testInitializerListConst();
	testKeys();
}
