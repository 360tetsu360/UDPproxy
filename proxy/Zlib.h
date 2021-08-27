#pragma once
#include <zlib.h>
#include <zconf.h>
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <algorithm>


typedef std::vector<unsigned char> vucarr;

class Zlib
{
	Zlib();
	~Zlib();
public:
	static Zlib* getZlib();
	int Inflate(const vucarr& in, vucarr& out);
private:
	z_stream m_stream;
};