#ifndef __UTIL__STRING__H__
#define __UTIL__STRING__H__


/**
 *
 *  作者: hm
 *
 *  说明: 字符串处理
 *
 */


#include <fmt/format.h>

#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <vector>
#  include <sstream>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <vector>
#  include <sstream>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <vector>
#  include <sstream>
#
#endif


namespace util
{
	class API_TYPE String
	{
	public:
		/**
		 *
		 * 流对象填充内容
		 *
		 * @param stream 流对象
		 * @param content 内容
		 *
		 */
		template <typename ContentT>
		static void JoinToStream(std::stringstream & stream, ContentT && content)
		{
			stream << std::forward<ContentT>(content);
		}

		/**
		 *
		 * 流对象填充内容
		 *
		 * @param stream 流对象
		 * @param content 内容
		 * @param args 内容
		 *
		 */
		template <typename ContentT, typename... Args>
		static void JoinToStream(std::stringstream & stream, ContentT && content, Args && ... args)
		{
			JoinToStream(stream, std::forward<ContentT>(content));
			JoinToStream(stream, std::forward<Args>(args)...);
		}

		/**
		 *
		 * 转换小写
		 *
		 * @param content 内容
		 * @param offset 偏移
		 *
		 */
		static void Lower(std::string & content, std::size_t offset = 0);

		/**
		 *
		 * 转换大写
		 *
		 * @param content 内容
		 * @param offset 偏移
		 *
		 */
		static void Upper(std::string & content, std::size_t offset = 0);

		/**
		 *
		 * 删除内容
		 *
		 * @param content 内容
		 * @param key 匹配值
		 * @param offset 偏移
		 *
		 */
		static void Erase(std::string & content, char key, std::size_t offset = 0);

		/**
		 *
		 * 删除内容
		 *
		 * @param content 内容
		 * @param key 匹配值
		 * @param offset 偏移
		 *
		 */
		static void Erase(std::string & content, const std::string & key, std::size_t offset = 0);

		/**
		 *
		 * 按值拆分内容
		 *
		 * @param content 内容
		 * @param key 匹配值
		 * @param result 结果
		 * @param keepEmpty 是否保留空串
		 *
		 */
		static void Split(const std::string & content, const std::string & key, std::vector<std::string> & result, bool keepEmpty = false);

		/**
		 *
		 * 按行拆分内容
		 *
		 * @param content 内容
		 * @param result 结果
		 * @param keepEnter 是否保留换行符
		 *
		 */
		static void SplitLines(const std::string & content, std::vector<std::string> & result, bool keepEnter = false);

		/**
		 *
		 * 替换内容
		 *
		 * @param content 内容
		 * @param src 被替换值
		 * @param dst 待替换值
		 * @param offset 偏移
		 *
		 */
		static void Replace(std::string & content, const std::string & src, const std::string & dst, std::size_t offset = 0);

		/**
		 *
		 * 循环替换内容
		 *
		 * @param content 内容
		 * @param src 被替换值
		 * @param dst 待替换值
		 * @param offset 偏移
		 *
		 */
		static void ReplaceLoop(std::string & content, const std::string & src, const std::string & dst, std::size_t offset = 0);

		/**
		 *
		 * 结尾匹配
		 *
		 * @param content 内容
		 * @param key 匹配值
		 *
		 * @return 是否匹配
		 *
		 */
		static bool EndWith(const std::string & content, const std::string & key);

		/**
		 *
		 * 开头匹配
		 *
		 * @param content 内容
		 * @param key 匹配值
		 *
		 * @return 是否匹配
		 *
		 */
		static bool StartWith(const std::string & content, const std::string & key);

		/**
		 *
		 * 填充内容
		 *
		 * @param content 内容
		 * @param args 内容
		 *
		 * @return 内容
		 *
		 */
		template <typename ContentT, typename... Args>
		static std::string Join(ContentT && content, Args && ... args)
		{
			std::stringstream stream{ };

			JoinToStream(stream, std::forward<ContentT>(content), std::forward<Args>(args)...);

			return stream.str();
		}

		/**
		 *
		 * 格式化内容
		 *
		 * @param format 格式化
		 * @param args 内容
		 *
		 * @return 内容
		 *
		 */
		template <typename... Args>
		static std::string Format(const char * format, Args &&... args)
		{
			return fmt::format(format, std::forward<Args>(args)...);
		}

		/**
		 *
		 * 格式化内容
		 *
		 * @param format 格式化
		 * @param args 内容
		 *
		 * @return 内容
		 *
		 */
		template <typename... Args>
		static std::string Format(const std::string & format, Args &&... args)
		{
			return fmt::format(format, std::forward<Args>(args)...);
		}

		/**
		 *
		 * 整理内容
		 *
		 * @param content 内容
		 * @param pattern 规则
		 *
		 * @return 内容
		 *
		 */
		static std::string Trim(const std::string & content, const char * pattern = "\r\n\t ");

		/**
		 *
		 * 过滤注释
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string FilterNote(const std::string & content);

		/**
		 *
		 * 收缩json
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string ReduceJson(const std::string & content);

		/**
		 *
		 * 美化json
		 *
		 * @param content 内容
		 *
		 * @return 内容
		 *
		 */
		static std::string BeautifyJson(const std::string & content);

		/**
		 *
		 * 转换为16进制内容
		 *
		 * @param content 内容
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string AsHexString(const char * content, bool reverse = false);

		/**
		 *
		 * 转换为16进制内容
		 *
		 * @param content 内容
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string AsHexString(const uint8_t * content, bool reverse = false);

		/**
		 *
		 * 转换为16进制内容
		 *
		 * @param content 内容
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string AsHexString(const std::string & content, bool reverse = false);

		/**
		 *
		 * 转换为16进制内容
		 *
		 * @param content 内容
		 * @param length 长度
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string AsHexString(const char * content, std::size_t length, bool reverse = false);

		/**
		 *
		 * 转换为16进制内容
		 *
		 * @param content 内容
		 * @param length 长度
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string AsHexString(const uint8_t * content, std::size_t length, bool reverse = false);

		/**
		 *
		 * 转换为16进制内容
		 *
		 * @param content 内容
		 * @param length 长度
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string AsHexString(const std::string & content, std::size_t length, bool reverse = false);

		/**
		 *
		 * 转换为10进制内容
		 *
		 * @param content 内容
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string FromHexString(const char * content, bool reverse = false);

		/**
		 *
		 * 转换为10进制内容
		 *
		 * @param content 内容
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string FromHexString(const uint8_t * content, bool reverse = false);

		/**
		 *
		 * 转换为10进制内容
		 *
		 * @param content 内容
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string FromHexString(const std::string & content, bool reverse = false);

		/**
		 *
		 * 转换为10进制内容
		 *
		 * @param content 内容
		 * @param length 长度
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string FromHexString(const char * content, std::size_t length, bool reverse = false);

		/**
		 *
		 * 转换为10进制内容
		 *
		 * @param content 内容
		 * @param length 长度
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string FromHexString(const uint8_t * content, std::size_t length, bool reverse = false);

		/**
		 *
		 * 转换为10进制内容
		 *
		 * @param content 内容
		 * @param length 长度
		 * @param reverse 是否反向转换
		 *
		 * @return 内容
		 *
		 */
		static std::string FromHexString(const std::string & content, std::size_t length, bool reverse = false);
	};
}


#endif // __UTIL__STRING__H__
