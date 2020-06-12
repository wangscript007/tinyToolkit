#ifndef __LOGGER__SYNC_LOGGER__H__
#define __LOGGER__SYNC_LOGGER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 同步日志
 *
 */


#include "logger.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <ctime>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#
#
#endif


namespace logger
{
	class API_TYPE SyncLogger : public ILogger
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		SyncLogger();

		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 *
		 */
		explicit SyncLogger(std::string name);

		/**
		 *
		 * 析构函数
		 *
		 */
		~SyncLogger() override = default;

		/**
		 *
		 * 等待
		 *
		 */
		void Wait() override;

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
		void Write(Context & context) override;

	private:
		std::tm _tm{ };

		std::time_t _second{ 0 };
		std::time_t _minutes{ 0 };
	};
}


#endif // __LOGGER__SYNC_LOGGER__H__
