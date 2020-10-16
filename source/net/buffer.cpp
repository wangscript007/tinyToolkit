/**
 *
 *  作者: hm
 *
 *  说明: 缓冲区
 *
 */


#include "buffer.h"

#include <cstring>


namespace net
{
	/**
	 *
	 * 构造函数
	 *
	 * @param originalSize 原始大小
	 *
	 */
	Buffer::Buffer(std::size_t originalSize) : _readPos(0),
	                                           _writePos(0),
	                                           _buffer(originalSize)
	{

	}

	/**
	 *
	 * 构造函数
	 *
	 * @param content 内容
	 * @param length 长度
	 *
	 */
	Buffer::Buffer(const void * content, std::size_t length) : _readPos(0),
	                                                           _writePos(0),
	                                                           _buffer(length)
	{
		Append(content, length);
	}

	/**
	 *
	 * 收缩
	 *
	 */
	void Buffer::Shrink()
	{
		Restructures();

		_buffer.resize(ReadableBytes());
		_buffer.shrink_to_fit();
	}

	/**
	 *
	 * 重组
	 *
	 */
	void Buffer::Restructures()
	{
		auto readable = ReadableBytes();

		::memmove(&_buffer[0], &_buffer[_readPos], readable);

		_readPos  = 0;
		_writePos = readable;
	}

	/**
	 *
	 * 追加内容
	 *
	 * @param content 内容
	 * @param length 长度
	 *
	 */
	void Buffer::Append(const void * content, std::size_t length)
	{
		ExpansionWriteSpace(length);

		::memcpy(Entry(), content, length);

		RetrieveWriteBytes(length);
	}

	/**
	 *
	 * 回收读取字节数
	 *
	 * @param bytes 字节数
	 *
	 */
	void Buffer::RetrieveReadBytes(std::size_t bytes)
	{
		if (bytes < ReadableBytes())
		{
			_readPos += bytes;
		}
		else
		{
			_readPos  = 0;
			_writePos = 0;
		}
	}

	/**
	 *
	 * 回收写入字节数
	 *
	 * @param bytes 字节数
	 *
	 */
	void Buffer::RetrieveWriteBytes(std::size_t bytes)
	{
		if (bytes < WritableBytes())
		{
			_writePos += bytes;
		}
		else
		{
			_writePos = Size();
		}
	}

	/**
	 *
	 * 扩充可写入空间
	 *
	 * @param bytes 字节数
	 *
	 */
	void Buffer::ExpansionWriteSpace(std::size_t bytes)
	{
		if (bytes <= WritableBytes())
		{
			return;
		}

		if (bytes <= AvailableBytes())
		{
			Restructures();
		}
		else
		{
			_buffer.resize(_writePos + bytes);
		}
	}

	/**
	 *
	 * 入口
	 *
	 * @return 入口
	 *
	 */
	char * Buffer::Entry()
	{
		return &_buffer[_writePos];
	}

	/**
	 *
	 * 查看8位有符号整数
	 *
	 * @return 8位有符号整数
	 *
	 */
	int8_t Buffer::PeekInt8() const
	{
		return *Peek();
	}

