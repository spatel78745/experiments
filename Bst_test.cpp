/*
 * Bst_test.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#include <string>
#include <vector>
#include <iostream>
#include "Bst.h"
#include "Node.h"

using std::string;
using std::vector;
using std::cerr;
using std::endl;

typedef Bst<string, int> BstT;
typedef BstT::value_type NodeT;
typedef string KeyT;
typedef int ValT;

BstT gBst;
vector<KeyT> gKeys = { "H", "C", "S", "A", "E", "R", "X", "Z", "T" };

void header(string s)
{
	static string border("============");
	cerr << border << " " << s << " " << border << endl;
}

void pf(string test, bool result)
{
	string pass_fail(result ? "pass" : "fail");
	cerr << test << ": " << pass_fail << endl;
}

static void get(KeyT key)
{
	NodeT *node;

	node = gBst.get(key);

	cerr << "get(" << key << ") = { " << node->key() << ", " << node->val() << " }";
}

void testPut()
{
	header("put");

	for (int i = 0; i != gKeys.size(); ++i)
	{
		gBst.put(gKeys[i], i);
	}

	gBst.print();

	pf("size", gBst.size() == gKeys.size());
	pf("height", gBst.height() == 4);
}

void testGet()
{
	header("get");

	bool debug = false;

	for (int i = 0; i != gKeys.size(); ++i)
	{
		string key = gKeys[i];
		NodeT *node = gBst.get(key);

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

	NodeT *node = gBst.get("W");
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

	for(int i = 0; i != gKeys.size(); ++i) {
		string key = gKeys[i];
		NodeT& node = gBst[key];
		NodeT::value_type val = node.val();
		cerr << "[ " << key << " ] = " << node.val() << endl;
		if (val != i)
		{
			pf("[]", false);
		}
	}
	pf("[]", true);

	pf("[unknown]", gBst["unknown"] == NodeT::null());
}

void testTree()
{
	testPut();
	testGet();
	testIsNull();
	testOpEqual();
	testOpIndex();
}
