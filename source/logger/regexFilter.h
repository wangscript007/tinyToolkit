#ifndef __LOGGER__REGEX_FILTER__H__
#define __LOGGER__REGEX_FILTER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 正则过滤器
 *
 */


#include "filter.h"

#include <regex>


namespace logger
{
	class API_TYPE RegexFilter : public IFilter
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param rule 规则
		 *
		 */
		explicit RegexFilter(std::regex rule);

		/**
		 *
		 * 构造函数
		 *
		 * @param rule 规则
		 *
		 */
		explicit RegexFilter(const std::string & rule);

	private:
		/**
		 *
		 * 过滤处理
		 *
		 * @param context 上下文
		 *
		 * @return 是否过滤
		 *
		 */
		bool Filter(const Context & context) override;

	private:
		std::regex _rule{ };
	};
}


#endif // __LOGGER__REGEX_FILTER__H__
