#ifndef __HASH__HMAC_SHA1__H__
#define __HASH__HMAC_SHA1__H__


/**
 *
 *  作者: hm
 *
 *  说明: hmac_sha1
 *
 */


#include "sha1.h"


namespace hash
{
	class API_TYPE HMAC_SHA1
	{
		static const uint32_t PAD_SIZE = 64;
		static const uint32_t DIGEST_SIZE = 20;

		typedef struct
		{
			uint8_t iPad[PAD_SIZE]{ 0 };
			uint8_t oPad[PAD_SIZE]{ 0 };
		}Context;

	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		HMAC_SHA1();

		/**
		 *
		 * 重置
		 *
		 */
		void Reset();

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void SetKey(const char * key);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void SetKey(const uint8_t * key);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 *
		 */
		void SetKey(const std::string & key);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void SetKey(const char * key, std::size_t length);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void SetKey(const uint8_t * key, std::size_t length);

		/**
		 *
		 * 设置密钥
		 *
		 * @param key 密钥
		 * @param length 长度
		 *
		 */
		void SetKey(const std::string & key, std::size_t length);

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 *
		 */
		void Append(const char * content);

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 *
		 */
		void Append(const uint8_t * content);

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 *
		 */
		void Append(const std::string & content);

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void Append(const char * content, std::size_t length);

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void Append(const uint8_t * content, std::size_t length);

		/**
		 *
		 * 追加内容
		 *
		 * @param content 内容
		 * @param length 长度
		 *
		 */
		void Append(const std::string & content, std::size_t length);

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const uint8_t * Digest();

		/**
		 *
		 * 摘要
		 *
		 * @return 摘要
		 *
		 */
		const std::string & Result();

	private:
		/**
		 *
		 * 生成
		 *
		 */
		void Generate();

		/**
		 *
		 * 初始化
		 *
		 * @param context 上下文
		 *
		 */
		static void Initialization(Context & context);

	protected:
		SHA1 _sha1{ };

		bool _isComputed{ false };

		uint8_t _digest[DIGEST_SIZE]{ 0 };

		Context _context{ };

		std::string _result{ };
	};
}


#endif // __HASH__HMAC_SHA1__H__
