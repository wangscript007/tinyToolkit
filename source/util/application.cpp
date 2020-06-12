/**
 *
 *  作者: hm
 *
 *  说明: 应用处理
 *
 */


#include "application.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <memory>
#  include <functional>
#
#  include <windows.h>
#  include <TlHelp32.h>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <climits>
#
#  include <pthread.h>
#  include <unistd.h>
#
#  include <mach-o/dyld.h>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <memory>
#  include <climits>
#  include <functional>
#
#  include <unistd.h>
#
#  include <sys/syscall.h>
#
#endif


namespace util
{
	/**
	 *
	 * 应用是否存在
	 *
	 * @param name 名称
	 *
	 * @return 应用是否存在
	 *
	 */
	bool Application::Exist(const std::string & name)
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hSnapshot
		(
			::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0),

			[](HANDLE handle)
			{
				if (handle && handle != INVALID_HANDLE_VALUE)
				{
					::CloseHandle(handle);
				}
			}
		);

		if (hSnapshot == nullptr || hSnapshot.get() == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		PROCESSENTRY32 process{ };

		process.dwSize = sizeof(PROCESSENTRY32);

		if (::Process32First(hSnapshot.get(), &process) == FALSE)
		{
			return false;
		}

		do
		{
			if (::strcmp(process.szExeFile, name.c_str()) == 0)
			{
				return true;
			}
		} while (::Process32Next(hSnapshot.get(), &process));

	#else

		std::string command{ };

		command += "ps -ef | grep ";
		command += name;
		command += " | grep -v grep | grep -v /";
		command += name;
		command += "/ | wc -l";

		std::unique_ptr<FILE, std::function<void(FILE *)>> handle
		(
			::popen(command.c_str(), "r"),

			[](FILE * file)
			{
				if (file)
				{
					::pclose(file);
				}
			}
		);

		if (handle == nullptr)
		{
			return false;
		}

		char buffer[16]{ 0 };

		if (::fgets(buffer, sizeof(buffer), handle.get()))
		{
			return ::strtol(buffer, nullptr, 10) >= 1;
		}

	#endif

		return false;
	}

	/**
	 *
	 * 线程序列号
	 *
	 * @return 线程序列号
	 *
	 */
	uint64_t Application::ThreadID()
	{
		uint64_t tid = 0;

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		tid = ::GetCurrentThreadId();

	#elif PLATFORM_TYPE == PLATFORM_LINUX

		tid = static_cast<uint64_t>(::syscall(SYS_gettid));

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		::pthread_threadid_np(nullptr, &tid);

	#endif

		return tid;
	}

	/**
	 *
	 * 进程序列号
	 *
	 * @return 进程序列号
	 *
	 */
	uint64_t Application::ProcessID()
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		return ::GetCurrentProcessId();

	#else

		return static_cast<uint64_t>(::getpid());

	#endif
	}

	/**
	 *
	 * 路径
	 *
	 * @return 路径
	 *
	 */
	std::string Application::Path()
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

		return path;
	}

	/**
	 *
	 * 名称
	 *
	 * @return 名称
	 *
	 */
	std::string Application::Name()
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

	/**
	 *
	 * 编译时间
	 *
	 * @param date 日期
	 * @param time 时间
	 *
	 * @return 编译时间
	 *
	 */
	std::string Application::CompileTime(const char * date, const char * time)
	{
		char buffer[20]{ 0 };

		auto len = ::snprintf
		(
			buffer,
			sizeof(buffer),
			"%04d-%02d-%02d %s",
			(((date[7] - '0') * 10 + (date[8] - '0')) * 10 + (date[9] - '0')) * 10 + (date[10] - '0'),

			date[2] == 'n' ? 1 :
			date[2] == 'b' ? 2 :
			date[2] == 'r' ? (date[0] == 'M' ? 3 : 4) :
			date[2] == 'y' ? 5 :
			date[2] == 'n' ? 6 :
			date[2] == 'l' ? 7 :
			date[2] == 'g' ? 8 :
			date[2] == 'p' ? 9 :
			date[2] == 't' ? 10 :
			date[2] == 'v' ? 11 : 12,

			(date[4] == ' ' ? 0 : date[4] - '0') * 10 + (date[5] - '0'),

			time
		);

		if (len < 0)
		{
			len = 0;
		}

		buffer[len] = '\0';

		return buffer;
	}
}
