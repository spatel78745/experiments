/*
 * Hashtable.h
 *
 *  Created on: Dec 30, 2015
 *      Author: spatel78745
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

template <class K, class V>
class Hashtable
{
public:
    typedef K* iterator;
    typedef const K* const_iterator;
    typedef size_t size_type;
    typedef V value_type;

public:
    Hashtable() { Hashtable(997); }
    explicit Hashtable(size_type M)

private:
    size_type mM;
    V* mData;
    V* mLimit;
};

#endif /* HASHTABLE_H_ */
