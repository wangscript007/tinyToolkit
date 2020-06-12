/**
 *
 *  作者: hm
 *
 *  说明: 时间处理
 *
 */


#include "time.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <stdexcept>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <climits>
#  include <stdexcept>
#
#endif


namespace util
{
	/**
	 *
	 * 时区
	 *
	 * @return 时区
	 *
	 */
	std::time_t Time::Timezone()
	{
		std::tm utc{ };
		std::tm local{ };

		std::time_t current{ Seconds() };
		std::time_t timezone{ };

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::gmtime_s(&utc, &current);

		::localtime_s(&local, &current);

	#else

		::gmtime_r(&current, &utc);

		::localtime_r(&current, &local);

	#endif

		timezone = static_cast<std::time_t>(local.tm_hour - utc.tm_hour);

		if (timezone < -12)
		{
			timezone += 24;
		}
		else if (timezone > 12)
		{
			timezone -= 24;
		}

		return timezone;
	}

	/**
	 *
	 * 小时时间戳
	 *
	 * @return 小时时间戳
	 *
	 */
	std::time_t Time::Hours()
	{
		return std::chrono::duration_cast<std::chrono::hours>(TimePoint().time_since_epoch()).count();
	}

	/**
	 *
	 * 分钟时间戳
	 *
	 * @return 分钟时间戳
	 *
	 */
	std::time_t Time::Minutes()
	{
		return std::chrono::duration_cast<std::chrono::minutes>(TimePoint().time_since_epoch()).count();
	}

	/**
	 *
	 * 秒数时间戳
	 *
	 * @return 秒数时间戳
	 *
	 */
	std::time_t Time::Seconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(TimePoint().time_since_epoch()).count();
	}

	/**
	 *
	 * 毫秒时间戳
	 *
	 * @return 毫秒时间戳
	 *
	 */
	std::time_t Time::Milliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(TimePoint().time_since_epoch()).count();
	}

	/**
	 *
	 * 微秒时间戳
	 *
	 * @return 微秒时间戳
	 *
	 */
	std::time_t Time::Microseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(TimePoint().time_since_epoch()).count();
	}

	/**
	 *
	 * 纳秒时间戳
	 *
	 * @return 纳秒时间戳
	 *
	 */
	std::time_t Time::Nanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(TimePoint().time_since_epoch()).count();
	}

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
	std::time_t Time::OffsetTime(int64_t day, int32_t hour, int32_t minutes, int32_t seconds)
	{
		if (hour < 0 || hour > 23)
		{
			throw std::range_error("Hour out of range [0 ~ 23]");
		}

		if (minutes < 0 || minutes > 59)
		{
			throw std::range_error("Minutes out of range [0 ~ 59]");
		}

		if (seconds < 0 || seconds > 59)
		{
			throw std::range_error("Seconds out of range [0 ~ 59]");
		}

		std::tm now{ };

		std::time_t current = Seconds();

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::localtime_s(&now, &current);

	#else

		::localtime_r(&current, &now);

	#endif

		now.tm_hour = hour;
		now.tm_min  = minutes;
		now.tm_sec  = seconds;

		return std::mktime(&now) + (day * 86400);
	}

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
	std::time_t Time::FromString(const char * date, const char * format)
	{
		if (date == nullptr || format == nullptr)
		{
			return 0;
		}

		std::tm now{ };

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::sscanf_s(date, format, &now.tm_year, &now.tm_mon, &now.tm_mday, &now.tm_hour, &now.tm_min, &now.tm_sec);

	#else

		::sscanf(date, format, &now.tm_year, &now.tm_mon, &now.tm_mday, &now.tm_hour, &now.tm_min, &now.tm_sec);

	#endif

		now.tm_year -= 1900;
		now.tm_mon -= 1;

		return std::mktime(&now);
	}

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
	std::string Time::Format(std::time_t seconds, std::time_t timeZone, const char * format)
	{
		if (format == nullptr)
		{
			return { };
		}

		std::tm now{ };

		std::time_t current = seconds + (timeZone * 3600);

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::gmtime_s(&now, &current);

	#else

		::gmtime_r(&current, &now);

	#endif

		char content[NAME_MAX + 1]{ 0 };

		auto len = ::snprintf
		(
			content,
			NAME_MAX,
			format,
			now.tm_year + 1900,
			now.tm_mon + 1,
			now.tm_mday,
			now.tm_hour,
			now.tm_min,
			now.tm_sec
		);

		if (len < 0)
		{
			len = 0;
		}
		else if (len > NAME_MAX)
		{
			len = NAME_MAX;
		}

		content[len] = '\0';

		return content;
	}

	/**
	 *
	 * 当前UTC时间字符串
	 *
	 * @param format 格式化
	 *
	 * @return 时间字符串
	 *
	 */
	std::string Time::UTCTimeString(const char * pattern)
	{
		return Format(Seconds(), 0, pattern);
	}

	/**
	 *
	 * 当前时区时间字符串
	 *
	 * @param format 格式化
	 *
	 * @return 时间字符串
	 *
	 */
	std::string Time::LocalTimeString(const char * pattern)
	{
		static time_t timezone = Timezone();

		return Format(Seconds(), timezone, pattern);
	}

	/**
	 *
	 * 时间点
	 *
	 * @return 时间点
	 *
	 */
	std::chrono::system_clock::time_point Time::TimePoint()
	{
		return std::chrono::system_clock::now();
	}

	/**
	 *
	 * 时间点
	 *
	 * @param seconds 秒数时间戳
	 *
	 * @return 时间点
	 *
	 */
	std::chrono::system_clock::time_point Time::TimePoint(std::time_t time)
	{
		return std::chrono::time_point_cast<std::chrono::system_clock::duration>
		(
			std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>
			(
				std::chrono::seconds(time)
			)
		);
	}

	/**
	 *
	 * 时间点
	 *
	 * @param time 时间结构体
	 *
	 * @return 时间点
	 *
	 */
	std::chrono::system_clock::time_point Time::TimePoint(const struct timeval & time)
	{
		return std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration>
		(
			std::chrono::duration_cast<std::chrono::system_clock::duration>
			(
				std::chrono::seconds(time.tv_sec) + std::chrono::microseconds(time.tv_usec)
			)
		);
	}

	/**
	 *
	 * 时间点
	 *
	 * @param time 时间结构体
	 *
	 * @return 时间点
	 *
	 */
	std::chrono::system_clock::time_point Time::TimePoint(const struct timespec & time)
	{
		return std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration>
		(
			std::chrono::duration_cast<std::chrono::system_clock::duration>
			(
				std::chrono::seconds(time.tv_sec) + std::chrono::nanoseconds(time.tv_nsec)
			)
		);
	}
}
