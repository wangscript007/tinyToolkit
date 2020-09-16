#ifndef __CRYPTO__BASE64__H__
#define __CRYPTO__BASE64__H__


/**
 *
 *  作者: hm
 *
 *  说明: base64
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <string>


namespace crypto
{
	class API_TYPE Base64
	{
	public:
		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string Encode(const char * content);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string Encode(const uint8_t * content);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string Encode(const std::string & content);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 内容
		 *
		 */
		static std::string Encode(const char * content, std::size_t length);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 内容
		 *
		 */
		static std::string Encode(const uint8_t * content, std::size_t length);

		/**
		 *
		 * 编码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 内容
		 *
		 */
		static std::string Encode(const std::string & content, std::size_t length);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string Decode(const char * content);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string Decode(const uint8_t * content);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string Decode(const std::string & content);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 内容
		 *
		 */
		static std::string Decode(const char * content, std::size_t length);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 内容
		 *
		 */
		static std::string Decode(const uint8_t * content, std::size_t length);

		/**
		 *
		 * 解码
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 * @return 内容
		 *
		 */
		static std::string Decode(const std::string & content, std::size_t length);
	};
}


#endif // __CRYPTO__BASE64__H__
