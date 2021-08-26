#pragma once
#include <zlib.h>
#include <zconf.h>
#include <Windows.h>
class Zlib
{
	Zlib();
	~Zlib();
public:
	static Zlib* getZlib();
	bool Inflate(const BYTE* const pDataIn,DWORD& dataInSize,BYTE* pDataOut,DWORD& dataOutSize);
private:
	z_stream m_stream;
};