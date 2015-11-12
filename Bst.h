/*
 * Bst.h
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <sstream>
#include "Node.h"

using std::string;
using std::cout;
using std::cerr;

template<typename K, typename V>
class Bst
{
public:
	typedef Node<K, V> NodeT;

	Bst() :
			mRoot(nullptr)
	{
	}

	~Bst()
	{
		delete mRoot;
	}

	void put(const K key, const V val)
	{
		NodeT *node = new NodeT(key, val);
		mRoot = put(mRoot, nullptr, node);
	}

	void print()
	{
		print(mRoot);
	}

private:
	NodeT *put(NodeT *x, NodeT *p, NodeT *node)
	{
		std::string parentKey = ((p == nullptr) ? "no parent (root)" : " " + p->mKey);

		if (x == nullptr)
		{
			std::cerr << "Inserting " << node->mKey << " " << parentKey << "\n";

			node->mParent = p;

			return node;
		}

		if (*node < *x)
		{
			std::cerr << "Going left from " << x->mKey << " to insert " << node->mKey << " parent " << parentKey << "\n";
			x->mLeft = put(x->mLeft, x, node);
		}
		else if (*x < *node)
		{
			std::cerr << "Going right from " << x->mKey << " to insert " << node->mKey << " parent " << parentKey << "\n";
			x->mRight = put(x->mRight, x, node);
		}
		else
		{
			std::cout << "Replacing value in " << node->mKey << "\n";
			x->mVal = node->mVal;
		}

		return x;
	}

	void print(NodeT *x)
	{
		if (x == nullptr)
		{
			return;
		}

		string parentKey = ((x->mParent == nullptr) ? "null" : x->mParent->mKey);

		cerr << x->mKey << "(" << parentKey << ") ";
		print(x->mLeft);
		print(x->mRight);
	}

	NodeT *mRoot;
};

#endif /* BST_H_ */
