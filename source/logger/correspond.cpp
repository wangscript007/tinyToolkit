/**
 *
 *  作者: hm
 *
 *  说明: 对应关系
 *
 */


#include "correspond.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <map>
#  include <stdexcept>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <map>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <map>
#
#endif


namespace logger
{
	/**
	 *
	 * 优先级
	 *
	 * @param name 名称
	 *
	 * @return 优先级
	 *
	 */
	LOG_PRIORITY_TYPE PriorityCorrespond::Priority(const std::string & name)
	{
		static std::map<std::string, LOG_PRIORITY_TYPE> PriorityNumber
		{
			{ "DEBUG", LOG_PRIORITY_TYPE::DEBUGS },
			{ "INFO", LOG_PRIORITY_TYPE::INFO },
			{ "NOTICE", LOG_PRIORITY_TYPE::NOTICE },
			{ "WARNING", LOG_PRIORITY_TYPE::WARNING },
			{ "ERROR", LOG_PRIORITY_TYPE::ERRORS },
			{ "CRITICAL", LOG_PRIORITY_TYPE::CRITICAL },
			{ "ALERT", LOG_PRIORITY_TYPE::ALERT },
			{ "FATAL", LOG_PRIORITY_TYPE::FATAL },
			{ "EMERG", LOG_PRIORITY_TYPE::EMERG },
		};

		auto find = PriorityNumber.find(name);

		if (find == PriorityNumber.end())
		{
			throw std::logic_error("The priority name cannot be recognized : " + name);
		}

		return find->second;
	}

	/**
	 *
	 * 名称
	 *
	 * @param priority 优先级
	 *
	 * @return 名称
	 *
	 */
	const std::string & PriorityCorrespond::Name(LOG_PRIORITY_TYPE priority)
	{
		static std::map<LOG_PRIORITY_TYPE, std::string> PriorityName
		{
			{ LOG_PRIORITY_TYPE::DEBUGS,   "DEBUG   " },
			{ LOG_PRIORITY_TYPE::INFO,     "INFO    " },
			{ LOG_PRIORITY_TYPE::NOTICE,   "NOTICE  " },
			{ LOG_PRIORITY_TYPE::WARNING,  "WARNING " },
			{ LOG_PRIORITY_TYPE::ERRORS,   "ERROR   " },
			{ LOG_PRIORITY_TYPE::CRITICAL, "CRITICAL" },
			{ LOG_PRIORITY_TYPE::ALERT,    "ALERT   " },
			{ LOG_PRIORITY_TYPE::FATAL,    "FATAL   " },
			{ LOG_PRIORITY_TYPE::EMERG,    "EMERG   " },
		};

		auto find = PriorityName.find(priority);

		if (find == PriorityName.end())
		{
			throw std::logic_error("The priority type cannot be recognized");
		}

		return find->second;
	}
}
