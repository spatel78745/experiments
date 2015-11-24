/*
 * misc.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: spatel78745
 */
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "Bst.h"
#include "FileBuffer.h"
#include "TcpSocketTest.h"

using namespace std;

class BoolFunc
{
public:
	template <class T>
	bool operator()(T q)
	{
		cout << q.size();
		return true;
	}
};

template<class T, class F = BoolFunc>
class QueueThread
{
public:
	QueueThread(T &q, F &postProcess, F &waitCondition);

private:
	std::thread mThread;
	F &mPostProcess;
	F &mWaitCondition;
	T &mQueue;
};

template<class T, class F>
QueueThread<T, F>::QueueThread(T &q, F &postProcess, F &waitCondition) :
		mPostProcess(postProcess), mWaitCondition(waitCondition), mQueue(q)
{
	mPostProcess(mQueue);
}

void testQueueThread()
{
	std::queue<int> q;
	BoolFunc preProcess, waitCondition;
	QueueThread<std::queue<int>> qt(q, preProcess, waitCondition);
}

template<typename T>
int compare(const T &v1, const T &v2)
{
	if (v1 < v2)
		return -1;
	// Why use '<' instead of '>'? Want to minimize the requirements on the types.
	// Think of the types of iterators: input, output, etc.
	if (v1 < v2)
		return 1;
	if (v1 == v2)
		return 0;
}

template<unsigned N, unsigned M>
int compares(const char (&p1)[N], const char (&p2)[M])
{
	return strcmp(p1, p2);
}

class NoCopy
{
	NoCopy(NoCopy& noCopy)
	{
	}
public:
	NoCopy()
	{
	}
};

void testNoCopy(NoCopy& nc)
{
}

template<typename elemType> class ListItem;
template<typename elemType> class List
{
public:
	List();
	List(const List&);
	~List();
	void insert(ListItem<elemType> *ptr, elemType value);
private:
	ListItem<elemType> *front, *end;
};

template<typename In, typename V>
In tfind(In b, In e, V v)
{
	for (; b != e; ++b)
	{
		if (*b == v)
		{
			return b;
		}
	}

	return e;
}

template<class T>
void tfind(vector<T>& v, T val)
{
	typename vector<T>::iterator iter;

	if ((iter = tfind(v.begin(), v.end(), val)) != v.end())
	{
		cout << "found: " << *iter << endl;
	}
	else
	{
		cout << "didn't find: " << val << endl;
	}
}

template<class T, unsigned N>
void print(const T (&a)[N])
{
	for (int i = 0; i < N; ++i)
	{
		cout << a[i] << " ";
	}

	cout << endl;
}

template<class T>
void print(T t)
{
	for(typename T::size_type i = 0; i < t.size(); ++i)
	{
		cout << t[i] << " " << endl;
	}
}

template<class T>
void print2(T t)
{
	for(typename T::const_iterator i = t.begin(); i != t.end(); ++i)
	{
		cout << t[i] << " " << endl;
	}
}


template<class T, unsigned N>
constexpr int array_size(const T (&a)[N])
{
	return N;
}

template<typename T>
typename T::value_type top(const T& c)
{
	if (!c.empty())
		return c.back();
	else
		return typename T::value_type();
}

template <typename T, typename U, typename V> void f1(T, U, V);
template <typename T> T f2(int &t);
template <typename T> T foo(T, unsigned int*);
template <typename T> T f4(T, T);
typedef char CType;
template <typename Ctype> Ctype f5(Ctype a);

void testPipe()
{
    int mypipe[2];
    if (pipe(mypipe))
    {
        cerr << "Failed to create pipe" << endl;
        return;
    }

    pid_t pid = fork();
    // TODO: should this be <static_cast>?
    if (pid == (pid_t)0)
    {
        close(mypipe[1]);
    }

}

int main()
{
	extern void testTree();
	extern void testNullFilterBuf();
	extern void testCharArrayBuffer();
	extern void testCapsBuffer();

	TcpSocketTest tcpSocketTest;

	tcpSocketTest.runAll();
}
