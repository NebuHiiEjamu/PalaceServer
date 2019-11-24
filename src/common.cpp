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

Byte ByteBuffer::readByte()
{
	Byte b;
	std::copy(position, position + sizeof(Byte), reinterpret_cast<Byte*>(&b));
	position += sizeof(Byte);
	return b;
}

int16 ByteBuffer::readI16()
{
	int16 i;
	std::copy(position, position + sizeof(int16), reinterpret_cast<int16*>(&i));
	position += sizeof(int16);
	return i;
}

int32 ByteBuffer::readI32()
{
	int32 i;
	std::copy(position, position + sizeof(int32), reinterpret_cast<int32*>(&i));
	position += sizeof(int32);
	return i;
}

void ByteBuffer::readNull(std::size_t bytes)
{
	position += bytes;
}

template <class StringType> StringType&& ByteBuffer::readS31(bool padded)
{
	Byte b = *position;
	position++;

	StringType s(position, padded ? position + 31 : position + b);
	position += padded ? 31 : b;
	return std::move(s);
}

template <class StringType> StringType&& ByteBuffer::readS63(bool padded)
{
	Byte b = *position;
	position++;

	StringType s(position, padded ? position + 63 : position + b);
	position += padded ? 63 : b;
	return std::move(s);
}

std::string&& ByteBuffer::readString()
{
	std::string s;

	while (*position != 0)
	{
		s += static_cast<char>(*position);
		position++;
	}
	return std::move(s);
}

uint16 ByteBuffer::readU16()
{
	uint16 i;
	std::copy(position, position + sizeof(uint16), reinterpret_cast<uint16*>(&i));
	position += sizeof(uint16);
	return i;
}

uint32 ByteBuffer::readU32()
{
	uint32 i;
	std::copy(position, position + sizeof(uint32), reinterpret_cast<uint32*>(&i));
	position += sizeof(uint32);
	return i;
}

template <class StringType> void ByteBuffer::write(const StringType &s);
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
}

void ByteBuffer::writeByte(Byte b)
{
	data.push_back(b);
}

void ByteBuffer::writeI16(int16 i)
{
	data.push_back(static_cast<Byte>(i & 0xFF);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
}

void ByteBuffer::writeI32(int32 i)
{
	data.push_back(static_cast<Byte>(i & 0xFF);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>((i & 0xFF0000) >> 16);
	data.push_back(static_cast<Byte>((i & 0xFF000000) >> 24);
}

void ByteBuffer::writeNull(std::size_t bytes)
{
	for (std::size_t i = 0; i < bytes; i++) data.push_back(0);
}

template <class StringType> void ByteBuffer::writeS31(const StringType &s, bool padded = false)
{
	data.push_back(static_cast<Byte>(s.size());
	data.insert(std::back_inserter(data), s.begin(), s.end());
	if (padded) writeNull(31 - s.size());
}

template <class StringType> void ByteBuffer::writeS63(const StringType &s, bool padded = false)
{
	data.push_back(static_cast<Byte>(s.size());
	data.insert(std::back_inserter(data), s.begin(), s.end());
	if (padded) writeNull(63 - s.size());
}

void ByteBuffer::writeString(std::string_view s)
{
	data.insert(std::back_inserter(data), s.begin(), s.end());
	data.push_back(0);
}

void ByteBuffer::writeU16(uint16 i)
{
	data.push_back(static_cast<Byte>(i & 0xFF);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
}

void ByteBuffer::writeU32(uint32 i)
{
	data.push_back(static_cast<Byte>(i & 0xFF);
	data.push_back(static_cast<Byte>((i & 0xFF00) >> 8);
	data.push_back(static_cast<Byte>((i & 0xFF0000) >> 16);
	data.push_back(static_cast<Byte>((i & 0xFF000000) >> 24);
}
