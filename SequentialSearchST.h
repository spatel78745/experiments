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
#include "MyException.h"

using namespace std;

template <class K, class V>
class SequentialSearchST
{
private:
    class Node
    {
    public:
        Node(K key, V val): mKey(key), mVal(val) {}

        bool operator==(const Node& other) const
        {
            return (mKey == other.mKey) && (mVal == other.mVal);
        }

        bool operator!=(const Node& other) const
        {
            return !(*this == other);
        }

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

        const Iterator& operator++()
        {
            if (mPos != nullptr) mPos = mPos->mNext;
            return *this;
        }

        const Iterator& operator++(int) const
        {
            Iterator current = Iterator(mPos);
            ++(*this);

            return current;
        }

        K& operator*() const
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
    typedef const Iterator const_iterator;
    typedef pair<K, V> pair_type;

    SequentialSearchST() {};

    SequentialSearchST(initializer_list<pair_type> lst)
    {
        for(pair_type p: lst)
        {
            put(p.first, p.second);
        }
    }

    SequentialSearchST(const SequentialSearchST& other)
    {
        for(auto key: other)
        {
            put(key, other[key]);
        }
        reverse();
    }

    ~SequentialSearchST()
    {
        int count{0};

        for(Node *p = mHead; p != nullptr; p = p->mNext)
        {
            cout << __func__ << ": deleting: " << p->mKey << endl;
            delete p;
            ++count;
        }

        cout << __func__ << ": Deleted " << count << " elements" << endl;
    }

    bool operator==(const SequentialSearchST& other) const
    {
        if (size() != other.size()) return false;
        for(Node *p = mHead, *q = other.mHead; p != nullptr && q != nullptr;
                p = p->mNext, q = q->mNext)
        {
            if (*p != *q) return false;
        }

        return true;
    }

    bool operator!=(const SequentialSearchST& other) const
    {
        return !(*this == other);
    }

    Iterator begin() const { return Iterator(mHead); }

    Iterator end() const { return nullptr; }

    size_type size() const
    {
        size_type size{0};

        for(Node *p = mHead; p != nullptr; p = p->mNext)
        {
            ++size;
        }

        return size;
    }

    V& operator[](K key)
    {
        Node *match;

        if ((match = get(key)))
        {
            return match->mVal;
        }

        return(put(key, V())->mVal);
    }

    V operator[](K key) const
    {
        Node *match;

        if ((match = get(key)))
        {
            return match->mVal;
        }

        throw MyException("Error: No such key");
    }

    SequentialSearchST& operator=(SequentialSearchST rhs)
    {
        swap(this->mHead, rhs.mHead);

        return *this;
    }

private:
    Node *get(K key) const
    {
        for(Node *p = mHead; p != nullptr; p = p->mNext)
        {
            if (p->mKey == key) return p;
        }

        return nullptr;
    }

    void prepend(Node *node)
    {
        if (mHead == nullptr)
        {
            mHead = node;
            node->mNext = nullptr;
        }
        else
        {
            node->mNext = mHead;
            mHead = node;
        }
    }

    Node *put(K key, V val)
    {
        Node *node = new Node(key, val);
        prepend(node);

        return node;
    }

    void reverse()
    {
        Node *p = mHead;
        mHead = nullptr;

        while(p)
        {
            Node *next = p->mNext;
            prepend(p);
            p = next;
        }
    }

    Node *mHead = nullptr;
};

template<class K, class V>
ostream& operator<<(ostream &os, const SequentialSearchST<K, V>& st)
{
    os << '[';

    auto iter = st.begin();

    //TODO: Why doesn't this work, and I had to use 'auto iter'
//    SequentialSearchST<K, V>::iterator iter = st.begin();
//    cout << typeid(iter).name() << endl;
    os << "(" << *iter << ", " << st[*iter] << ")";
    ++iter;

    for( ;iter != st.end(); ++iter )
    {
        os << " " << "(" << *iter << ", " << st[*iter] << ")";
    }

    os << ']';

    return os;
}

#endif /* SEQUENTIALSEARCHST_H_ */
