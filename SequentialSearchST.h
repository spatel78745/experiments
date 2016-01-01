/*
 * SequentialSearchST.h
 *
 *  Created on: Dec 30, 2015
 *      Author: spatel78745
 */

#ifndef SEQUENTIALSEARCHST_H_
#define SEQUENTIALSEARCHST_H_

#include <cstdlib>
#include <iostream>

using namespace std;

template <class K, class V>
class SequentialSearchST
{
private:
    class Node
    {
    public:
        Node(K key, V val): mKey(key), mVal(val) {}
    public:
        K mKey;
        V mVal;
        Node *mNext = nullptr;
    };

public:
    class Iterator
    {
    public:
        Iterator(Node *pos) : mPos(pos) {}

        Iterator& operator++()
        {
            if (mPos != nullptr) mPos = mPos->mNext;
            return *this;
        }

        Iterator& operator++(int)
        {
            Iterator current = Iterator(mPos);
            ++(*this);

            return current;
        }

        K& operator*()
        {
            return mPos->mKey;
        }

        bool operator==(const Iterator& other) const
        {
            return other.mPos == mPos;
        }

        bool operator!=(const Iterator& other) const
        {
            return other.mPos != mPos;
        }

    private:
        Node *mPos;
    };

    typedef size_t size_type;
    typedef Iterator iterator;

    SequentialSearchST() {};

    Iterator begin() { return Iterator(mHead); }

    Iterator end() { return nullptr; }

    Node *put(K key, V val)
    {
        Node *node = new Node(key, val);
        if (mHead == nullptr)
            mHead = node;
        else
        {
            node->mNext = mHead;
            mHead = node;
        }

        return node;
    }

    V& operator[](K key)
    {
        for(Node *p = mHead; p != nullptr; p = p->mNext)
        {
            if (p->mKey == key) return p->mVal;
        }

        return(put(key, V{})->mVal);
    }

    void dump()
    {
        for(Node *p = mHead; p != nullptr; p = p->mNext)
        {
            cout << "key " << p->mKey << "val " << p->mVal << endl;
        }
    }

private: // data
    Node *mHead = nullptr;
    size_type mSize = 0;
};

#endif /* SEQUENTIALSEARCHST_H_ */
