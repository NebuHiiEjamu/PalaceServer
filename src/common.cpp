#include <algorithm>
#include <iterator>
#include <utility>

#include "common.hpp"

ByteBuffer::ByteBuffer()
	position(data.begin())
{
}

ByteBuffer::ByteBuffer(ByteString &inString):
	data(std::move(inString)),
	position(data.begin())
{
}

ByteBuffer&& ByteBuffer::clone(std::size_t bytes) const
{
	ByteBuffer newBuffer;
	newBuffer.data.insert(std::back_inserter(data), position, position + bytes);
	return std::move(newBuffer);
}

ByteString& ByteBuffer::getBytes() const
{
	return data;
}

std::size ByteBuffer::getSize() const
{
	return data.size();
}

void ByteBuffer::setBytes(ByteString &inString)
{
	data = std::move(inString);
}

void ByteBuffer::flush()
{
	data.clear();
}

template <class StringType> StringType&& ByteBuffer::read(std::size_t bytes)
{
	StringType s(position, position + bytes);
	position += bytes;
	return std::move(s);
}

template <class T> T ByteBuffer::read()
{
	T t;
	std::copy(position, position + sizeof(T), reinterpret_cast<T*>(&t));
	position += sizeof(T);
	return t;
}

void ByteBuffer::readNull(std::size_t bytes)
{
	position += bytes;
}

template <class StringType> StringType&& ByteBuffer::readStr31(bool padded)
{
	Byte b = *position;
	position++;

	StringType s(position, padded ? position + 31 : position + b);
	position += padded ? 31 : b;
	return std::move(s);
}

template <class StringType> StringType&& ByteBuffer::readStr63(bool padded)
{
	Byte b = *position;
	position++;

	StringType s(position, padded ? position + 63 : position + b);
	position += padded ? 63 : b;
	return std::move(s);
}

template <class StringType> StringType&& ByteBuffer::readPString()
{
	Byte b = *position;
	position++;

	StringType s(position, position + b);
	position += b
	return std::move(s);
}

std::string&& ByteBuffer::readCString()
{
	std::string s;

	while (*position != 0)
	{
		s += static_cast<char>(*position);
		position++;
	}
	return std::move(s);
}

template <class StringType> void ByteBuffer::write(const StringType &s);
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

template <class T> void ByteBuffer::write(T t, int overwritePos = -1)
{
	if (overwritePos >= 0)
	{
		data[overwritePos] = static_cast<Byte>(t & 0xFF);
		if (sizeof(T) > 1)
			for (int i = 1; i < sizeof(T); i++)
				data[overwritePos + i] = static_cast<Byte>((t & (0xFF << (i * 8))) >> (i * 8));
	}
	else
	{
		data.push_back(static_cast<Byte>(t & 0xFF));
		if (sizeof(T) > 1)
			for (int i = 1; i < sizeof(T); i++)
				data.push_back(static_cast<Byte>((t & (0xFF << (i * 8))) >> (i * 8)));
	}
}

void ByteBuffer::write32(uint32 i)
{
	data.push_back(static_cast<Byte>((i & 0xFF000000) >> 24);
	data.push_back(static_cast<Byte>((i & 0xFF0000) >> 16);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>(i & 0xFF);
}

void ByteBuffer::writeNull(std::size_t bytes)
{
	for (std::size_t i = 0; i < bytes; i++) data.push_back(0);
}

template <class StringType> void ByteBuffer::writeStr31(const StringType &s, bool padded = false)
{
	writePString(s);
	if (padded) writeNull(31 - s.size());
}

template <class StringType> void ByteBuffer::writeStr63(const StringType &s, bool padded = false)
{
	writePString(s);
	if (padded) writeNull(63 - s.size());
}

template <class StringType> void ByteBuffer::writePString(const StringType &s)
{
	data.push_back(static_cast<Byte>(s.size());
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

void ByteBuffer::writeCString(std::string_view s)
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
	data.push_back(0);
}
