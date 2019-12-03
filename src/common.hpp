#ifndef _COMMON_H
#define _COMMON_H

#include <boost/asio.hpp>
#include <boost/safe_numerics/safe_integer.hpp>
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

using Acceptor = boost::asio::ip::tcp::acceptor;
using Byte = std::uint8_t;
using ByteString = std::vector<Byte>;
using Error = boost::asio::error_code;
using int16 = std::int16_t;
using int32 = std::int32_t;
using LockGuard = std::lock_guard<std::mutex>;
using sint16 = boost::numeric::safe<int16>;
using sint32 = boost::numeric::safe<int32>;
using Socket = boost::asio::ip::tcp::socket;
using Strand = boost::asio::io_context::strand;
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;

class ByteBuffer : std::enable_shared_from_this<ByteBuffer>
{
public:
	ByteBuffer();
	ByteBuffer(ByteString&);
	ByteBuffer&& clone(std::size_t) const;
	ByteString& getBytes() const;
	void setBytes(ByteString&);
	std::size getSize() const;
	void flush();
	template <class StringType> StringType&& read(std::size_t);
	template <class T> T read();
	void readNull(std::size_t);
	template <class StringType> StringType&& readStr31(bool);
	template <class StringType> StringType&& readStr63(bool);
	template <class StringType> StringType&& readPString();
	std::string&& readCString();
	template <class StringType> void write(const StringType&);
	template <class T> void write(T, int);
	void write32(uint32); // for ambiguity
	void writeNull(std::size_t);
	template <class StringType> void writeStr31(const StringType&, bool);
	template <class StringType> void writeStr63(const StringType&, bool);
	template <class StringType> void writePString(const StringType&);
	void writeCString(std::string_view);
private:
	ByteString data;
	ByteString::iterator position;
};

using ByteBufferPtr = std::shared_ptr<ByteBuffer>;

#endif // _COMMON_H
