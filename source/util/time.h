#ifndef __UTIL__TIME__H__
#define __UTIL__TIME__H__


/**
 *
 *  作者: hm
 *
 *  说明: 时间处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <ctime>
#  include <string>
#  include <chrono>
#
#  include <winsock.h>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <string>
#  include <chrono>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <string>
#  include <chrono>
#
#endif


namespace util
{
	class API_TYPE Time
	{
	public:
		/**
		 *
		 * 时区
		 *
		 * @return 时区
		 *
		 */
		static std::time_t Timezone();

		/**
		 *
		 * 小时时间戳
		 *
		 * @return 小时时间戳
		 *
		 */
		static std::time_t Hours();

		/**
		 *
		 * 分钟时间戳
		 *
		 * @return 分钟时间戳
		 *
		 */
		static std::time_t Minutes();

		/**
		 *
		 * 秒数时间戳
		 *
		 * @return 秒数时间戳
		 *
		 */
		static std::time_t Seconds();

		/**
		 *
		 * 毫秒时间戳
		 *
		 * @return 毫秒时间戳
		 *
		 */
		static std::time_t Milliseconds();

		/**
		 *
		 * 微秒时间戳
		 *
		 * @return 微秒时间戳
		 *
		 */
		static std::time_t Microseconds();

		/**
		 *
		 * 纳秒时间戳
		 *
		 * @return 纳秒时间戳
		 *
		 */
		static std::time_t Nanoseconds();

		/**
		 *
		 * 偏移时间戳
		 *
		 * @param day 天
		 * @param hour 时
		 * @param minutes 分
		 * @param seconds 秒
		 *
		 * @return 秒数时间戳
		 *
		 */
		static std::time_t OffsetTime(int64_t day = 0, int32_t hour = 0, int32_t minutes = 0, int32_t seconds = 0);

		/**
		 *
		 * 转换为秒数时间戳
		 *
		 * @param date 日期
		 * @param format 格式化
		 *
		 * @return 秒数时间戳
		 *
		 */
		static std::time_t FromString(const char * date, const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 格式化时间字符串
		 *
		 * @param seconds 秒数时间戳
		 * @param timeZone 时区
		 * @param format 格式化
		 *
		 * @return 时间字符串
		 *
		 */
		static std::string Format(std::time_t seconds, std::time_t timeZone, const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 当前UTC时间字符串
		 *
		 * @param format 格式化
		 *
		 * @return 时间字符串
		 *
		 */
		static std::string UTCTimeString(const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 当前时区时间字符串
		 *
		 * @param format 格式化
		 *
		 * @return 时间字符串
		 *
		 */
		static std::string LocalTimeString(const char * format = "%4d-%02d-%02d %02d:%02d:%02d");

		/**
		 *
		 * 时间点
		 *
		 * @return 时间点
		 *
		 */
		static std::chrono::system_clock::time_point TimePoint();

		/**
		 *
		 * 时间点
		 *
		 * @param seconds 秒数时间戳
		 *
		 * @return 时间点
		 *
		 */
		static std::chrono::system_clock::time_point TimePoint(std::time_t time);

		/**
		 *
		 * 时间点
		 *
		 * @param time 时间结构体
		 *
		 * @return 时间点
		 *
		 */
		static std::chrono::system_clock::time_point TimePoint(const struct timeval & time);

		/**
		 *
		 * 时间点
		 *
		 * @param time 时间结构体
		 *
		 * @return 时间点
		 *
		 */
		static std::chrono::system_clock::time_point TimePoint(const struct timespec & time);
	};
}


#endif // __UTIL__TIME__H__
