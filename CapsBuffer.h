/*
 * CapsBuffer.h
 *
 *  Created on: Nov 17, 2015
 *      Author: spatel78745
 */

#ifndef CAPSBUFFER_H_
#define CAPSBUFFER_H_

#include <streambuf>
#include <cstdlib>
#include <vector>

using namespace std;

class CapsBuffer : public streambuf
{
public:
    explicit CapsBuffer(ostream& sink, size_t buffSize = 256);

protected:
    bool doCapsAndFlush();

private:
    /*
     * Here's what the documentation says:
     * - Called by other methods (e.g. sputc) to put a character into the controlled output
     *   sequence when writing positions are unavailable i.e. pptr == epptr
     *   - The "controlled output sequence" must be the R/W buffer and not the write-only
     *     sequence i.e. stream that's the final destination for the character
     * - Default behaviour: return EOF i.e. failure
     * - If successful, returns the "ch" otherwise returns EOF
     *
     * Now let's take a look at what int sputc(c) does:
     * int sputc(char c) {
     *   if ((!pptr()) || (pptr() == epptr())) return overflow;
     *   *pptr() = c;
     *   pbump(1);
     *   return c;
     *
     *   EZ PZ!!
     */
    int_type overflow(int_type ch);

    /*
     * And now the mighty sync:
     * - Called by "pubsync" to synchronize the buffer with the stream. Probably aka "flush".
     *   If successful, returns 0, otherwise returns -1.
     * - pubsync() simply calls sync. I guess its purpose is to provide a function that
     *   clients can call, though this is puzzling -- why not make sync() public?
     */
    int sync();

    CapsBuffer(const CapsBuffer&);
    CapsBuffer &operator=(const CapsBuffer&);

private:
    bool mCapNext;
    ostream& mSink;
    vector<char> mBuffer;
    bool debug = false;
};

#endif /* CAPSBUFFER_H_ */
