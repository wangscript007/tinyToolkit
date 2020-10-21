/**
 *
 *  作者: hm
 *
 *  说明: 简单布局
 *
 */


#include "correspond.h"
#include "simpleLayout.h"

#include <fmt/format.h>


namespace tinyToolkit
{
	namespace logger
	{
		/**
		 *
		 * 格式化
		 *
		 * @param context 上下文
		 *
		 * @return 格式化后内容
		 *
		 */
		std::string SimpleLayout::Format(const Context & context)
		{
			return fmt::format
			(
				"[{:04}-{:02}-{:02} {:02}:{:02}:{:02}.{:06}][{}][{}] {}\n",
				context.tm.tm_year + 1900,
				context.tm.tm_mon + 1,
				context.tm.tm_mday,
				context.tm.tm_hour,
				context.tm.tm_min,
				context.tm.tm_sec,
				std::chrono::duration_cast<std::chrono::microseconds>(context.timePoint.time_since_epoch()).count() % 1000000,
				context.name,
				PriorityCorrespond::Name(context.priority),
				context.content
			);
		}
	}
}
