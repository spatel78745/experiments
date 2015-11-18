/*
 * testStreamBuf.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: spatel78745
 */
#include <iostream>
#include <streambuf>
#include <sstream>
#include "CharArrayBuffer.h"
#include "CapsBuffer.h"

using namespace std;

class NullFilterBuf : public streambuf
{
    streambuf *src;

    /*
     * A singlebyte buffer
     */
    char ch;
protected:
    int underflow()
    {
        bool debug = false;

        if (debug) cerr << "Enter underflow" << endl;
        /*
         * From the docs, sbumpc returns *current++
         *
         * Here's a sample implementation:
         * int sbumpc()
         * {
         *   - This is saying "get more characters if the buffer is empty"
         *   if ( !(gptr()) || (gptr() == egptr()) ) return uflow();
         *
         *   - This is a cool way of avoiding a temporary. You could've done this:
         *     - t = *gptr(); gbump(1); return t;
         *   gbump(1);
         *   return gptr()[-1];
         * }
         */
        while((ch = src->sbumpc()) == '\0')
            if (debug) cerr << ch << " is not 0" << endl;

        // set eback, gptr, egptr
        setg(&ch, &ch, &ch + 1);

        if (debug) cerr << "Exit underflow" << endl;

        return ch;
    }

public:
    NullFilterBuf(streambuf *buf) : src(buf)
    {
        /*
         * Make buffer initially full? Why?
         * - Full must mean eback == base address of the buffer
         * - Probably doesn't matter since all we need to provide is a character at gptr
         */
        setg(&ch, &ch + 1, &ch + 1);
    }
};

void filteredRead(istream& in)
{
    /*
     * The istream has an internal buffer. Create a NullFilterBuf out of it. NullFilterBuf
     * will use this as the source of bytes/stream.
     */
    streambuf *orig = in.rdbuf();
    NullFilterBuf buf(orig);
    in.rdbuf(&buf);

    cout << "Result of filtered read:" << endl;

    /*
     * This is very cool:
     * - See how the variable is defined but not initialized
     * - The loop ends when cout returns false. cout is false if c is EOF. c is EOF if
     *   in.get(c) puts EOF in c. in.get(c) puts EOF in c if underflow or uflow returns EOF
     */
    for(char c; in.get(c); cout << c);
    cout << endl;

    in.rdbuf(orig);
}

void testNullFilterBuf()
{
    char a[] = "This i\0s \0an e\0\0\0xample";
    /*
     * Here's a level one understanding of begin() and end()
     * - if "a" is a container, it returns a.begin()
     * - if "a" is an array, it returns the array-to-pointer conversion of its argument
     */
    istringstream in(string(begin(a), end(a)));
    filteredRead(in);
}

void testCharArrayBuffer()
{
    CharArrayBuffer sb("hello 20 3.14 world");
    istream is(&sb);
    if (!is) cerr << "Error on istream\n"; return;

    string hello, world;
    int twenty;
    double pi;

    is >> hello >> twenty >> pi >> world;

    cerr << "read: " << hello << " " << twenty << " " << pi << " " << world << " " << endl;
    if (is) cerr << "Still not at EOF\n";
    else    cerr << "At EOF\n";

    int dummy;
    is >> dummy;
    if (is) cerr << "Still not at EOF\n";
    else    cerr << "At EOF\n";

    cerr << "Exit testCharArrayBuffer" << endl;
}

void testCapsBuffer()
{
    string line;
    CapsBuffer cb(cout, 20);
    ostream os(&cb);

    for(;;)
    {
        string text;

        cerr << "Enter some text:" << endl;
        getline(cin, text);
        if (text.find("stop") != string::npos)
        {
            cerr << "Stopping..." << endl;
            break;
        }
        cerr << "You entered: " << text << endl;
        os << text;
    }
}
