#ifndef __LOGGER__CORRESPOND__H__
#define __LOGGER__CORRESPOND__H__


/**
 *
 *  作者: hm
 *
 *  说明: 对应关系
 *
 */


#include "type.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <string>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <string>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <string>
#
#endif


namespace logger
{
	class API_TYPE PriorityCorrespond
	{
	public:
		/**
		 *
		 * 优先级
		 *
		 * @param name 名称
		 *
		 * @return 优先级
		 *
		 */
		static LOG_PRIORITY_TYPE Priority(const std::string & name);

		/**
		 *
		 * 名称
		 *
		 * @param priority 优先级
		 *
		 * @return 名称
		 *
		 */
		static const std::string & Name(LOG_PRIORITY_TYPE priority);
	};
}


#endif // __LOGGER__CORRESPOND__H__
