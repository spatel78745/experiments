/*
 * FileBuffer.cpp
 *
 *  Created on: Nov 16, 2015
 *      Author: spatel78745
 */

#include "FileBuffer.h"

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/*
 * Things I learned:
 * - If you don't implement virtual methods, the compiler complains "missing vtbl"
 */
FileBuffer::FileBuffer(FILE *fp, size_t bufSize, size_t putBack) :
    mFp(fp), mPutBack(max(putBack, size_t(1))), mBuffer(max(bufSize, putBack) + putBack)
{
    char *end = &mBuffer.front() + mBuffer.size();
    setg(end, end, end);
}

/*
 * How does all this putback stuff work?
 *
 *
 */
streambuf::int_type FileBuffer::underflow()
{
    if (gptr() < egptr())
    {
        cerr << "gptr < egptr: returning" << *gptr() << endl;
        return traits_type::to_int_type(*gptr());
    }

    char *base = &mBuffer.front();
    char *start = base;

    /*
     * True when this isn't the first fill.
     * - Meaning that eback() == base iff we just constructed the FileBuffer
     */
    if (eback() == base)
    {
        memmove(base, egptr() - mPutBack, mPutBack);
        start += mPutBack;
    }

    size_t n = fread(start, 1, mBuffer.size() - (start - base), mFp);
    cerr << "read " << n << " characters" << endl;
    for(int i = 0; i != n; ++i)
    {
        cerr << start[i] << " ";
    }
    cerr << endl;
    if (n == 0)
    {
        return traits_type::eof();
        cerr << "returning EOF";
    }

    cerr << "returning *gptr() " << (int)*gptr() << endl;

    setg(base, start, start + n);

    return traits_type::to_int_type(*gptr());
}
