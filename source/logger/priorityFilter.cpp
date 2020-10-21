/**
 *
 *  作者: hm
 *
 *  说明: 优先级过滤器
 *
 */


#include "correspond.h"
#include "priorityFilter.h"


namespace tinyToolkit
{
	namespace logger
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		PriorityFilter::PriorityFilter(LOG_PRIORITY_TYPE priority) : _priority(priority)
		{

		}

		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		PriorityFilter::PriorityFilter(const std::string & priority) : _priority(PriorityCorrespond::Priority(priority))
		{

		}

		/**
		 *
		 * 过滤处理
		 *
		 * @param context 上下文
		 *
		 * @return 是否过滤
		 *
		 */
		bool PriorityFilter::Filter(const Context & context)
		{
			return _priority == context.priority;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		PriorityBelowFilter::PriorityBelowFilter(LOG_PRIORITY_TYPE priority) : _priority(priority)
		{

		}

		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		PriorityBelowFilter::PriorityBelowFilter(const std::string & priority) : _priority(PriorityCorrespond::Priority(priority))
		{

		}

		/**
		 *
		 * 过滤处理
		 *
		 * @param context 上下文
		 *
		 * @return 是否过滤
		 *
		 */
		bool PriorityBelowFilter::Filter(const Context & context)
		{
			return _priority > context.priority;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		PriorityAboveFilter::PriorityAboveFilter(LOG_PRIORITY_TYPE priority) : _priority(priority)
		{

		}

		/**
		 *
		 * 构造函数
		 *
		 * @param priority 优先级
		 *
		 */
		PriorityAboveFilter::PriorityAboveFilter(const std::string & priority) : _priority(PriorityCorrespond::Priority(priority))
		{

		}

		/**
		 *
		 * 过滤处理
		 *
		 * @param context 上下文
		 *
		 * @return 是否过滤
		 *
		 */
		bool PriorityAboveFilter::Filter(const Context & context)
		{
			return _priority < context.priority;
		}
	}
}
