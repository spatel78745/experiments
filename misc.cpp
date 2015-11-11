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
#include "Bst.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cerr;

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



void testTree()
{
	Bst<string, int> bst;

	bst.put("H", 1);
	bst.put("C", 2);
	bst.put("S", 3);
	bst.put("A", 4);
	bst.put("E", 5);
	bst.put("R", 6);
	bst.put("X", 7);
}

int main()
{

//	Node<string, int> nodeH("H", 1);
//	Node<string, int> nodeA("A", 1);
//
//	cout << "nodeH: " << nodeH.key() << endl;
//	cout << "nodeA: " << nodeA.key() << endl;
//
//	cout << "nodeH < nodeA: " << (nodeH < nodeA) << endl;
//	cout << "nodeA < nodeH: " << (nodeA < nodeH) << endl;

	testTree();

//	int a[3];
//
//	compare(&a, &a);

//	cout << compare(0, 1) << endl;
//	cout << compares("function", "function") << endl;
//	cout << compare("started", "finished") << endl;

//	NoCopy nc;
//	testNoCopy(nc);

//	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	vector<int> q;
//
//	cout << top(v) << endl;
//	cout << top(q) << endl;
//	tfind(v, 3);
//	tfind(v, 69);
//
//	double d[]{1.1, 2.2, 3.4, 4.4, 5.5};
//	int i[]{10, 11, 12, 13, 14, 15, 16, 17};
//
//	print(d);
//	print(i);
//
//	cout << "array d has " << array_size(d) << " elements" << endl;
//	cout << "array i has " << array_size(i) << " elements" << endl;

//	testQueueThread();
}
