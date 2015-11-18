/*
 * CapsBuffer.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: spatel78745
 */

#include <cctype>
#include <ostream>
#include <functional>
#include <cassert>
#include <iostream>
#include "CapsBuffer.h"

using namespace std;

/*
 * Things I learned:
 * - Default argument values must be specified in the declaration. If you put it here i.e.
 *   buffSize = 256, it won't work
 */
CapsBuffer::CapsBuffer(ostream& sink, size_t buffSize):
        mCapNext(true),
        mSink(sink),
        mBuffer(buffSize + 1) // Minimum buffer size is 1
{
    mSink.clear();
    char *base = &mBuffer.front();

    /*
     * Set (pbase, epptr). See overflow() to understand the " - 1"
     *
     */
    setp(base, base + mBuffer.size() - 1);
}

CapsBuffer::int_type CapsBuffer::overflow(int_type ch)
{
    if (debug) cerr << "Enter overflow" << endl;
    /*
     * TODO: is it really necessary to use less_equal vs. "<=" on a pointer compare?
     */
    assert(std::less_equal<char *>()(pptr(), epptr()));

    /*
     * Because we did "- 1" in the setp call in the ctor, *pptr() always points to valid memory.
     */
    *pptr() = ch;
    pbump(1);
    if (doCapsAndFlush())
    {
        if (debug) cerr << "Exit overflow after doCapsAndFlush()" << endl;
        return ch;
    }

    if (debug) cerr << "Exit overflow. Returning EOF" << endl;
    return traits_type::eof();
}

int CapsBuffer::sync()
{
    return doCapsAndFlush() ? 0 : -1;
}

bool CapsBuffer::doCapsAndFlush()
{
    for (char *p = pbase(), *e = pptr(); p != e; ++p)
    {
        if (*p == '.')
            mCapNext = true;
        else if (isalpha(*p))
        {
            if (mCapNext)
                *p = toupper(*p);

            mCapNext = false;
        }
    }
    ptrdiff_t n = pptr() - pbase();
    pbump(-n);

    /*
     * Most puzzling: I can't just return mSink.write(pbase(), n). See below: I use it as a bool
     * to convert it to a bool. WTF?
     */
    return mSink.write(pbase(), n) ? true : false;
}
