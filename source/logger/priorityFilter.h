#ifndef __LOGGER__PRIORITY_FILTER__H__
#define __LOGGER__PRIORITY_FILTER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 优先级过滤器
 *
 */


#include "filter.h"


namespace logger
{
	class API_TYPE PriorityFilter : public IFilter
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		explicit PriorityFilter(LOG_PRIORITY_TYPE priority);

		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		explicit PriorityFilter(const std::string & priority);

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
		LOG_PRIORITY_TYPE _priority{ };
	};

	class API_TYPE PriorityBelowFilter : public IFilter
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		explicit PriorityBelowFilter(LOG_PRIORITY_TYPE priority);

		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		explicit PriorityBelowFilter(const std::string & priority);

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
		LOG_PRIORITY_TYPE _priority{ };
	};

	class API_TYPE PriorityAboveFilter : public IFilter
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		explicit PriorityAboveFilter(LOG_PRIORITY_TYPE priority);

		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		explicit PriorityAboveFilter(const std::string & priority);

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
		LOG_PRIORITY_TYPE _priority{ };
	};
}


#endif // __LOGGER__PRIORITY_FILTER__H__
