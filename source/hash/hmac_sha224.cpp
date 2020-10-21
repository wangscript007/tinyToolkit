/**
 *
 *  作者: hm
 *
 *  说明: hmac_sha224
 *
 */


#include "hmac_sha224.h"

#include <cstring>


namespace tinyToolkit
{
	namespace hash
	{
		const uint32_t HMAC_SHA224::PAD_SIZE;
		const uint32_t HMAC_SHA224::DIGEST_SIZE;

		/**
		 *
		 * 构造函数
		 *
		 */
		HMAC_SHA224::HMAC_SHA224()
		{
			Reset();
		}

		/**
		 *
		 * 重置
		 *
		 */
		void HMAC_SHA224::Reset()
		{
			_isComputed = false;

			::memset(reinterpret_cast<void *>(_digest),   0, sizeof(_digest));
			::memset(reinterpret_cast<void *>(&_context), 0, sizeof(_context));

			_result.clear();
			_result.shrink_to_fit();

			Initialization(_context);

			_sha224.Reset();
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void HMAC_SHA224::SetKey(const char * key)
		{
			if (key == nullptr)
			{
				return;
			}

			SetKey(key, ::strlen(key));
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void HMAC_SHA224::SetKey(const uint8_t * key)
		{
			if (key == nullptr)
			{
				return;
			}

			SetKey(key, ::strlen(reinterpret_cast<const char *>(key)));
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void HMAC_SHA224::SetKey(const std::string & key)
		{
			if (key.empty())
			{
				return;
			}

			SetKey(key, key.size());
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void HMAC_SHA224::SetKey(const char * key, std::size_t length)
		{
			if (key == nullptr || length == 0)
			{
				return;
			}

			SetKey(reinterpret_cast<const uint8_t *>(key), length);
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void HMAC_SHA224::SetKey(const uint8_t * key, std::size_t length)
		{
			if (key == nullptr || length == 0)
			{
				return;
			}

			if (length > PAD_SIZE)
			{
				SHA224 sha224{ };

				sha224.Append(key, length);

				for (uint32_t i = 0; i < PAD_SIZE; ++i)
				{
					_context.iPad[i] = sha224.Digest()[i] ^ 0x36;
					_context.oPad[i] = sha224.Digest()[i] ^ 0x5c;
				}
			}
			else
			{
				::memset(_context.iPad, 0x36, PAD_SIZE);
				::memset(_context.oPad, 0x5c, PAD_SIZE);

				for (std::size_t i = 0; i < length; ++i)
				{
					_context.iPad[i] = key[i] ^ 0x36;
					_context.oPad[i] = key[i] ^ 0x5c;
				}
			}

			Append(_context.iPad, PAD_SIZE);
		}

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void HMAC_SHA224::SetKey(const std::string & key, std::size_t length)
		{
			if (length == 0)
			{
				return;
			}

			SetKey(key.c_str(), length);
		}

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 *
		 */
		void HMAC_SHA224::Append(const char * content)
		{
			if (content == nullptr)
			{
				return;
			}

			Append(content, ::strlen(content));
		}

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 *
		 */
		void HMAC_SHA224::Append(const uint8_t * content)
		{
			if (content == nullptr)
			{
				return;
			}

			Append(content, ::strlen(reinterpret_cast<const char *>(content)));
		}

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 *
		 */
		void HMAC_SHA224::Append(const std::string & content)
		{
			if (content.empty())
			{
				return;
			}

			Append(content, content.size());
		}

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void HMAC_SHA224::Append(const char * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return;
			}

			Append(reinterpret_cast<const uint8_t *>(content), length);
		}

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void HMAC_SHA224::Append(const uint8_t * content, std::size_t length)
		{
			if (content == nullptr || length == 0)
			{
				return;
			}

			_sha224.Append(content, length);

			_isComputed = false;
		}

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void HMAC_SHA224::Append(const std::string & content, std::size_t length)
		{
			if (length == 0)
			{
				return;
			}

			Append(content.c_str(), length);
		}

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const uint8_t * HMAC_SHA224::Digest()
		{
			Generate();

			return _digest;
		}

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const std::string & HMAC_SHA224::Result()
		{
			Generate();

			return _result;
		}

		/**
		 *
		 * 生成
		 *
		 */
		void HMAC_SHA224::Generate()
		{
			if (_isComputed)
			{
				return;
			}

			_isComputed = true;

			SHA224 sha224{ };

			sha224.Append(_context.oPad, PAD_SIZE);
			sha224.Append(_sha224.Digest(), DIGEST_SIZE);

			::memcpy(_digest, sha224.Digest(), DIGEST_SIZE);

			_result.clear();
			_result.shrink_to_fit();

			for (uint32_t i = 0; i != DIGEST_SIZE; ++i)
			{
				char buffer[3]{ 0 };

				::snprintf(buffer, sizeof(buffer), "%02x", _digest[i]);

				_result.append(buffer, 2);
			}
		}

		/**
		 *
		 * 初始化
		 *
		 * @param context 上下文
		 *
		 */
		void HMAC_SHA224::Initialization(Context & context)
		{
			::memset(context.iPad, 0x36, PAD_SIZE);
			::memset(context.oPad, 0x5c, PAD_SIZE);
		}
	}
}
