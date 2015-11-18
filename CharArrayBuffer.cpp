/*
 * CharArrayBuffer.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: spatel78745
 */

#include <functional>
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "CharArrayBuffer.h"

using namespace std;

/*
 * Things I learned:
 * - There are parameterized function objects for relations (see below)
 * - Remember to use "assert"
 * - Remember that you can do ptr[-1]!! This should be most pleasing to you since you like
 *   stupid pointer tricks.
 */
CharArrayBuffer::CharArrayBuffer(const char *begin, const char *end):
        mBegin(begin),
        mEnd(end),
        mCurrent(begin)
{
    /*
     * less_equal is a function object:
     * template <class T> struct less_equal : binary_function <T, T, bool>
     * {
     *   bool operator() (const T& x, const T& y) const { return x <= y; }
     * }
     *
     * Chose not to go down the "binary_function" rat hole. It's deprecated in C++11
     */
    assert(less_equal<const char *>()(mBegin, mEnd));
}

CharArrayBuffer::CharArrayBuffer(const char *str):
        mBegin(str),
        mEnd(mBegin + strlen(str)),
        mCurrent(mBegin)
{
    if (debug) fprintf(stderr, "mBegin = %p, mEnd = %p, *mBegin = %s", mBegin, mEnd, mBegin);
}

CharArrayBuffer::int_type CharArrayBuffer::underflow()
{
    if (mCurrent == mEnd)
    {
        if (debug) cerr << "underflow: mCurrent == mEnd: returning EOF" << endl;
        return traits_type::eof();
    }

    /*
     * Now what is this "to_int_type"?
     * - traits_type is char_traits<char>
     * - char_traits<char> typedef char char_type
     * - static constexpr int_type to_int_type(char_type c) no except // whew!!
     *   obviously converts the char_type to an int_type
     */
    if (debug) cerr << "underflow: returning " << *mCurrent << endl;
    return traits_type::to_int_type(*mCurrent);
}

/*
 * The default implementation does this:
 * int uflow()
 * {
 *   if (underflow() == EOF) return EOF;
 *   gbump(1); //  gptr++
 *   return gptr()[-1];
 * }
 *
 * Why can't we use this? Cuz look at underflow: it's not updating gptr. We're not using gptr,
 * so we can't use the default implementation. It's quite a s simple as that. Mr. Edd says
 * "the need to override uflow() typically arises in stream buffers that don't use a writeable
 * array for intermediate storage.
 *
 * You need to read more of this guy's code...
 */
CharArrayBuffer::int_type CharArrayBuffer::uflow()
{
    if (mCurrent == mEnd)
    {
        if (debug) cerr << "uflow: mCurrent == mEnd: returning EOF" << endl;
        return traits_type::eof();
    }

    if (debug) cerr << "uflow: returning " << *mCurrent << endl;
    return traits_type::to_int_type(*mCurrent++);
}

/*
 * - The docs say "put ch back in the controlled input sequence and --gptr."
 *   - This is probably what the default it supposed to do.
 * - "called when there are no putback positions available"
 *   - This probably means eback() == gptr(). Mr. Edd says that this will always be the case in
 *     this example because we don't use setg() to change them, and by default they are set to zero.
 * - "or when the character being put back does not match the one in the buffer"
 *   - The pushback area is less then eback(). We don't have a writeable pushback area. If you
 *   try to pushback a character that you just read, we can make it work by decrementing current.
 *   If you try to pushback a character that's not in the stream, you can't do it because the
 *   memory is read-only. Yes yes, this is clearly level one understanding. But good enough of a
 *   gloss for now. We can move on.
 * - Mr. Edd says that this function is called as a "last-resort" to pushback a character, if all
 *   other methods fail. What other methods? Let's stick with this level 1 understanding.
 */
CharArrayBuffer::int_type CharArrayBuffer::pbackfail(int_type ch)
{
    /*
     * - If mCurrent == mBegin, we can't decrement mCurrent, so fail.
     * - If we're trying to pushback eof (why the hell would you do that?), then fail
     * - If you're trying to pushback any character other than the one you just read, then fail
     */
    if (mCurrent == mBegin || (ch != traits_type::eof() && ch != mCurrent[-1]))
        return traits_type::eof();

    return traits_type::to_int_type(*--mCurrent);
}

/*
 * - "streamsize represents sizes and character counts in streams"
 * - Defined in ios, iostream
 * - This guy's called by "in_avail()":
 *   - "If gptr < egptr, returns egptr - gptr"
 *   - If not, calls showmanyc to do this dirty work.
 *   - Now in our case, gptr == egptr always and forever, so we'll always end-up here in
 *     showmanyc(). Mr. Edd says it's "polite" to override this member.
 */
streamsize CharArrayBuffer::showmanyc()
{
    assert(less_equal<const char *>()(mCurrent, mEnd));
    return mEnd - mCurrent;
}