	/**
	 *
	 * 读取8位有符号整数
	 *
	 * @return 8位有符号整数
	 *
	 */
	int8_t Buffer::ReadInt8()
	{
		int8_t integer = PeekInt8();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看8位无符号整数
	 *
	 * @return 8位无符号整数
	 *
	 */
	uint8_t Buffer::PeekUint8() const
	{
		return static_cast<uint8_t>(*Peek());
	}

	/**
	 *
	 * 读取8位无符号整数
	 *
	 * @return 8位无符号整数
	 *
	 */
	uint8_t Buffer::ReadUint8()
	{
		uint8_t integer = PeekUint8();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看16位有符号整数
	 *
	 * @return 16位有符号整数
	 *
	 */
	int16_t Buffer::PeekInt16() const
	{
		int16_t integer{ 0 };

		::memcpy(&integer, Peek(), sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 读取16位有符号整数
	 *
	 * @return 16位有符号整数
	 *
	 */
	int16_t Buffer::ReadInt16()
	{
		int16_t integer = PeekInt16();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看16位无符号整数
	 *
	 * @return 16位无符号整数
	 *
	 */
	uint16_t Buffer::PeekUint16() const
	{
		uint16_t integer{ 0 };

		::memcpy(&integer, Peek(), sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 读取16位无符号整数
	 *
	 * @return 16位无符号整数
	 *
	 */
	uint16_t Buffer::ReadUint16()
	{
		uint16_t integer = PeekUint16();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看32位有符号整数
	 *
	 * @return 32位有符号整数
	 *
	 */
	int32_t Buffer::PeekInt32() const
	{
		int32_t integer{ 0 };

		::memcpy(&integer, Peek(), sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 读取32位有符号整数
	 *
	 * @return 32位有符号整数
	 *
	 */
	int32_t Buffer::ReadInt32()
	{
		int32_t integer = PeekInt32();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看32位无符号整数
	 *
	 * @return 32位无符号整数
	 *
	 */
	uint32_t Buffer::PeekUint32() const
	{
		uint32_t integer{ 0 };

		::memcpy(&integer, Peek(), sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 读取32位无符号整数
	 *
	 * @return 32位无符号整数
	 *
	 */
	uint32_t Buffer::ReadUint32()
	{
		uint32_t integer = PeekUint32();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看64位有符号整数
	 *
	 * @return 64位有符号整数
	 *
	 */
	int64_t Buffer::PeekInt64() const
	{
		int64_t integer{ 0 };

		::memcpy(&integer, Peek(), sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 读取64位有符号整数
	 *
	 * @return 64位有符号整数
	 *
	 */
	int64_t Buffer::ReadInt64()
	{
		int64_t integer = PeekInt64();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 查看64位无符号整数
	 *
	 * @return 64位无符号整数
	 *
	 */
	uint64_t Buffer::PeekUint64() const
	{
		uint64_t integer{ 0 };

		::memcpy(&integer, Peek(), sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 读取64位无符号整数
	 *
	 * @return 64位无符号整数
	 *
	 */
	uint64_t Buffer::ReadUint64()
	{
		uint64_t integer = PeekUint64();

		RetrieveReadBytes(sizeof(integer));

		return integer;
	}

	/**
	 *
	 * 大小
	 *
	 * @return 大小
	 *
	 */
	std::size_t Buffer::Size() const
	{
		return _buffer.size();
	}

	/**
	 *
	 * 容量
	 *
	 * @return 容量
	 *
	 */
	std::size_t Buffer::Capacity() const
	{
		return _buffer.capacity();
	}

	/**
	 *
	 * 可读字节数
	 *
	 * @return 可读字节数
	 *
	 */
	std::size_t Buffer::ReadableBytes() const
	{
		return _writePos - _readPos;
	}

	/**
	 *
	 * 可写字节数
	 *
	 * @return 可写字节数
	 *
	 */
	std::size_t Buffer::WritableBytes() const
	{
		return Size() - _writePos;
	}

	/**
	 *
	 * 可使用字节数
	 *
	 * @return 可使用字节数
	 *
	 */
	std::size_t Buffer::AvailableBytes() const
	{
		return Size() - ReadableBytes();
	}

	/**
	 *
	 * 查看字符串
	 *
	 * @param length 长度
	 *
	 * @return 字符串
	 *
	 */
	std::string Buffer::PeekString(std::size_t length) const
	{
		return std::string(Peek(), length > ReadableBytes() ? ReadableBytes() : length);
	}

	/**
	 *
	 * 读取字符串
	 *
	 * @param length 长度
	 *
	 * @return 字符串
	 *
	 */
	std::string Buffer::ReadString(std::size_t length)
	{
		std::string content(PeekString(length));

		RetrieveReadBytes(length);

		return content;
	}

	/**
	 *
	 * 查看
	 *
	 * @return 查看
	 *
	 */
	const char * Buffer::Peek() const
	{
		return &_buffer[_readPos];
	}
}
