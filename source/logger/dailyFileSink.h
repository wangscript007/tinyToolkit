#ifndef __LOGGER__DAILY_FILE_SINK__H__
#define __LOGGER__DAILY_FILE_SINK__H__


/**
 *
 *  作者: hm
 *
 *  说明: 时间文件节点
 *
 */


#include "file.h"
#include "sink.h"

#include <ctime>


namespace logger
{
	class API_TYPE DailyFileSink : public ISink
	{
	public:
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
		DailyFileSink(std::string name, std::string path, int32_t hour = 0, int32_t minute = 0, int32_t second = 0);

		/**
		 *
		 * 析构函数
		 *
		 */
		~DailyFileSink() override;

		/**
		 *
		 * 关闭
		 *
		 */
		void Close() override;

		/**
		 *
		 * 刷新
		 *
		 */
		void Flush() override;

		/**
		 *
		 * 写入
		 *
		 * @param context 上下文
		 *
		 */
		void Write(const Context & context) override;

	private:
		/**
		 *
		 * 刷新下次生成的时间
		 *
		 */
		void UpdateTime();

		/**
		 *
		 * 格式化路径
		 *
		 * @return 路径
		 *
		 */
		std::string FormatPath();

	private:
		File _file{ };

		int32_t _hour{ 0 };
		int32_t _minute{ 0 };
		int32_t _second{ 0 };

		int64_t _time{ 0 };

		std::string _path{ };
	};
}


#endif // __LOGGER__DAILY_FILE_SINK__H__
