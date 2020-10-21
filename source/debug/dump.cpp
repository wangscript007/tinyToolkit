/**
 *
 *  作者: hm
 *
 *  说明: 转储
 *
 */


#include "dump.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <chrono>
#  include <string>
#  include <memory>
#  include <functional>
#
#  include <windows.h>
#  include <DbgHelp.h>
#
#  pragma comment( lib, "dbghelp.lib")
#
#endif


namespace tinyToolkit
{
	namespace debug
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		static LPTOP_LEVEL_EXCEPTION_FILTER sExceptionFilter = nullptr;

		/**
		 *
		 * 是否是需要的文件
		 *
		 * @param path 路径
		 *
		 * @return 是否是需要的文件
		 *
		 */
		BOOL WINAPI IsNeedFile(const WCHAR * path)
		{
			if (path == nullptr)
			{
				return FALSE;
			}

			WCHAR file[NAME_MAX + 1]{ };

			::_wsplitpath_s(path, nullptr, 0, nullptr, 0, file, NAME_MAX, nullptr, 0);

			return ::_wcsicmp(file, L"ntdll") == 0 ? TRUE : FALSE;
		}

		/**
		 *
		 * 转储文件回调函数
		 *
		 * @param param 参数
		 * @param input 输入
		 * @param output 输出
		 *
		 * @return 是否转储成功
		 *
		 */
		BOOL WINAPI DumpCallback(PVOID param, PMINIDUMP_CALLBACK_INPUT input, PMINIDUMP_CALLBACK_OUTPUT output)
		{
			(void)param;

			if (input == nullptr || output == nullptr)
			{
				return FALSE;
			}

			switch (input->CallbackType)
			{
				case ModuleCallback:
				{
					if (output->ModuleWriteFlags & ModuleWriteDataSeg)
					{
						if (!IsNeedFile(input->Module.FullPath))
						{
							output->ModuleWriteFlags &= (~ModuleWriteDataSeg);
						}
					}
				}

				case ThreadCallback:
				case ThreadExCallback:
				case IncludeModuleCallback:
				case IncludeThreadCallback:
				{
					return TRUE;
				}

				default:
				{
					break;
				}
			}

			return FALSE;
		}

		/**
		 *
		 * 转储时间
		 *
		 * @return 转储时间
		 *
		 */
		std::string WINAPI DumpTime()
		{
			std::tm now{ };

			int64_t current = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() + (8 * 3600);

			::gmtime_s(&now, &current);

			char str[NAME_MAX + 1]{ 0 };

			auto len = ::snprintf
			(
				str,
				NAME_MAX,
				"%4d_%02d_%02d_%02d_%02d_%02d",
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

			str[len] = '\0';

			return str;
		}

		/**
		 *
		 * 转储文件
		 *
		 * @return 转储文件
		 *
		 */
		std::string WINAPI DumpFile()
		{
			char path[PATH_MAX + 1]{ 0 };

			DWORD size = ::GetModuleFileName(nullptr, path, PATH_MAX);

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
		 * 创建最小转储文件
		 *
		 * @param exception 异常
		 *
		 */
		void WINAPI CreateMiniDump(PEXCEPTION_POINTERS exception)
		{
			std::string file{ };

			file += DumpFile();
			file += ".";
			file += DumpTime();
			file += ".dmp";

			std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hFile
			(
				::CreateFile(file.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr),

				[](HANDLE handle)
				{
					if (handle && (handle != INVALID_HANDLE_VALUE))
					{
						::CloseHandle(handle);
					}
				}
			);

			if (hFile == nullptr || hFile.get() == INVALID_HANDLE_VALUE)
			{
				return;
			}

			MINIDUMP_EXCEPTION_INFORMATION exceptionInformation{ };

			exceptionInformation.ThreadId = ::GetCurrentThreadId();
			exceptionInformation.ExceptionPointers = exception;
			exceptionInformation.ClientPointers = FALSE;

			MINIDUMP_CALLBACK_INFORMATION callbackInformation{ };

			callbackInformation.CallbackRoutine = static_cast<MINIDUMP_CALLBACK_ROUTINE>(DumpCallback);
			callbackInformation.CallbackParam = nullptr;

			MiniDumpWriteDump
			(
				::GetCurrentProcess(),
				::GetCurrentProcessId(),
				hFile.get(),
				static_cast<MINIDUMP_TYPE>(MiniDumpWithFullMemory | MiniDumpWithHandleData | MiniDumpWithFullMemoryInfo | MiniDumpWithThreadInfo | MiniDumpWithFullAuxiliaryState | MiniDumpIgnoreInaccessibleMemory),
				&exceptionInformation,
				nullptr,
				&callbackInformation
			);
		}

		/**
		 *
		 * 异常处理
		 *
		 * @param exception 异常
		 *
		 * @return 异常处理结果
		 *
		 */
		LONG WINAPI ExceptionHandler(PEXCEPTION_POINTERS exception)
		{
			CreateMiniDump(exception);

			return EXCEPTION_EXECUTE_HANDLER;
		}

	#endif


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 注册
		 *
		 */
		void Dump::Register()
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			sExceptionFilter = ::SetUnhandledExceptionFilter(ExceptionHandler);

		#endif
		}

		/**
		 *
		 * 注销
		 *
		 */
		void Dump::UnRegister()
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			if (sExceptionFilter)
			{
				::SetUnhandledExceptionFilter(sExceptionFilter);

				sExceptionFilter = nullptr;
			}

		#endif
		}
	}
}
