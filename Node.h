/*
 * Node.h
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#ifndef NODE_H_
#define NODE_H_

template <typename, typename> class Bst;

template<typename K, typename V>
class Node
{
public:
	friend class Bst<K, V> ;
public:
	Node(const K key, const V val) :
			mKey(key), mVal(val), mLeft(nullptr), mRight(nullptr)
	{
	}

	Node(const Node &node) :
			Node(node.mKey, node.mVal)
	{
	}

	virtual ~Node()
	{
		delete mLeft;
		delete mRight;
	}

	K key() const
	{
		return mKey;
	}

	V val() const
	{
		return mVal;
	}

	bool operator<(const Node &rhs) const
	{
		return mKey < rhs.mKey;
	}

	Node& operator=(const Node &rhs)
	{
		mKey = rhs.mKey;
		mVal = rhs.mVal;

		return *this;
	}

private:
	K mKey;
	V mVal;
	Node *mLeft;
	Node *mRight;
};

#endif /* NODE_H_ */
