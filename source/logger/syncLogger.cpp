/**
 *
 *  作者: hm
 *
 *  说明: 同步日志
 *
 */


#include "syncLogger.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <windows.h>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <mach-o/dyld.h>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <climits>
#
#  include <unistd.h>
#
#endif


namespace logger
{
	/**
	 *
	 * 名称
	 *
	 * @return 名称
	 *
	 */
	static std::string ApplicationName()
	{
		char path[PATH_MAX + 1]{ 0 };

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		auto size = ::GetModuleFileName(nullptr, path, PATH_MAX);

	#elif PLATFORM_TYPE == PLATFORM_LINUX

		auto size = ::readlink("/proc/self/exe", path, PATH_MAX);

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		uint32_t size = PATH_MAX;

		::_NSGetExecutablePath(path, &size);

	#endif

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
				return path + i + 1;
			}
		}

		return path;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 构造函数
	 *
	 */
	SyncLogger::SyncLogger() : SyncLogger(ApplicationName())
	{

	}

	/**
	 *
	 * 构造函数
	 *
	 * @param name 名称
	 *
	 */
	SyncLogger::SyncLogger(std::string name) : ILogger(std::move(name))
	{

	}

	/**
	 *
	 * 等待
	 *
	 */
	void SyncLogger::Wait()
	{

	}

	/**
	 *
	 * 关闭
	 *
	 */
	void SyncLogger::Close()
	{
		if (!IsValid())
		{
			return;
		}

		std::lock_guard<std::mutex> lock(_mutex);

		for (auto && iter : _sinks)
		{
			iter.second->Close();
		}

		_sinks.clear();

		_isValid = false;
	}

	/**
	 *
	 * 刷新
	 *
	 */
	void SyncLogger::Flush()
	{
		if (!IsValid())
		{
			return;
		}

		std::lock_guard<std::mutex> lock(_mutex);

		for (auto && iter : _sinks)
		{
			iter.second->Flush();
		}
	}

	/**
	 *
	 * 写入内容
	 *
	 * @param context 上下文
	 *
	 */
	void SyncLogger::Write(Context & context)
	{
		if (!IsValid())
		{
			return;
		}

		std::lock_guard<std::mutex> lock(_mutex);

		context.timePoint = std::chrono::system_clock::now();

		std::time_t second = std::chrono::duration_cast<std::chrono::seconds>(context.timePoint.time_since_epoch()).count();

		if (second == _second)  /// 同一秒生成的日志
		{
			/// 不需要处理
		}
		else if (second / 60 == _minutes)  /// 同一分钟生成的日志
		{
			_second = second;

			_tm.tm_sec = static_cast<int32_t>(_second % 60);  /// 更新秒
		}
		else  /// 不同分钟生成的日志
		{
			_minutes = second / 60;

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			::localtime_s(&_tm, &second);

		#else

			::localtime_r(&second, &_tm);

		#endif
		}

		context.tm = _tm;

		for (auto && iter : _sinks)
		{
			iter.second->Write(context);
		}
	}
}
