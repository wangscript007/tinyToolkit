#ifndef __UTIL__REGEX__H__
#define __UTIL__REGEX__H__


/**
 *
 *  作者: hm
 *
 *  说明: 正则处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <regex>


namespace tinyToolkit
{
	namespace util
	{
		class API_TYPE Regex
		{
		public:
			/**
			 *
			 * 正则匹配
			 *
			 * @param content 内容
			 * @param rule 规则
			 *
			 * @return 是否匹配成功
			 *
			 */
			static bool Match(const std::string & content, const std::regex & rule);

			/**
			 *
			 * 是否为IP地址
			 *
			 * @param content 内容
			 *
			 * @return 是否为IP地址
			 *
			 */
			static bool IsIP(const std::string & content);

			/**
			 *
			 * 是否为Mac地址
			 *
			 * @param content 内容
			 *
			 * @return 是否为Mac地址
			 *
			 */
			static bool IsMac(const std::string & content);

			/**
			 *
			 * 是否为IPv4地址
			 *
			 * @param content 内容
			 *
			 * @return 是否为IPv4地址
			 *
			 */
			static bool IsIPv4(const std::string & content);

			/**
			 *
			 * 是否为IPv6地址
			 *
			 * @param content 内容
			 *
			 * @return 是否为IPv6地址
			 *
			 */
			static bool IsIPv6(const std::string & content);

			/**
			 *
			 * 是否为Mail地址
			 *
			 * @param content 内容
			 *
			 * @return 是否为Mail地址
			 *
			 */
			static bool IsMail(const std::string & content);

			/**
			 *
			 * 是否为日期
			 *
			 * @param content 内容
			 *
			 * @return 是否为日期
			 *
			 */
			static bool IsDate(const std::string & content);

			/**
			 *
			 * 是否为时间
			 *
			 * @param content 内容
			 *
			 * @return 是否为时间
			 *
			 */
			static bool IsTime(const std::string & content);

			/**
			 *
			 * 是否为日期时间
			 *
			 * @param content 内容
			 *
			 * @return 是否为日期时间
			 *
			 */
			static bool IsDateTime(const std::string & content);
		};
	}
}


#endif // __UTIL__REGEX__H__
