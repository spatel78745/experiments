/*
 * HashtableLp.h
 *
 *  Created on: Jan 18, 2016
 *      Author: spatel78745
 */

#ifndef HASHTABLELP_H_
#define HASHTABLELP_H_

#include <iostream>

using namespace std;

class KeyNotFoundError : public std::logic_error
{
public:
    KeyNotFoundError(const char * what) : logic_error(what) {}
};


template<class K, class V>
class HashtableLp
{
public:

    typedef size_t size_type;
    typedef V value_type;
    typedef K key_type;
    typedef pair<K, V> pair_type;
    typedef pair_type *iterator;
    typedef const pair_type *const_iterator;

    HashtableLp(const HashtableLp& other);
    HashtableLp(size_type initialSize = M_DEFAULT_SIZE);
    HashtableLp& operator=(HashtableLp rhs);

    iterator begin() {};
    iterator end() {};
    const_iterator begin() const {};
    const_iterator end() const {};

    const pair_type& operator[](size_type i) const {};
    pair_type& operator[](size_type i) {}

    void dump(const string& header) const;

private:
    static const size_type M_DEFAULT_SIZE = 1;
    size_type mM;
    size_type mSize = 0;
    pair_type **mData = nullptr;
    size_type *mCluster;

    size_type hash(K key) { return std::hash<K>()(key) % mM; }

// TODO: make private
public:
    void put(const K& key, const V& val);
    V& get(const K& key);
    void resize(size_type newSize);
};

template<class K, class V>
HashtableLp<K, V>::HashtableLp(size_type initialSize): mM{initialSize}
{
    mData = new pair_type*[mM]{};
    mCluster = new size_type[mM]{};
}

template<class K, class V>
HashtableLp<K, V>::HashtableLp(const HashtableLp& other)
{
    mM = other.mM;
}

template<class K, class V>
HashtableLp<K, V>& HashtableLp<K, V>::operator=(HashtableLp rhs)
{
    swap(mM, rhs.mM);

    return *this;
}

template<class K, class V>
void HashtableLp<K, V>::put(const K& key, const V& val)
{
    // TODO: remove when resize complete
    if (mSize == mM)
    {
        cout << "Table full cannot insert " << key << " " << val << endl;
        return;
    }

    if (mSize >= mM / 2) resize(mM * 2);

    size_type h = hash(key);
    for (int i = h; ; i = (i + 1) % mM)
    {
        if (mData[i] == nullptr)
        {
            mData[i] = new pair_type{key, val};
            cout << "hash " << h << " slot " << i << " inserted " << mData[i]->first << " " << mData[i]->second << endl;
            ++mSize;
            mCluster[h]++;
            return;
        }

        if (mData[i]->first == key)
        {
            mData[i]->second = val;
            cout << "slot " << i << " updated " << mData[i]->first << " " << mData[i]->second << endl;
            return;
        }
    }
}

template<class K, class V>
V& HashtableLp<K, V>::get(const K& key)
{
    // TODO: same code in put(): factor out
    for (int i = hash(key); ; i = (i + 1) % mM)
    {
        if (mData[i] == nullptr) throw KeyNotFoundError("No such key");
        if (mData[i]->first == key) return mData[i]->second;
    }
}

template<class K, class V>
void HashtableLp<K, V>::dump(const string& header) const
{
    cout << header << endl;
    cout << "mM: " << mM << endl;
    cout << "mSize: " << mSize << endl;

    double total = 0;
    int min = mCluster[0];
    int max = mCluster[0];
    for (size_type i = 0; i < mM; ++i) {
        cout << "cluster " << i << " " << mCluster[i] << endl;
        if (mData[i] == nullptr) cout << "data " << i << " null" << endl;
        else                     cout << "data " << i << mData[i]->first << " " << mData[i]->second << endl;
        total += mCluster[i];
        if (mCluster[i] < min) min = mCluster[i];
        if (mCluster[i] > max) max = mCluster[i];
    }
    cout << "average cluster " << total / mM << endl;
    cout << "min cluster " << min << endl;
    cout << "max cluster " << max << endl;

    for (size_type i = 0; i < mM; ++i) {
        if (mData[i] == nullptr) cout << "data " << i << " null" << endl;
        else                     cout << "data " << i << " " << mData[i]->first << " " << mData[i]->second << endl;
    }
}

template<class K, class V>
void HashtableLp<K, V>::resize(size_type newSize)
{
    HashtableLp htNew(newSize);


//    htNew.dump("resizing: htNew");
    for (int i = 0; i < mM; ++i) {
        if (mData[i] != nullptr)
        {
            htNew.put(mData[i]->first, mData[i]->second);
        }
    }

    swap(mM, htNew.mM);
    swap(mSize, htNew.mSize);
    swap(mData, htNew.mData);
    swap(mCluster, htNew.mCluster);
}

#endif /* HASHTABLELP_H_ */