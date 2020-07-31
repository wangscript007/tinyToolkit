/**
 *
 *  作者: hm
 *
 *  说明: url
 *
 */


#include "url.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <cstring>
#
#endif


namespace crypto
{
	/**
	 *
	 * 字符对应的16进制
	 *
	 * @param tag 字符
	 *
	 * @return 16进制字符
	 *
	 */
	static char AsHex(uint8_t tag)
	{
		return static_cast<char>(tag > 9 ? tag - 10 + 'A': tag + '0');
	}

	/**
	 *
	 * 16进制对应的字符
	 *
	 * @param tag 字符
	 *
	 * @return 字符
	 *
	 */
	static uint8_t AsChar(uint8_t tag)
	{
		return static_cast<uint8_t>(::isdigit(tag) == 0 ? tag + 10 - 'A' : tag - '0');
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 编码
	 *
	 * @param content 内容
	 *
	 * @return 内容
	 *
	 */
	std::string Url::Encode(const char * content)
	{
		if (content == nullptr)
		{
			return { };
		}

		return Encode(content, ::strlen(content));
	}

	/**
	 *
	 * 编码
	 *
	 * @param content 内容
	 *
	 * @return 内容
	 *
	 */
	std::string Url::Encode(const uint8_t * content)
	{
		if (content == nullptr)
		{
			return { };
		}

		return Encode(content, ::strlen(reinterpret_cast<const char *>(content)));
	}

	/**
	 *
	 * 编码
	 *
	 * @param content 内容
	 *
	 * @return 内容
	 *
	 */
	std::string Url::Encode(const std::string & content)
	{
		if (content.empty())
		{
			return { };
		}

		return Encode(content, content.size());
	}

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
	std::string Url::Encode(const char * content, std::size_t length)
	{
		if (content == nullptr || length == 0)
		{
			return { };
		}

		return Encode(reinterpret_cast<const uint8_t *>(content), length);
	}

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
	std::string Url::Encode(const uint8_t * content, std::size_t length)
	{
		if (content == nullptr || length == 0)
		{
			return { };
		}

		std::string value{ };

		for (size_t i = 0; i < length; ++i)
		{
			uint8_t byte = content[i];

			if (::isalnum(byte))
			{
				value += static_cast<char>(byte);
			}
			else if (byte == ' ')
			{
				value += "+";
			}
			else if (byte == '-' || byte == '_' || byte == '.' || byte == '!' ||
			         byte == '~' || byte == '*' || byte == '(' || byte == ')')
			{
				value += static_cast<char>(byte);
			}
			else
			{
				value += "%";
				value += AsHex(static_cast<uint8_t>(byte >> 4));
				value += AsHex(static_cast<uint8_t>(byte % 16));
			}
		}

		return value;
	}

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
	std::string Url::Encode(const std::string & content, std::size_t length)
	{
		if (length == 0)
		{
			return { };
		}

		return Encode(content.c_str(), length);
	}

	/**
	 *
	 * 解码
	 *
	 * @param content 内容
	 *
	 * @return 内容
	 *
	 */
	std::string Url::Decode(const char * content)
	{
		if (content == nullptr)
		{
			return { };
		}

		return Decode(content, ::strlen(content));
	}

	/**
	 *
	 * 解码
	 *
	 * @param content 内容
	 *
	 * @return 内容
	 *
	 */
	std::string Url::Decode(const uint8_t * content)
	{
		if (content == nullptr)
		{
			return { };
		}

		return Decode(content, ::strlen(reinterpret_cast<const char *>(content)));
	}

	/**
	 *
	 * 解码
	 *
	 * @param content 内容
	 *
	 * @return 内容
	 *
	 */
	std::string Url::Decode(const std::string & content)
	{
		if (content.empty())
		{
			return { };
		}

		return Decode(content, content.size());
	}

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
	std::string Url::Decode(const char * content, std::size_t length)
	{
		if (content == nullptr || length == 0)
		{
			return { };
		}

		return Decode(reinterpret_cast<const uint8_t *>(content), length);
	}

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
	std::string Url::Decode(const uint8_t * content, std::size_t length)
	{
		if (content == nullptr || length == 0)
		{
			return { };
		}

		std::string value{ };

		for (std::size_t i = 0; i < length; ++i)
		{
			if (content[i] == '+')
			{
				value.push_back(' ');
			}
			else if (content[i] == '%')
			{
				uint8_t high = AsChar(content[++i]);
				uint8_t low  = AsChar(content[++i]);

				value.push_back(static_cast<char>(high * 16 + low));
			}
			else
			{
				value.push_back(static_cast<char>(content[i]));
			}
		}

		return value;
	}

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
	std::string Url::Decode(const std::string & content, std::size_t length)
	{
		if (length == 0)
		{
			return { };
		}

		return Decode(content.c_str(), length);
	}
}
