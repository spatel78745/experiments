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
public:

//    class Iterator
//    {
//        class Node;
//    public:
//        Iterator(Node *pos) : mPos(pos) {}
//
//        Iterator& operator++()
//        {
//            if (mPos != nullptr) mPos = mPos->mNext;
//        }
//
//    private:
//        Node *mPos;
//    };

    typedef size_t size_type;
//    typedef Iterator iterator;

    SequentialSearchST() {};

//    Iterator begin() { return iterator(mHead); }
//
//    Iterator end()
//    {
//        Node *p = mHead;
//
//        while(p && p->mNext != nullptr)
//            p = p->mNext;
//
//        return Iterator(p);
//    }

    void put(K key, V val)
    {
        Node *node = new Node(key, val);
        if (mHead == nullptr)
            mHead = node;
        else
        {
            node->mNext = mHead;
            mHead = node;
        }
    }

    void dump()
    {
        for(Node *p = mHead; p != nullptr; p = p->mNext)
        {
            cout << "key " << p->mKey << "val " << p->mVal << endl;
        }
    }

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

private: // data
    Node *mHead = nullptr;
    size_type mSize = 0;
};

#endif /* SEQUENTIALSEARCHST_H_ */
