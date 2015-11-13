/*
 * Node.h
 *
 *  Created on: Nov 11, 2015
 *      Author: spatel78745
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <string>

using std::cout;
using std::endl;

template <typename, typename> class Bst;
template <typename, typename> class Node;
template <typename K, typename V> bool operator==(const Node<K, V>& lhs, const Node<K, V>& rhs);

template<typename K, typename V>
class Node
{
public:
	friend class Bst<K, V> ;
	friend bool operator==<K, V>(const Node<K, V>& lhs, const Node<K, V>& rhs);

	Node(const K key, const V val) :
			mKey(key), mVal(val), mSize(1), mLeft(nullptr), mRight(nullptr), mParent(nullptr), mIsNull(false)
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

	bool operator<(const Node& rhs) const
	{
		return mKey < rhs.mKey;
	}

	Node& operator=(const Node& rhs)
	{
		mKey = rhs.mKey;
		mVal = rhs.mVal;

		return *this;
	}

	static Node& null()
	{
		static Node nullNode(true);

		return nullNode;
	}

private:
	Node(bool isNull) : mIsNull(isNull) {}
	K mKey;
	V mVal;
	typename K::size_type mSize;
	Node *mLeft;
	Node *mRight;
	Node *mParent;
	bool mIsNull;
};

template <typename K, typename V>
bool operator==(const Node<K, V>& lhs, const Node<K, V>& rhs)
{
	if (lhs.mIsNull || rhs.mIsNull)
	{
		return (&lhs == &Node<K, V>::null()) && (&rhs == &Node<K, V>::null());
	}

	return (lhs.mKey == rhs.mKey) && (lhs.mVal == rhs.mVal);
}

#endif /* NODE_H_ */
