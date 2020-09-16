#ifndef __LOGGER__TYPE__H__
#define __LOGGER__TYPE__H__


/**
 *
 *  作者: hm
 *
 *  说明: 类型
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <cstdint>


namespace logger
{
	/**
	 *
	 * 日志操作
	 *
	 */
	enum class LOG_OPTION_TYPE : uint8_t
	{
		WRITING,
		FLUSH,
		TERMINATE,
	};

	/**
	 *
	 * 日志优先级
	 *
	 */
	enum class LOG_PRIORITY_TYPE : uint8_t
	{
		DEBUGS,
		INFO,
		NOTICE,
		WARNING,
		ERRORS,
		CRITICAL,
		ALERT,
		FATAL,
		EMERG,
	};
}


#endif // __LOGGER__TYPE__H__
