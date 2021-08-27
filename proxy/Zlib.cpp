#include "Zlib.h"
#include <iostream>
#include <assert.h>
#define INBUFSIZ   4096 
#define OUTBUFSIZ  4096
#define CHUNK (1024 * 256)

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
    } \
}

Zlib* instance;

Zlib::Zlib()
{
}
static alloc_func zalloc = (alloc_func)0;
static free_func zfree = (free_func)0;

void vucarrWrite(vucarr& out, const unsigned char* buf, size_t bufLen)
{
    out.insert(out.end(), buf, buf + bufLen);
}

size_t vucarrRead(const vucarr& in, unsigned char*& inBuf, size_t& inPosition)
{
    size_t from = inPosition;
    inBuf = const_cast<unsigned char*>(in.data()) + inPosition;
    inPosition += std::min((size_t)CHUNK, in.size() - from);
    return inPosition - from;
}

int Zlib::Inflate(const vucarr& in, vucarr& out) {
    int ret;
    unsigned have;
    z_stream strm = {};
    unsigned char* inBuf;
    unsigned char outBuf[CHUNK];

    size_t inPosition = 0; /* position indicator of "in" */

    /* allocate inflate state */
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = vucarrRead(in, inBuf, inPosition);

        if (strm.avail_in == 0)
            break;
        strm.next_in = inBuf;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = outBuf;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR); /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR; /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            vucarrWrite(out, outBuf, have);
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

Zlib::~Zlib()
{
}

Zlib* Zlib::getZlib() {
	if (!instance) {
		instance = new Zlib();
	}
	return instance;
}