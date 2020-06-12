#ifndef __LOGGER__FILTER__H__
#define __LOGGER__FILTER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 过滤器
 *
 */


#include "context.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <memory>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <memory>
#
#endif


namespace logger
{
	class API_TYPE IFilter
	{
	public:
		/**
		 *
		 * 析构函数
		 *
		 */
		virtual ~IFilter() = default;

		/**
		 *
		 * 过滤处理
		 *
		 * @param context 上下文
		 *
		 * @return 是否过滤
		 *
		 */
		bool Decide(const Context & context);

		/**
		 *
		 * 添加过滤器
		 *
		 * @param filter 过滤器
		 *
		 * @return 过滤器
		 *
		 */
		std::shared_ptr<IFilter> AddFilter(std::shared_ptr<IFilter> filter);

	protected:
		/**
		 *
		 * 过滤处理
		 *
		 * @param context 上下文
		 *
		 * @return 是否过滤
		 *
		 */
		virtual bool Filter(const Context & context) = 0;

	private:
		/**
		 *
		 * 下一个过滤器
		 *
		 * @return 过滤器
		 *
		 */
		const std::shared_ptr<IFilter> & NextFilter();

	private:
		std::shared_ptr<IFilter> _nextFilter{ };
	};
}


#endif // __LOGGER__FILTER__H__
