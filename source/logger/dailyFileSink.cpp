/**
 *
 *  作者: hm
 *
 *  说明: 时间文件节点
 *
 */


#include "dailyFileSink.h"

#include <climits>


namespace logger
{
	/**
	 *
	 * 秒数时间戳
	 *
	 * @return 秒数时间戳
	 *
	 */
	static int64_t Seconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	/**
	 *
	 * 基于今日偏移的天数时间戳
	 *
	 * @param hour 时
	 * @param minutes 分
	 * @param seconds 秒
	 *
	 * @return 天数时间戳
	 *
	 */
	static int64_t OffsetTime(int32_t hour, int32_t minutes, int32_t seconds)
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

		int64_t current = Seconds();

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::localtime_s(&now, reinterpret_cast<std::time_t *>(&current));

	#else

		::localtime_r(reinterpret_cast<std::time_t *>(&current), &now);

	#endif

		now.tm_hour = hour;
		now.tm_min  = minutes;
		now.tm_sec  = seconds;

		return std::mktime(&now) + 86400;
	}

	/**
	 *
	 * 当前本地时间字符串
	 *
	 * @param format 格式化
	 *
	 * @return 时间字符串
	 *
	 */
	static std::string LocalTimeString(const char * format)
	{
		if (format == nullptr)
		{
			return { };
		}

		std::tm now{ };

		int64_t current = Seconds() + (8 * 3600);

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::gmtime_s(&now, reinterpret_cast<std::time_t *>(&current));

	#else

		::gmtime_r(reinterpret_cast<std::time_t *>(&current), &now);

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


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 构造函数
	 *
	 * @param name 名称
	 * @param path 路径
	 * @param hour 小时
	 * @param minute 分钟
	 * @param second 秒数
	 *
	 */
	DailyFileSink::DailyFileSink(std::string name, std::string path, int32_t hour, int32_t minute, int32_t second) : ISink(std::move(name)),
	                                                                                                                 _hour(hour),
	                                                                                                                 _minute(minute),
	                                                                                                                 _second(second),
	                                                                                                                 _path(std::move(path))
	{
		if (!_file.Open(FormatPath()))
		{
			throw std::logic_error("Open daily log file failed : " + _file.Path());
		}

		UpdateTime();
	}

	/**
	 *
	 * 析构函数
	 *
	 */
	DailyFileSink::~DailyFileSink()
	{
		_file.Close();
	}

	/**
	 *
	 * 关闭
	 *
	 */
	void DailyFileSink::Close()
	{
		_file.Flush();
		_file.Close();
	}

	/**
	 *
	 * 刷新
	 *
	 */
	void DailyFileSink::Flush()
	{
		_file.Flush();
	}

	/**
	 *
	 * 写入
	 *
	 * @param context 上下文
	 *
	 */
	void DailyFileSink::Write(const Context & context)
	{
		if (Filter() && Filter()->Decide(context))
		{
			return;
		}

		if (Seconds() >= _time)
		{
			_file.Close();

			if (!_file.Open(FormatPath()))
			{
				throw std::logic_error("Open daily log file failed : " + _file.Path());
			}

			UpdateTime();
		}

		_file.Write(Layout() ? Layout()->Format(context) : context.content);

		if (IsAutoFlush())
		{
			Flush();
		}
	}

	/**
	 *
	 * 刷新下次生成的时间
	 *
	 */
	void DailyFileSink::UpdateTime()
	{
		_time = OffsetTime(_hour, _minute, _second);

		if (_time < Seconds())
		{
			_time += 86400;
		}
	}

	/**
	 *
	 * 格式化路径
	 *
	 * @return 路径
	 *
	 */
	std::string DailyFileSink::FormatPath()
	{
		std::size_t pos = _path.rfind('.');

		auto time = LocalTimeString("%4d_%02d_%02d_%02d_%02d_%02d");

		if (pos == std::string::npos)  /// name_yyyy_MM_dd_hh_mm_ss
		{
			return _path + "_" + time;
		}
		else if (pos == 0)  /// yyyy_MM_dd_hh_mm_ss.log
		{
			return time + _path;
		}
		else   /// name_yyyy_MM_dd_hh_mm_ss.log
		{
			return _path.substr(0, pos) + "_" + time + _path.substr(pos);
		}
	}
}
