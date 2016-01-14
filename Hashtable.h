/*
 * Hashtable.h
 *
 *  Created on: Dec 30, 2015
 *      Author: spatel78745
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <cstdlib>
#include <string>
#include <functional>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "SequentialSearchST.h"
#include "MyException.h"

using namespace std;


template <class K, class V, size_t initialSize=5>
class Hashtable
{
public:
    template<class K_, class V_>
    friend ostream& operator<<(ostream &os, const Hashtable<K_, V_>& ht);
    typedef SequentialSearchST<K, V> StT;
    typedef pair<K, V> pairT;

    class Iterator
    {
    public:
        typedef pair<K, V> pairT;

        StT *nextRow(StT *begin, StT *end)
        {
            StT *st;

            for(st = begin; st != end; ++st)
            {
                // TODO: Make size() constant time
                if (st->size() > 0) break;
            }

            return st;
        }

        Iterator(StT *begin, StT *end): mEnd(end)
        {
            mCurr = nextRow(begin, end);
            if (mCurr != end)
                mIter = mCurr->begin();
//            cout << __func__ << " mCurr " << mCurr << " mEnd " << mEnd << endl;
        }

        Iterator& operator++()
        {
            pair<K, V> before = mIter.getPair();

//            cout << "++ Enter" << endl;

            if (mCurr == mEnd)
            {
//                cout << "++ No more elements" << endl;
                return *this;
            }

            ++mIter;
            if (mIter == mCurr->end())
            {
                mCurr = nextRow(mCurr + 1, mEnd);
                if (mCurr == mEnd)
                {
//                    cout << "++ No more elements" << endl;
                    mIter = nullptr;
//                    cout << "++ assigned nullptr" << endl;
                    return *this;
                }

                mIter = mCurr->begin();
//                cout << "++ Wrap" << endl;
            }

            pair<K, V>  after = mIter.getPair();
//            cout << "++ before: " << before.first << ", " << before.second
//                 << " after: "    << after.first  << ", " << after.second << endl;

//            cout << "++ Exit" << endl;

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator current = *this;
            ++(*this);

            return current;
        }

        pairT operator*() const
        {
            return mIter.getPair();
        }

        bool operator==(const Iterator& other) const
        {
            return (other.mCurr == mCurr) && (other.mEnd == mEnd) && (other.mIter == mIter);
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
//
//        string toStr() const
//        {
//            stringstream ss;
//
//            ss << "mRow=" << mRow << " mCol=" << mCol;
//            return ss.str();
//        }

    private:
        StT *mCurr;
        StT *mEnd;
        typename StT::iterator mIter;
    };

    typedef size_t size_type;
    typedef Iterator iterator;

    Iterator begin()
    {
        if (size() == 0)
        {
//            cout << __func__ << " returning end(),  end() == end? " << (end() == end()) << endl;
            return end();
        }

        return Iterator(mSt, mSt + mM);
    }

    Iterator end() const { return Iterator(mSt + mM, mSt + mM); }

    Hashtable(): Hashtable(initialSize)
    {
    }

    Hashtable(size_type M): mM(M)
    {
        mSt = new SequentialSearchST<K, V>[M];
        cout << __func__ << ": Created hash table with M=" << M << endl;
    }

    Hashtable(const Hashtable &other): Hashtable(other.mM)
    {
        for(int i = 0; i != mM; ++i)
        {
            mSt[i] = other.mSt[i];
        }
    }

    Hashtable(initializer_list<pairT> lst): Hashtable()
    {
        for(pairT p: lst)
        {
            (*this)[p.first] = p.second;
        }
    }

    int size()
    {
        int sz = 0;

        for(int i = 0; i < mM; ++i)
        {
            sz += mSt[i].size();
        }

        return sz;
    }


    bool operator==(const Hashtable& other) const
    {
        if (size() != other.size() || mM != other.mM) return false;

        for(int i = 0; i != mM; ++i)
        {
            if (mSt[i] != other.mSt[i]) return false;
        }

        return true;
    }


    Hashtable& operator=(Hashtable rhs)
    {
        swap(this->mM, rhs.mM);
        swap(this->mSt, rhs.mSt);

        return *this;
    }

    V& operator[](K key)
    {
        return mSt[hash(key)][key];
    }

    V operator[](K key) const
    {
        return mSt[hash(key)][key];
    }

    ~Hashtable()
    {
        delete[] mSt;
    }

    void del(K key)
    {
        mSt[hash(key)].del(key);
    }

    void keys()
    {
        for(int i = 0; i < mM; ++i)
        {
            cout << __func__ << ": slot " << i;
            auto& st = mSt[i];
            for(auto& key: st)
            {
                cout << " (" << key << ") ";
            }
            cout << endl;
        }
    }

    void dump()
    {
        for (int i = 0; i < mM; ++i) {
            cout << i << ": " << mSt[i] << endl;
        }
    }

private:
    size_type hash(K& key)
    {
        return std::hash<K>()(string(key)) % mM;
    }

    size_type mM;
    SequentialSearchST<K, V> *mSt = nullptr;
};


// TODO: This is exactly the same function as the one in SequentialSearchST
// TODO: The hashtable argument should be a const...you need a const_iterator for Hashtable
template<class K, class V>
ostream& operator<<(ostream &os, Hashtable<K, V>& ht)
{
    os << '[';

    auto iter = ht.begin();

    typename Hashtable<K, V>::pairT elem;

    if (iter != ht.end())
    {
        elem = *iter;
        os << "(" << elem.first << ", " << elem.second << ")";
        ++iter;
    }

    for( ;iter != ht.end(); ++iter )
    {
        elem = *iter;
        os << " " << "(" << elem.first << ", " << elem.second << ")";
    }

    os << ']';

    return os;
}

#endif /* HASHTABLE_H_ */
