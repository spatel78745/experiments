/*
 * CharArrayBuffer.h
 *
 *  Created on: Nov 17, 2015
 *      Author: spatel78745
 */

#ifndef CHARARRAYBUFFER_H_
#define CHARARRAYBUFFER_H_

#include <streambuf>

using namespace std;

/*
 * Things I learned:
 * - I like how he's using multiple access specifiers to delimit methods from data
 * - "streambuf" is typedef basic_streambuf<char> streambuf
 * - streambuf works like this: [stream] <=> [streambuf] <=> [some read-once source of bytes]
 *   - [some read-once source of bytes] is the "controlled input sequence"
 * - You can disallow copying and assignment by making these methods/ctors private
 *
 * Let's take a look at traits (a level 1 understanding):
 * template <class CharT> class char_traits gives you some types related to CharT. For example,
 * if set CharT=char i.e. traits = char_traits<char>, you get:
 * - char_type == CharT == char
 * - int_type == an integer type that can hold all values of char_type plus EOF
 * - off_type, post_type, state_type == "implementation defined WTF man"
 *
 * Streambuf example: reading from an array of bytes in memory.
 */
class CharArrayBuffer : streambuf
{
public:
    CharArrayBuffer(const char *begin, const char *end);
    explicit CharArrayBuffer(const char *str);
private:
    /*
     *  - If there's a character at gptr, returns it, otherwise returns traits_type::eof()
     *  - The subclass refills the buffer is empty
     *  - Called by other member functions (e.g. sgetc) when there's nothing to read at gptr
     *    (probably meaning that gptr == egptr)
     */
    int_type underflow();

    /*
     * - Like underflow except it advances gptr
     * - Called by member functions like sbumpc when there's nothing to read at gptr.
     * - So what's the difference between sgetc and sbumpc?
     */
    int_type uflow();

    /*
     * - Puts a character back in the controlled input sequence and decrements gptr.
     * - Still mysterious
     */
    int_type pbackfail(int_type ch);

    /*
     * - Returns ">0" if there are characters available, "0" if it can't tell, "-1" meaning
     *   sequence unavailable.
     * - Provides information to callers on the possible behaviour of uflow and underflow
     * - Still mysterious
     */
    streamsize showmanyc();

private:
    const char * const mBegin;
    const char * const mEnd;
    const char * mCurrent;
};

#endif /* CHARARRAYBUFFER_H_ */
