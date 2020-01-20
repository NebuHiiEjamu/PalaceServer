#ifndef _STREAM_H
#define _STREAM_H

#include <string_view>

#include "common/src/stream.hpp"

class PalaceInStream : public InStream
{
public:
	std::string&& readCString()
	{
		std::string s;
		char c = ' ';

		while (c != 0)
		{
			c = static_cast<char>(read());
			s += c;
		}
		return std::move(s);
	}

	template <class String, Size N> String&& readPString(bool padded = false)
	{
		Byte length = read();
		String s = read(length);
		if (padded) ignore(N - s.size());
		return std::move(s);
	}
};

class PalaceOutStream : public OutStream
{
public:
	void writeCString(const std::string_view &s)
	{
		writeString(s);
		write8(0);
	}

	template <class String, Size N> void writePString(const String &s, bool padded = false)
	{
		write8(s.size());
		writeString(s);
		if (padded) ignore(N - s.size());
	}
};

#endif // _STREAM_H
