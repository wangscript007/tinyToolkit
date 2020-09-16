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

#include <chrono>
#include <string>


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
