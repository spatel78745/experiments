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
#include <memory>
#include "Bst.h"
#include "FileBuffer.h"
#include "TcpSocketTest.h"
#include "BstTest.h"
#include "SequentialSearchST.h"
#include "SequentialSearchSTTest.h"
#include "Hashtable.h"
#include "HashtableTest.h"
#include "HashtableLp.h"
#include "UniquePtr.h"

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


class Pair
{
public:
    Pair(string& first, string& second): mFirst(first), mSecond(second) {}
    ~Pair() { cout << "destruct Pair " << mFirst << " " << mSecond << endl; }
    string first() { return mFirst; }
    string second() { return mSecond; }

private:
    string mFirst;
    string mSecond;
};

class PairArray
{
public:
    PairArray(size_t size)
    {
        mPairArray.reset(new unique_ptr<Pair>[size]);
        cout << "Created an array of " << size << " Pairs" << endl;
    }

    void addPair(string first, string second)
    {
        mPairArray[mAvail++].reset(new Pair(first, second));
        cout << "Added " << first << ", " << second << ". Total elements " << mAvail << endl;
    }

    void dump()
    {
        for (int i = 0; i < mAvail; ++i)
        {
            cout << i << " " << mPairArray[i]->first() << endl;
        }
    }

    ~PairArray() { cout << "destruct PairArray. Total elements " << mAvail << endl; }

private:
    unique_ptr<unique_ptr<Pair> []> mPairArray;
    size_t mAvail = 0;
};

template<class T, unsigned N>
int arraySize(const T (&anArray)[N]) { return N; }

void orange(int (&a)[3])
{
    for (auto i: a) cout << i << endl;
}

void eatOrange()
{
    int bag[3]{1,2,3};

    orange(bag);
}

template<typename> class Plum;

template<typename U>
bool operator==(const U &lhs, const U &rhs)
{
    cout << "Testing equality of " << lhs.mColor << " " << rhs.mColor << endl;
    return lhs.mColor == rhs.mColor;
}

template<typename T>
class Plum
{
public:
    Plum(T color): mColor(color) {}
    template<typename U>
    friend bool operator==(const U &lhs, const U &rhs);

private:
    T mColor;
};

template <typename elemType> class __ListItem;
template <typename elemType> class __List
{
public:
    __List<elemType>();
    __List<elemType>(const List<elemType> &);
    __List<elemType>& operator=(const __List<elemType> &);
    ~__List();
    void insert(ListItem<elemType> *ptr, elemType value);
};

template<typename T>
class Cherry
{
public:
//    typedef size_t size_type;
    typedef T value_type;
    static double tartness;
};

template<typename T>
double Cherry<T>::tartness = 0.0;

template <typename T>
typename T::value_type foo() { typename T::value_type x = 100; return x; }

template <typename T, typename U, typename V> void f1(T, U, V);
//template <typename T> T f2(int &T);
template <typename T> T f2(int &u);
/*inline*/ template <typename T> T foo(T, unsigned int*);
template <typename T> void f4(T, T);
typedef char Ctype;
template <typename Ctype> Ctype f5(Ctype a);

int add5(int n) { return n + 5; }

void callFuncThroughRef(int (&func)(int))
{
    cout << func(5) << endl;
}

class Raisin
{
public:
    Raisin(string descr): mDescr(descr) {};
    ~Raisin() { cout << __func__ << " destroying " << mDescr << endl; }

    string color() { return mDescr; }
    string good() { return mDescr + " is good!"; }

private:
    string mDescr;
};

void passByValue(UniquePtr<Raisin> up)
{
    cout << up.get() << endl;
}


void testUniquePointer()
{
    UniquePtr<Raisin> r1{};
    cout << __func__ << " r1 = " << r1.get() << endl;

    UniquePtr<Raisin> r2{new Raisin("white")};
    cout << __func__ << " r2 = " << r2.get() << endl;

    Raisin *black = new Raisin("black");
    UniquePtr<Raisin> r3{black};
    cout << __func__ << " r3 = " << r3.get() << endl;
    cout << __func__ << " " << (*r3).color() << endl;
    cout << __func__ << " " << r3->good() << endl;

    Raisin *green = new Raisin("green");
    UniquePtr<Raisin> r4{green};
    cout << __func__ << " r4 = " << r3.get() << endl;

    cout << __func__ << "Swapping r3 and r4" << endl;
    cout << __func__ << "Before r3 " << r3.get() << " r4 " << r4.get() << endl;
    r3.swap(r4);
    cout << __func__ << "After r3 " << r3.get() << " r4 " << r4.get() << endl;

//    UniquePtr<Raisin, MyDeleter<Raisin>> r5{new Raisin("blue")};

//    UniquePtr<Raisin> rNull;
//    cout << "rNull " << (bool) rNull << endl;
//    cout << "r2 " << (bool)r2 << endl;
//    if (!rNull) cout << "rNull is null" << endl;
//    if (r2) cout << "r2 is not null" << endl;

//    Raisin *purple = new Raisin("purple");
//    cout << __func__ << "Resetting green to purple" << endl;
//    r4.reset(purple);

//    black = nullptr;
//    black = r3.release();
//    delete black;

//    try
//    {
//        UniquePtr<Raisin> r4{black};
//    }
//    catch(invalid_argument &ia)
//    {
//        cout << __func__ << "Failed to create unique ptr: " << ia.what() << endl;
//    }

//    passByValue(r3);
//    UniquePtr<Raisin> aCopy = r1;
}

