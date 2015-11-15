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
using std::cerr;

template <typename, typename> class Bst;
template <typename, typename> class Node;
template <typename K, typename V> bool operator==(const Node<K, V>& lhs, const Node<K, V>& rhs);

template<typename K, typename V>
class Node
{
public:
	friend class Bst<K, V> ;
	friend bool operator==<K, V>(const Node<K, V>& lhs, const Node<K, V>& rhs);

	typedef V value_type;

	Node(const K key, const V val) :
			mKey(key), mVal(val), mSize(1), mLeft(nullptr), mRight(nullptr), mParent(nullptr), mIsNull(false)
	{
	}

	/*
	 * An important note. I puzzled over this for quite a while (not really). Anyway, during
	 * my inorder traversal, I was pushing nodes into a vector which triggered the default
	 * copy constructor. During vector expansion, or whatever it was doing, nodes were also
	 * destructed, causing the entire subtree at that node to be destructed. This lead to a
	 * segfault. The solution was to make all the pointers null so that the destructor wouldn't
	 * destroy subtrees. By the way, all this is speculation...I don't know if that was actually
	 * what was happening. But the problem is fixed for the moment.
	 *
	 * TODO: And I consider this a "creative" problem: figure out exactly what was going on. Trace
	 * through a full example based on a hypothesis of how the vector class works.
	 *
	 * And now back to business...
	 */
	Node(const Node& node) :
        mKey(node.mKey), mVal(node.mVal), mSize(node.mSize), mLeft(nullptr), mRight(nullptr), mParent(nullptr), mIsNull(node.mIsNull)
	{
	    static bool debug = false;

	    if (debug)
	    {
	        cerr << "copy from " << node.mKey << ", " << node.mVal << endl;
	    }
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
