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

void testFloor();

template<typename K, typename V>
class Bst
{
	// TODO: remove after public interface to floor is complete
	friend void testFloor();
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
		NodeT *node = get(mRoot, key);

		return (node == nullptr) ? NodeT::null() : *node;
	}

	// TODO: How do I fix this code duplication? A lambda?
	const NodeT& operator[](K key) const
	{
		NodeT *node = get(mRoot, key);

		return (node == nullptr) ? NodeT::null() : *node;
	}

	void put(const K key, const V val)
	{
		NodeT *node = new NodeT(key, val);
		mRoot = put(mRoot, node);
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

	NodeT& floor(K key) const
	{
	    NodeT *f = floor(mRoot, key);
	    if (f == nullptr)
	    {
	        return NodeT::null();
	    }

	    return *f;
	}

private:
	/*
	 * Returns the largest key in the tree that's less then the parameter "key"
	 *
	 * The naive algorithm is:
	 * - If the tree is empty, the floor is undefined, therefore return
	 *   NodeT::null()
	 * - Make a list of the keys in the tree and sort them ascending order
	 * - For each key in the list
	 *   - If the key is bigger than the parameter "key, " then by definition
	 *     it can't be the floor, so continue.
	 *   - If the key is less, then return it.
	 * - If we're here, all the keys were bigger then "key" so return null
	 *
	 * By now you should be used to thinking about the floor, so let's proceed
	 * with the recursive implementation. The basic idea is this:
	 *
	 * For any node x:
	 * - If (x == nullptr) then the floor is undefined, so return nullptr
	 * - If (x->key > "key") then it can't be the floor. If there is a floor, it
	 *   must be in the left subtree, so return the floor of the left subtree.
	 * - If (x->key == "key") then it's the floor, so return it
	 * - If (x->key < "key") then it might be the floor. However, the right
	 *   sub-tree contains keys that bigger then x->key. Some of them may
	 *   also be less then "key", so the floor may be in the right subtree.
	 *   So compute the floor of the right subtree, and call it FRS. If FRS
	 *   is null, then the floor must be x->key. If FRS is bigger than x->key
	 *   then it must be the floor, so return it. Otherwise, the only
	 *   remaining possibility is that the floor is the x->key.
	 *
	 *   Oh my god....
	 */
	NodeT *floor(NodeT *x, K key) const
	{
		/*
		 * First, the easy case. If the tree is empty, then the floor is
		 * undefined, so return nullptr in this case.
		 */
		if (x == nullptr)
		{
			return nullptr;
		}

		/*
		 * The next easiest case (for me to understand) is if x->key is
		 * larger then key. If this is true, then x->key can't be floor(key)
		 * because, by definition, floor(key) <= key. If there is a floor(key),
		 * it must be in the left sub-tree, so return floor(x->left, key)
		 */
		if (key < x->key())
		{
			return floor(x->mLeft, key);
		}

		/*
		 * And now for the trickiest case. If x->key is less then key, it may
		 * be floor(key). But the right sub-tree contains keys that are larger
		 * then x->key. Some of them may also be less than key, so the floor
		 * may be in the right subtree. So:
		 * - If floor(x->right)
		 *   - is nullptr, then either the right subtree is empty, or all the
		 *     keys are larger then key. So the floor must be x->key, so
		 *     return it.
		 *   - if larger or equal, then x->key, then it must be the floor, so return
		 *     floor(x->right).
		 */
		NodeT *frs = floor(x->mRight, key);

		if (frs == nullptr)
		{
			return x;
		}

		if (x->key() < frs->key())
		{
			return frs;
		}

		return x;
	}


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