void testVecOfPointers()
{
//    vector<void *> v;
//    Raisin *p;
//    find(begin(v), end(v), p) != end(v);

//    vector<int *> w;
//    int *i;
//    find(begin(w), end(w), i) != end(w);
}

int main()
{
    testUniquePointer();
//    callFuncThroughRef(add5);
//    Cherry<double> floatingCherry;
//    Cherry<double>::value_type x = 10.0;
//    cout << foo<Cherry<double>>() << endl;

//    Plum<string> purplePlum1{"purple"};
//    Plum<string> purplePlum2{"purple"};
//    Plum<string> redPlum{"red"};
//
//    cout << (purplePlum1 == purplePlum2) << endl;
//    cout << (purplePlum1 == redPlum) << endl;
//

//    eatOrange();

//    double d[100];
//    cout << arraySize(d) << endl;

//    constexpr int i = getVal<5>();
//    cout << i << endl;
//    PairArray pa(50);
//    pa.addPair("key1", "val1");
//    pa.addPair("key2", "val2");
//    pa.addPair("key3", "val3");
//    pa.addPair("key4", "val4");
//    pa.addPair("key5", "val5");
//    pa.addPair("key6", "val6");
//    pa.addPair("key7", "val7");

//    typedef HashtableLp<string, int> HtlpT;

//    cout << "Hello" << endl;

//    const HtlpT htc({
//    { "Sameer", 44 },         // 1
//    { "Cthulu", 15000000 },   // 2
//    { "Mad Max", 35 },        // 3
//    { "Chuckie", 41 },        // 4
//    { "Pinhead", 3 },         // 5
//    { "Inspector Clouseau", 50 }, // 6
//    { "Mr. Spock", 90 }, // 7
//    { "Q", 35000 }, // 8
//    { "Hannibal Lector", 51 }, // 9
//    { "Boyd Crowder", 46 }, // 10
//    { "Dewey Crowe", 40 }, // 11
//    { "Stalin", 60 }, // 12
//    { "Julius Caesar", 45 }, // 13
//    });

//    htc.dump("htc");
//    cout << "Stalin's old age " << htc.get("Stalin") << endl;
//    int& v1 = htc.get("Stalin");
//    v1 = 70;
//    cout << "Stalin's new age " << htc.get("Stalin") << endl;
//
////    htc["Stalin"] = 80; // Can't do it because the const version returns a const reference
//    cout << "Stalin's age via [] " << htc["Stalin"] << endl;


//    HtlpT htlp;

//    htlp.put("Sameer", 44);         // 1
//    htlp.put("Cthulu", 15000000);   // 2
//    htlp.put("Mad Max", 35);        // 3
//    htlp.put("Chuckie", 41);        // 4
//    htlp.put("Pinhead", 3);         // 5
//    htlp.put("Inspector Clouseau", 50); // 6
//    htlp.put("Mr. Spock", 90); // 7
//    htlp.put("Q", 35000); // 8
//    htlp.put("Hannibal Lector", 51); // 9
//    htlp.put("Boyd Crowder", 46); // 10
//    htlp.put("Dewey Crowe", 40); // 11
//    htlp.put("Stalin", 60); // 12
//    htlp.put("Julius Caesar", 45); // 13

//    HtlpT htlp({
//    { "Sameer", 44 },         // 1
//    { "Cthulu", 15000000 },   // 2
//    { "Mad Max", 35 },        // 3
//    { "Chuckie", 41 },        // 4
//    { "Pinhead", 3 },         // 5
//    { "Inspector Clouseau", 50 }, // 6
//    { "Mr. Spock", 90 }, // 7
//    { "Q", 35000 }, // 8
//    { "Hannibal Lector", 51 }, // 9
//    { "Boyd Crowder", 46 }, // 10
//    { "Dewey Crowe", 40 }, // 11
//    { "Stalin", 60 }, // 12
//    { "Julius Caesar", 45 }, // 13
//    });
//
//    htlp.dump("htlp");
//    cout << "Stalin's old age via [] " << htlp["Stalin"] << endl;
//    cout << "Changed Stalin's age via [] " << endl;
//    htlp["Stalin"] = 80;
//    cout << "Stalin's new age via [] " << htlp["Stalin"] << endl;
//
//    cout << "Add an element via []" << endl;
//    htlp["Marvin"] = 5;
//    cout << "Marvin's age via [] " << htlp["Marvin"] << endl;
//    htlp.dump("htlp add Marvin");

//
//    cout << "Stalin's old age " << htlp.get("Stalin") << endl;
//    int& v1 = htlp.get("Stalin");
//    v1 = 70;
//    cout << "Stalin's new age " << htlp.get("Stalin") << endl;

//    cout << "contains Boyd Crowder " << htlp.contains("Boyd Crowder") << endl;
//    cout << "contains Mr. Spock " << htlp.contains("Mr. Spock") << endl;
//    cout << "contains Pee Wee Herman " << htlp.contains("Pee Wee Herman") << endl;

//    htlp.del("Boyd Crowder");
//    htlp.dump("delete Boyd Crowder");
//    htlp.del("Dewey Crowe");
//    htlp.dump("delete Dewey Crowe");


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
