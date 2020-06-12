#ifndef __LOGGER__CONTEXT__H__
#define __LOGGER__CONTEXT__H__


/**
 *
 *  作者: hm
 *
 *  说明: 上下文
 *
 */


#include "type.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <chrono>
#  include <string>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <chrono>
#  include <string>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <chrono>
#  include <string>
#
#endif


namespace logger
{
	struct API_TYPE Context
	{
		std::tm tm{ };

		std::string name{ };
		std::string content{ };

		LOG_OPTION_TYPE option{ };
		LOG_PRIORITY_TYPE priority{ };

		std::chrono::system_clock::time_point timePoint{ };
	};
}


#endif // __LOGGER__CONTEXT__H__
