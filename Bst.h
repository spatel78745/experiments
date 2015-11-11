/*
 * Bst.h
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include "Node.h"

template <typename K, typename V>
class Bst
{
public:
	typedef Node<K, V> NodeT;

	Bst() :
			mRoot(nullptr)
	{
	}

	~Bst() { delete mRoot; };

	void put(K key, V val)
	{
		NodeT *node = new NodeT(key, val);
		mRoot = put(mRoot, node);
	}

private:
	NodeT *put(NodeT *x, NodeT *node)
	{
		if (x == nullptr)
		{
			std::cout << "Inserted " << node->mKey << "\n";
			return node;
		}

		if (*node < *x)
		{
			std::cout << "Going left to insert " << node->mKey << "\n";
			x->mLeft = put(x->mLeft, node);
		}
		else if (*x < *node)
		{
			std::cout << "Going right to insert " << node->mKey << "\n";
			x->mRight = put(x->mRight, node);
		}
		else
		{
			std::cout << "Replacing value in " << node->mKey << "\n";
			x->mVal = node->mVal;
		}

		return x;
	}

	NodeT *mRoot;
};

#endif /* BST_H_ */
