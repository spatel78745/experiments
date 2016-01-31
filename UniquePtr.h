/*
 * UniquePtr.h
 *
 *  Created on: Jan 30, 2016
 *      Author: spatel78745
 */

#ifndef UNIQUEPTR_H_
#define UNIQUEPTR_H_

#include <vector>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
struct MyDeleter
{
    void operator()(T *ptr)
    {
        cout << "MyDeleter deleting " << ptr << endl;
        delete ptr;
    }
};

template<typename P, typename Deleter = MyDeleter<P>>
class UniquePtr
{
//    friend void testUniquePointer();
public:
    explicit UniquePtr(P *ptr = nullptr);
    virtual ~UniquePtr();
    UniquePtr(const UniquePtr&) = delete;

    operator bool() const { return mPtr != nullptr; }
    P& operator*() const { return *mPtr; }
    P* operator->() const { return mPtr; }

    P *get() const { return mPtr; }
    P *release();
    void reset(P *newPtr = nullptr);
    void swap(UniquePtr &other);

private:
    P *mPtr;
    static vector<const void *> mUniquePtrs;

private:
    static void own(const P *ptr);
    static void disown(const P *ptr);
};

template<typename P, typename Deleter>
vector <const void *> UniquePtr<P, Deleter>::mUniquePtrs{};

template<typename P, typename Deleter>
void UniquePtr<P, Deleter>::own(const P *ptr)
{
    if (ptr == nullptr) return;

    if (find(begin(mUniquePtrs), end(mUniquePtrs), ptr) != end(mUniquePtrs))
        throw invalid_argument("Pointer is not unique");

    mUniquePtrs.push_back(ptr);
}

template<typename P, typename Deleter>
void UniquePtr<P, Deleter>::disown(const P *ptr)
{
    if (ptr == nullptr) return;

    auto iter = find(begin(mUniquePtrs), end(mUniquePtrs), ptr);

    if (iter == end(mUniquePtrs))
        throw invalid_argument("Pointer not found");

    mUniquePtrs.erase(iter);
}

template<typename P, typename Deleter>
UniquePtr<P, Deleter>::UniquePtr(P *ptr): mPtr(ptr)
{
    own(mPtr);
}

template<typename P, typename Deleter>
P *UniquePtr<P, Deleter>::release()
{
    disown(mPtr);

    auto tmp = mPtr;
    mPtr = nullptr;

    return tmp;
}

template<typename P, typename Deleter>
void UniquePtr<P, Deleter>::reset(P *newPtr)
{
    disown(mPtr);

    Deleter()(mPtr);

    own(newPtr);
    mPtr = newPtr;
}

template<typename P, typename Deleter>
void UniquePtr<P, Deleter>::swap(UniquePtr &other)
{
    auto tmp = mPtr;
    mPtr = other.mPtr;
    other.mPtr = tmp;
}

template<typename P, typename Deleter>
UniquePtr<P, Deleter>::~UniquePtr()
{
    reset();
}

#endif /* UNIQUEPTR_H_ */
