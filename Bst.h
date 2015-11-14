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
#include <algorithm>
#include <utility>
#include <vector>
#include <initializer_list>
#include "Node.h"

using std::string;
using std::cout;
using std::cerr;
using std::max;
using std::pair;
using std::vector;
using std::initializer_list;

template<typename K, typename V>
class Bst
{
public:
	typedef Node<K, V> NodeT;
	typedef typename vector<NodeT>::iterator iterator;
	typedef typename vector<NodeT>::const_iterator const_iterator;
	typedef size_t size_type;
	typedef V value_type;
	typedef K key_type;

	Bst() :
			mRoot(nullptr)
	{
	}

	Bst(initializer_list<pair<K, V>> elems) :
			Bst()
	{
		for (pair<K, V> p : elems)
		{
			put(p.first, p.second);
		}
	}

	~Bst()
	{
		delete mRoot;
	}

	NodeT& operator[](K key)
	{
		NodeT *node = get(key);

		return (node == nullptr) ? NodeT::null() : *node;
	}

	// TODO: How do I fix this code duplication? A lambda?
	const NodeT& operator[](K key) const
	{
		NodeT *node = get(key);

		return (node == nullptr) ? NodeT::null() : *node;
	}

	void put(const K key, const V val)
	{
		NodeT *node = new NodeT(key, val);
		mRoot = put(mRoot, node);
	}

	NodeT *get(const K key) const
	{
		return get(mRoot, key);
	}

	size_type size() const
	{
		return size(mRoot);
	}

	size_type height() const
	{
		return height(mRoot);
	}

	void print() const
	{
		cerr << "size: " << size() << endl;
		cerr << "height: " << height() << endl;
		print(mRoot);
		cerr << endl;
	}

	vector<K> keys() const
	{
		vector<K> ks;

		keys(mRoot, ks);

		return ks;
	}

private:
	void keys(NodeT *x, vector<K>& ks) const
	{
		if (x != nullptr)
		{
			ks.push_back(x->mKey);

			keys(x->mLeft, ks);
			keys(x->mRight, ks);
		}
	}

	size_type size(NodeT *x) const
	{
		if (x == nullptr)
		{
			return 0;
		}
		else
		{
			return x->mSize;
		}
	}

	size_type height(NodeT *x) const
	{
		if (x == nullptr)
		{
			return 0;
		}

		return max(1 + height(x->mLeft), 1 + height(x->mRight));
	}

	NodeT *get(NodeT *x, K key) const
	{
		if (x == nullptr)
		{
			return nullptr;
		}

		if (key < x->mKey)
		{
			return get(x->mLeft, key);
		}

		if (x->mKey < key)
		{
			return get(x->mRight, key);
		}

		return x;

	}

	NodeT *put(NodeT *x, NodeT *node)
	{
		bool debug = false;

		std::string parentKey = ((x == nullptr || x->mParent == nullptr) ? "null" : x->mParent->mKey);

		if (x == nullptr)
		{
			if (debug)
				std::cerr << "Inserting " << node->mKey << " " << parentKey << "\n";

			return node;
		}

		if (*node < *x)
		{
			if (debug)
				std::cerr << "Going left from " << x->mKey << " to insert " << node->mKey << " parent " << parentKey << "\n";
			x->mLeft = put(x->mLeft, node);
			x->mLeft->mParent = x;
		}
		else if (*x < *node)
		{
			if (debug)
				std::cerr << "Going right from " << x->mKey << " to insert " << node->mKey << " parent " << parentKey << "\n";
			x->mRight = put(x->mRight, node);
			x->mRight->mParent = x;
		}
		else
		{
			if (debug)
				std::cout << "Replacing value in " << node->mKey << "\n";
			x->mVal = node->mVal;
		}

		x->mSize = size(x->mRight) + size(x->mLeft) + 1;

		return x;
	}

	void print(NodeT *x) const
	{
		if (x == nullptr)
		{
			return;
		}

		string parentKey = ((x->mParent == nullptr) ? "null" : x->mParent->mKey);

		cerr << x->mKey << "/" << parentKey << "/" << size(x) << " ";
		print(x->mLeft);
		print(x->mRight);
	}

	NodeT *mRoot;
};

#endif /* BST_H_ */
