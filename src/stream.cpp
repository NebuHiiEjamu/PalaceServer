#include <utility>

#include "stream.hpp"

template <class String, Size N> String&& PalaceInStream::read(bool padded)
{
	String s = readPString();
	if (padded) skip(N - s.size());
	return std::move(s);
}

template <class String> String&& PalaceInStream::readPString()
{
	Byte length = read()
	String s = read(length);
	return std::move(s);
}

std::string&& PalaceInStream::readCString()
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

template <class T> void PalaceOutStream::write(T t, int overwritePos = -1)
{
	if (overwritePos >= 0)
	{
		seek(overwritePos);
		write(t);
	}
	else
		write(t);
}

template <class String, Size N> void PalaceOutStream::write(const String &s, bool padded = false)
{
	writePString(s);
	if (padded) pad(N - s.size());
}

template <class String> void ByteBuffer::writePString(const String &s)
{
	write8(s.size());
	writeString(s);
}

void ByteBuffer::writeCString(const std::string_view &s)
{
	writeString(s);
	write8(0);
}
