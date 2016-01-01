/*
 * SequentialSearchST.h
 *
 *  Created on: Dec 30, 2015
 *      Author: spatel78745
 */

#ifndef SEQUENTIALSEARCHST_H_
#define SEQUENTIALSEARCHST_H_

template <class T>
class SequentialSearchST
{
public:
    typedef size_t size_type;
    typedef T value_type;

public:
    SequentialSearchST();

    void put(T t)
    {

    }

    T& get()
    {

    }

private:
    class Node
    {
    public:
        Node(T data): mData(data) {}
    public:
        T mData;
        T *mNext = nullptr;
    };

private: // data
    Node *mHead = nullptr;
    size_type mSize = 0;
};

#endif /* SEQUENTIALSEARCHST_H_ */
