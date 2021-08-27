#include "Zlib.h"
#include <iostream>
#include <assert.h>
#define INBUFSIZ   4096 
#define OUTBUFSIZ  4096
#define CHUNK  4096

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
    } \
}

Zlib* instance;

Zlib::Zlib()
{
    m_stream.zalloc = Z_NULL;
    m_stream.zfree = Z_NULL;
    m_stream.opaque = Z_NULL;

    // èâä˙âª
    m_stream.next_in = Z_NULL;
    m_stream.avail_in = 0;
    if (inflateInit(&m_stream) != Z_OK) {
        printf("Fuckin zlib");
    }
}
static alloc_func zalloc = (alloc_func)0;
static free_func zfree = (free_func)0;
void Zlib::Inflate(Byte* compr, uLong comprLen, Byte* uncompr, uLong uncomprLen) {
    int err = uncompress(uncompr, &uncomprLen, compr, comprLen);
    //CHECK_ERR(err, "uncompress");
    std::cout << err << std::endl;
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