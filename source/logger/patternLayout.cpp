/**
 *
 *  作者: hm
 *
 *  说明: 模式布局
 *
 */


#include "correspond.h"
#include "patternLayout.h"

#include <fmt/format.h>


namespace logger
{
	/**
	 *
	 * 格式化
	 *
	 * @param context 上下文
	 * @param storage 存储
	 * @param key 键值
	 *
	 */
	static void FormatPattern(const Context & context, std::string & storage, char key)
	{
		switch (key)
		{
			case 'A': /// 纳秒 (000000000..999999999)
			{
				storage += fmt::format
				(
					"{:09}",
					std::chrono::duration_cast<std::chrono::nanoseconds>(context.timePoint.time_since_epoch()).count() % 1000000000
				);

				break;
			}

			case 'C':  /// 微秒 (000000..999999)
			{
				storage += fmt::format
				(
					"{:06}",
					std::chrono::duration_cast<std::chrono::microseconds>(context.timePoint.time_since_epoch()).count() % 1000000
				);

				break;
			}

			case 'd':  /// 日期 (YYYY-MM-DD hh:mm:ss)
			{
				storage += fmt::format
				(
					"{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
					context.tm.tm_year + 1900,
					context.tm.tm_mon + 1,
					context.tm.tm_mday,
					context.tm.tm_hour,
					context.tm.tm_min,
					context.tm.tm_sec
				);

				break;
			}

			case 'D':  /// 按月计的日期 (01..31)
			{
				storage += fmt::format("{:02}", context.tm.tm_mday);

				break;
			}

			case 'h':  /// 小时 (00..23)
			{
				storage += fmt::format("{:02}", context.tm.tm_hour);

				break;
			}

			case 'L':  /// 毫秒 (000..999)
			{
				storage += fmt::format
				(
					"{:03}",
					std::chrono::duration_cast<std::chrono::milliseconds>(context.timePoint.time_since_epoch()).count() % 1000
				);

				break;
			}

			case 'm':  /// 分钟 (00..59)
			{
				storage += fmt::format("{:02}", context.tm.tm_min);

				break;
			}

			case 'M':  /// 月份 (01..12)
			{
				storage += fmt::format("{:02}", context.tm.tm_mon + 1);

				break;
			}

			case 'n':  /// 换行
			{
				storage += LINE_EOL;

				break;
			}

			case 'N':  /// 日志名称
			{
				storage += context.name;

				break;
			}

			case 'P':  /// 优先级
			{
				storage += PriorityCorrespond::Name(context.priority);

				break;
			}

			case 's':  /// 秒数 (00..60)
			{
				storage += fmt::format("{:02}", context.tm.tm_sec);

				break;
			}

			case 'S':  /// 秒数
			{
				storage += std::to_string(std::chrono::duration_cast<std::chrono::seconds>(context.timePoint.time_since_epoch()).count());

				break;
			}

			case 't':  /// 制表符Tab
			{
				storage += "\t";

				break;
			}

			case 'V':  /// 日志信息
			{
				storage += context.content;

				break;
			}

			case 'Y':  /// 年份 (1970...)
			{
				storage += std::to_string(context.tm.tm_year + 1900);

				break;
			}

			default: /// 其余格式化
			{
				storage.push_back('%');
				storage.push_back(key);

				break;
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 构造函数
	 *
	 * @param pattern 模式
	 *
	 */
	PatternLayout::PatternLayout(std::string pattern) : _pattern(std::move(pattern))
	{

	}

	/**
	 *
	 * 格式化
	 *
	 * @param context 上下文
	 *
	 * @return 格式化后内容
	 *
	 */
	std::string PatternLayout::Format(const Context & context)
	{
		std::string value{ };

		for (auto iter = _pattern.begin(); iter != _pattern.end(); ++iter)
		{
			if (*iter == '%')
			{
				if (++iter == _pattern.end())
				{
					break;
				}

				FormatPattern(context, value, *iter);
			}
			else
			{
				value.push_back(*iter);
			}
		}

		return value;
	}
}
