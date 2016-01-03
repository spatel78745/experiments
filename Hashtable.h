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
    typedef size_t size_type;

    Hashtable(): Hashtable(initialSize)
    {
    }

    Hashtable(size_type M): mM(M)
    {
        mSt = new SequentialSearchST<K, V>[M];
        cout << __func__ << ": Created hash table with M=" << M << endl;
    }

    V& operator[](K key)
    {
        size_type slot{hash(key)};
        SequentialSearchST<K, V>& st{ mSt[slot] };

//        cout << __func__ << ": slot=" << slot << " st[" << key << "]=" << st[key] << endl;

        return st[key];
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

    size_type mN{0};
    size_type mM;
    SequentialSearchST<K, V> *mSt = nullptr;
};

//template<class K, class V>
//ostream& operator<<(ostream &os, SequentialSearchST<K, V>& st)
//{
//    os << '[';
//
//    auto iter = st.begin();
//
//    //TODO: Why doesn't this work, and I had to use 'auto iter'
////    SequentialSearchST<K, V>::iterator iter = st.begin();
////    cout << typeid(iter).name() << endl;
//    os << "(" << *iter << ", " << st[*iter] << ")";
//    ++iter;
//
//    for( ;iter != st.end(); ++iter )
//    {
//        os << " " << "(" << *iter << ", " << st[*iter] << ")";
//    }
//
//    os << ']';
//
//    return os;
//}

#endif /* HASHTABLE_H_ */
