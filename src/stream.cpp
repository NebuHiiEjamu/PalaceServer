#include <utility>

#include "stream.hpp"

template <class String, Size N> String&& PalaceInStream::read(bool padded)
{
	String s = readPString();
	internal.ignore(N - s.size());
	return std::move(s);
}

template <class String> String&& PalaceInStream::readPString()
{
	Byte length = internal.get();
	String s(length, 0);

	internal.read(reinterpret_cast<Byte*>(&s[0]), length);
	return std::move(s);
}

std::string&& PalaceInStream::readCString()
{
	std::string s;
	char c = ' ';

	while (c != 0)
	{
		c = static_cast<char>(internal.get());
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
	internal.put(s.size());
	write(s);
}

void ByteBuffer::writeCString(const std::string_view &s)
{
	write(s);
	internal.put(0);
}
