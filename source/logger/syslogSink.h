#ifndef __LOGGER__SYSLOG_SINK__H__
#define __LOGGER__SYSLOG_SINK__H__


/**
 *
 *  作者: hm
 *
 *  说明: 系统节点
 *
 */


#include "sink.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <windows.h>
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
	class API_TYPE SyslogSink : public ISink
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 *
		 */
		explicit SyslogSink(std::string name);

		/**
		 *
		 * 析构函数
		 *
		 */
		~SyslogSink() override;

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

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

	private:

		HANDLE _handle{ };

	#endif
	};
}


#endif // __LOGGER__SYSLOG_SINK__H__
