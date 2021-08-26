#include "Zlib.h"
#include <iostream>
#define INBUFSIZ   4096 
#define OUTBUFSIZ  4096

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

bool Zlib::Inflate(
    const BYTE* const pDataIn,
    DWORD& dataInSize,
    BYTE* pDataOut,
    DWORD& dataOutSize)
{
    if (pDataIn)
    {
        if (m_stream.avail_in == 0)
        {
            m_stream.avail_in = dataInSize;
            m_stream.next_in = const_cast<BYTE* const>(pDataIn);
        }
        else
        {
            return false;
        }
    }

    m_stream.avail_out = dataOutSize;
    m_stream.next_out = pDataOut;

    bool done = false;

    do
    {
        int result = inflate(&m_stream, Z_BLOCK);

        if (result < 0)
        {
            printf("CDataInflator::Inflate()");
            break;
        }

        done = (m_stream.avail_in == 0 ||
            (dataOutSize != m_stream.avail_out &&
                m_stream.avail_out != 0));
    }    while (!done && m_stream.avail_out == dataOutSize);

    dataInSize = m_stream.avail_in;

    dataOutSize = dataOutSize - m_stream.avail_out;

    return done;
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