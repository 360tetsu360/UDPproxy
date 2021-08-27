#pragma once
#include <zlib.h>
#include <zconf.h>
#include <Windows.h>
#include <vector>
class Zlib
{
	Zlib();
	~Zlib();
public:
	static Zlib* getZlib();
	void Inflate(Byte* compr, uLong comprLen, Byte* uncompr, uLong uncomprLen);
private:
	z_stream m_stream;
};