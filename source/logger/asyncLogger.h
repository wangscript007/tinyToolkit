#ifndef __LOGGER__ASYNC_LOGGER__H__
#define __LOGGER__ASYNC_LOGGER__H__


/**
 *
 *  作者: hm
 *
 *  说明: 异步日志
 *
 */


#include "logger.h"

#include <ctime>
#include <queue>
#include <thread>
#include <condition_variable>


namespace logger
{
	class API_TYPE AsyncLogger : public ILogger
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		AsyncLogger();

		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 *
		 */
		explicit AsyncLogger(std::string name);

		/**
		 *
		 * 析构函数
		 *
		 */
		~AsyncLogger() override = default;

		/**
		 *
		 * 单例对象
		 *
		 * @return 单例对象
		 *
		 */
		static AsyncLogger & Instance();

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

		int64_t _second{ 0 };
		int64_t _minutes{ 0 };

		std::thread _thread{ };

		std::queue<Context> _queue{ };

		std::condition_variable _condition{ };
	};
}


#endif // __LOGGER__ASYNC_LOGGER__H__
