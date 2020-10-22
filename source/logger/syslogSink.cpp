/**
 *
 *  作者: hm
 *
 *  说明: 系统节点
 *
 */


#include "syslogSink.h"

#if PLATFORM_TYPE == PLATFORM_MIPS || PLATFORM_TYPE == PLATFORM_APPLE || PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <syslog.h>
#
#endif

#include <map>


namespace tinyToolkit
{
	namespace logger
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 *
		 */
		SyslogSink::SyslogSink(std::string name) : ISink(std::move(name))
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			char path[PATH_MAX + 1]{ 0 };

			auto size = ::GetModuleFileName(nullptr, path, PATH_MAX);

			if (size < 0)
			{
				size = 0;
			}
			else if (size > PATH_MAX)
			{
				size = PATH_MAX;
			}

			path[size] = '\0';

			for (auto i = size; i > 0; --i)
			{
				if (path[i] == PATH_SEP[0])
				{
					_handle = ::RegisterEventSource(nullptr, path + i + 1);

					return;
				}
			}

			_handle = ::RegisterEventSource(nullptr, path);

		#else

			::openlog(nullptr, LOG_CONS, LOG_USER);

		#endif
		}

		/**
		 *
		 * 析构函数
		 *
		 */
		SyslogSink::~SyslogSink()
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			if (_handle)
			{
				::DeregisterEventSource(_handle);
			}

		#else

			::closelog();

		#endif
		}

		/**
		 *
		 * 关闭节点
		 *
		 */
		void SyslogSink::Close()
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			if (_handle)
			{
				::DeregisterEventSource(_handle);
			}

		#else

			::closelog();

		#endif
		}

		/**
		 *
		 * 刷新节点
		 *
		 */
		void SyslogSink::Flush()
		{

		}

		/**
		 *
		 * 写入内容
		 *
		 * @param context 上下文
		 *
		 */
		void SyslogSink::Write(const Context & context)
		{
			if (Filter() && Filter()->Decide(context))
			{
				return;
			}

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			static std::map<LOG_PRIORITY_TYPE, int32_t> priorities
			{
				{ LOG_PRIORITY_TYPE::DEBUGS, EVENTLOG_INFORMATION_TYPE },
				{ LOG_PRIORITY_TYPE::INFO, EVENTLOG_INFORMATION_TYPE },
				{ LOG_PRIORITY_TYPE::NOTICE, EVENTLOG_INFORMATION_TYPE },
				{ LOG_PRIORITY_TYPE::WARNING, EVENTLOG_WARNING_TYPE },
				{ LOG_PRIORITY_TYPE::ERRORS, EVENTLOG_ERROR_TYPE },
				{ LOG_PRIORITY_TYPE::CRITICAL, EVENTLOG_ERROR_TYPE },
				{ LOG_PRIORITY_TYPE::ALERT, EVENTLOG_ERROR_TYPE },
				{ LOG_PRIORITY_TYPE::FATAL, EVENTLOG_ERROR_TYPE },
			};

			const char * ps[1]{ nullptr };

			if (Layout())
			{
				std::string content(Layout()->Format(context));

				ps[0] = content.c_str();

				::ReportEvent(_handle, priorities[context.priority], 0, ::GetCurrentProcessId(), nullptr, 1, 0, ps, nullptr);
			}
			else
			{
				ps[0] = context.content.c_str();

				::ReportEvent(_handle, priorities[context.priority], 0, ::GetCurrentProcessId(), nullptr, 1, 0, ps, nullptr);
			}

		#else

			static std::map<LOG_PRIORITY_TYPE, int32_t> priorities
			{
				{ LOG_PRIORITY_TYPE::DEBUGS, LOG_DEBUG },
				{ LOG_PRIORITY_TYPE::INFO, LOG_INFO },
				{ LOG_PRIORITY_TYPE::NOTICE, LOG_NOTICE },
				{ LOG_PRIORITY_TYPE::WARNING, LOG_WARNING },
				{ LOG_PRIORITY_TYPE::ERRORS, LOG_ERR },
				{ LOG_PRIORITY_TYPE::CRITICAL, LOG_CRIT },
				{ LOG_PRIORITY_TYPE::ALERT, LOG_ALERT },
				{ LOG_PRIORITY_TYPE::FATAL, LOG_EMERG },
			};

			if (Layout())
			{
				std::string content(Layout()->Format(context));

				::syslog(priorities[context.priority], "%s", content.c_str());
			}
			else
			{
				::syslog(priorities[context.priority], "%s", context.content.c_str());
			}

		#endif

			if (IsAutoFlush())
			{
				Flush();
			}
		}
	}
}
