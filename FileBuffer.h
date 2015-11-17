/*
 * FileBuffer.h
 *
 *  Created on: Nov 16, 2015
 *      Author: spatel78745
 */

#include <streambuf>
#include <vector>
#include <cstdlib>
#include <cstdio>

#ifndef FILEBUFFER_H_
#define FILEBUFFER_H_

using namespace std;

class FileBuffer : public streambuf
{
public:
    explicit FileBuffer(FILE *fp, size_t bufSize = 256, size_t putBack = 8);

private:
    /*
     * Things I learned:
     * Overrides base class underflow()
     * - int_type is an integer type large enough to hold any character and traits_type::eof()
     */
    int_type underflow();

    /*
     * Forbid assignment and copying
     */
    FileBuffer(const FileBuffer &);
    FileBuffer& operator=(const FileBuffer &);

private:
    FILE *mFp;
    const size_t mPutBack;
    vector<char> mBuffer;
};

#endif /* FILEBUFFER_H_ */
