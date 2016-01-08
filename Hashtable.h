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
#include "SequentialSearchST.h"

using namespace std;

template <class K, class V, size_t initialSize=5>
class Hashtable
{
public:
    template<class K_, class V_>
    friend ostream& operator<<(ostream &os, const Hashtable<K_, V_>& ht);

    typedef size_t size_type;

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

private:
    size_type hash(K& key)
    {
        return std::hash<K>()(string(key)) % mM;
    }

    size_type mM;
    SequentialSearchST<K, V> *mSt = nullptr;
};

template<class K, class V>
ostream& operator<<(ostream &os, const Hashtable<K, V>& ht)
{
    cout << "mM = " << ht.mM << endl;
    for(int i = 0; i != ht.mM; ++i)
    {
//        int size = ht.mSt[i].size();
//        if (size != 0) cout << i << ":" << ht.mSt[i] << endl;
        cout << i << ":" << ht.mSt[i] << endl;
    }

    return os;
}

#endif /* HASHTABLE_H_ */
