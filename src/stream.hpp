#ifndef _PALACE_STREAM_H
#define _PALACE_STREAM_H

#include <string>
#include <string_view>

#include "common/src/stream.hpp"

class PalaceInStream : public InStream
{
public:
	template <class String, Size N> StringType&& read(bool);
	std::string&& readCString();
	template <class String> String&& readPString();
};

class PalaceOutStream : public OutStream
{
public:
	template <class String, Size N> void write(const String&, bool);
	template <class T> void write(T, int);
	void writeCString(const std::string_view&);
	template <class String> void writePString(const String&);
};

#endif // _PALACE_STREAM_H
