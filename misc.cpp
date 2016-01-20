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
#include <treeplot/TreePlotTest.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <ratio>
#include <functional>
#include "Bst.h"
#include "FileBuffer.h"
#include "TcpSocketTest.h"
#include "BstTest.h"
#include "SequentialSearchST.h"
#include "SequentialSearchSTTest.h"
#include "Hashtable.h"
#include "HashtableTest.h"
#include "HashtableLp.h"

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

void testRatio()
{
    /*
     * Ok, I'm going to convert the time unit of hs (half-seconds) to milliseconds using all this
     * duration and ratio non-sense.
     *
     * Now, I want to represent 3 hs, so it will be like this:
     * - Given that you make a duration-type like this: duration<int, ratio<seconds, ticks>,
     *  3 hs is duration<int, ratio<1, 2>> t(3)
     * - Given that you convert like this:
     *   output_duration = duration_cast<output_type> (input_duration)
     *   - and we have:
     *     - output_type = duration<int, ratio<1, 1000>)
     *     - input_duration = t
     *   - the conversion expression is:
     *     - duration_cast<duration<int, ratio<1, 1000>>>(t).count()
     *   - and the answer should be 1500
     */
    using namespace chrono;

    duration<int, ratio<1, 2>> t(3); // 3 hs
    int ms = duration_cast<duration<int, ratio<1, 1000>>>(t).count();
    cout << t.count() << "hs == " << ms;
}

template<class T>
class Dummy
{
public:
    Dummy(T data): mData(data) { cout << "constructing dummy" << endl; }
    T mData;
};

template<class T>
ostream& operator<<(ostream &os, const Dummy<T>& d)
{
    os << d.mData;
    return os;
}

int main()
{
    typedef HashtableLp<string, int> HtlpT;

    HtlpT htlp;

    htlp.put("Sameer", 44);         // 1
    htlp.put("Cthulu", 15000000);   // 2
    htlp.put("Mad Max", 35);        // 3
    htlp.put("Chuckie", 41);        // 4
    htlp.put("Pinhead", 3);         // 5
    htlp.put("Inspector Clouseau", 50); // 6
    htlp.put("Mr. Spock", 90); // 7
    htlp.put("Q", 35000); // 8
    htlp.put("Hannibal Lector", 51); // 9
    htlp.put("Boyd Crowder", 46); // 10
    htlp.put("Dewey Crowe", 40); // 11
    htlp.put("Stalin", 60); // 12
    htlp.put("Julius Caesar", 45); // 13

    htlp.dump("htlp");

//    try {
//        cout << "get Terminator T1000: " << htlp.get("Terminator T1000") << endl;
//    } catch (KeyNotFoundError& knfe) {
//        cout << "get failed, reason: " << knfe.what() << endl;
//    }
//    cout << "get Sameer: " << htlp.get("Sameer") << endl;

//    htlp.dump("htlp");
//    cout << "RESIZING" << endl;
//    htlp.resize(25);
//    htlp.dump("htlp");

//    HashtableLp<string, int> htlp2(900);
//
//    htlp.dump("htlp");
//    htlp2.dump("htlp2");
//
//    htlp2=htlp;
//    htlp2.dump("htlp2");

//    HashtableTest htTest;
//    htTest.runAll();

//    Hashtable<string, int> ht;
//
//    ht["Sameer"] = 44;
//    ht["John"] = 32;
//    ht["Rajiv"] = 80;
//    ht["Gordon"] = 100;
//    ht["Connor McCloud"] = 1500;
//    ht["Methuselah"] = 900;
//    ht["Cthulu"] = 100000;
//    ht["Cookie Monster"] = 10;
//    ht.keys();

//    SequentialSearchSTTest stTest;
//    stTest.runAll();

//    BstTest bstTest;
//    bstTest.runAll();
//    ss.put("john", 80);
//	TcpSocketTest tcpSocketTest;
//	tcpSocketTest.runAll();
//    TreePlotTest treePlotTest;
//    treePlotTest.runAll();
//    testRatio();
}
