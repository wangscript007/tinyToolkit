#ifndef __NET__BUFFER__H__
#define __NET__BUFFER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 缓冲区
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <vector>
#include <string>


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE Buffer
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param originalSize 原始大小
			 *
			 */
			explicit Buffer(std::size_t originalSize = 256);

			/**
			 *
			 * 构造函数
			 *
			 * @param content 内容
			 * @param length 长度
			 *
			 */
			explicit Buffer(const void * content, std::size_t length);

			/**
			 *
			 * 收缩
			 *
			 */
			void Shrink();

			/**
			 *
			 * 重组
			 *
			 */
			void Restructures();

			/**
			 *
			 * 追加内容
			 *
			 * @param content 内容
			 * @param length 长度
			 *
			 */
			void Append(const void * content, std::size_t length);

			/**
			 *
			 * 回收读取字节数
			 *
			 * @param bytes 字节数
			 *
			 */
			void RetrieveReadBytes(std::size_t bytes);

			/**
			 *
			 * 回收写入字节数
			 *
			 * @param bytes 字节数
			 *
			 */
			void RetrieveWriteBytes(std::size_t bytes);

			/**
			 *
			 * 扩充可写入空间
			 *
			 * @param bytes 字节数
			 *
			 */
			void ExpansionWriteSpace(std::size_t bytes);

			/**
			 *
			 * 入口
			 *
			 * @return 入口
			 *
			 */
			char * Entry();

			/**
			 *
			 * 查看8位有符号整数
			 *
			 * @return 8位有符号整数
			 *
			 */
			int8_t PeekInt8() const;

			/**
			 *
			 * 读取8位有符号整数
			 *
			 * @return 8位有符号整数
			 *
			 */
			int8_t ReadInt8();

			/**
			 *
			 * 查看8位无符号整数
			 *
			 * @return 8位无符号整数
			 *
			 */
			uint8_t PeekUint8() const;

			/**
			 *
			 * 读取8位无符号整数
			 *
			 * @return 8位无符号整数
			 *
			 */
			uint8_t ReadUint8();

			/**
			 *
			 * 查看16位有符号整数
			 *
			 * @return 16位有符号整数
			 *
			 */
			int16_t PeekInt16() const;

			/**
			 *
			 * 读取16位有符号整数
			 *
			 * @return 16位有符号整数
			 *
			 */
			int16_t ReadInt16();

			/**
			 *
			 * 查看16位无符号整数
			 *
			 * @return 16位无符号整数
			 *
			 */
			uint16_t PeekUint16() const;

			/**
			 *
			 * 读取16位无符号整数
			 *
			 * @return 16位无符号整数
			 *
			 */
			uint16_t ReadUint16();

			/**
			 *
			 * 查看32位有符号整数
			 *
			 * @return 32位有符号整数
			 *
			 */
			int32_t PeekInt32() const;

			/**
			 *
			 * 读取32位有符号整数
			 *
			 * @return 32位有符号整数
			 *
			 */
			int32_t ReadInt32();

			/**
			 *
			 * 查看32位无符号整数
			 *
			 * @return 32位无符号整数
			 *
			 */
			uint32_t PeekUint32() const;

			/**
			 *
			 * 读取32位无符号整数
			 *
			 * @return 32位无符号整数
			 *
			 */
			uint32_t ReadUint32();

			/**
			 *
			 * 查看64位有符号整数
			 *
			 * @return 64位有符号整数
			 *
			 */
			int64_t PeekInt64() const;

			/**
			 *
			 * 读取64位有符号整数
			 *
			 * @return 64位有符号整数
			 *
			 */
			int64_t ReadInt64();

			/**
			 *
			 * 查看64位无符号整数
			 *
			 * @return 64位无符号整数
			 *
			 */
			uint64_t PeekUint64() const;

			/**
			 *
			 * 读取64位无符号整数
			 *
			 * @return 64位无符号整数
			 *
			 */
			uint64_t ReadUint64();

			/**
			 *
			 * 大小
			 *
			 * @return 大小
			 *
			 */
			std::size_t Size() const;

			/**
			 *
			 * 容量
			 *
			 * @return 容量
			 *
			 */
			std::size_t Capacity() const;

			/**
			 *
			 * 可读字节数
			 *
			 * @return 可读字节数
			 *
			 */
			std::size_t ReadableBytes() const;

			/**
			 *
			 * 可写字节数
			 *
			 * @return 可写字节数
			 *
			 */
			std::size_t WritableBytes() const;

			/**
			 *
			 * 可使用字节数
			 *
			 * @return 可使用字节数
			 *
			 */
			std::size_t AvailableBytes() const;

			/**
			 *
			 * 查看字符串
			 *
			 * @param length 长度
			 *
			 * @return 字符串
			 *
			 */
			std::string PeekString(std::size_t length) const;

			/**
			 *
			 * 读取字符串
			 *
			 * @param length 长度
			 *
			 * @return 字符串
			 *
			 */
			std::string ReadString(std::size_t length);

			/**
			 *
			 * 查看
			 *
			 * @return 查看
			 *
			 */
			const char * Peek() const;

		private:
			std::size_t _readPos{ 0 };
			std::size_t _writePos{ 0 };

			std::vector<char> _buffer{ };
		};
	}
}


#endif // __NET__BUFFER__H__
