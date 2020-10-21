/**
 *
 *  作者: hm
 *
 *  说明: 堆栈信息
 *
 */


#include "stackTrace.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <windows.h>
#  include <DbgHelp.h>
#
#  pragma comment( lib, "dbghelp.lib")
#
#else
#
#  include <memory>
#
#  include <unistd.h>
#  include <cxxabi.h>
#  include <execinfo.h>
#
#endif


namespace tinyToolkit
{
	namespace debug
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		/**
		 *
		 * 格式化符号
		 *
		 * @param content 内容
		 * @param format 格式化
		 * @param args 参数
		 *
		 */
		template <typename ... Args>
		static void WINAPI FormatSymbol(std::string & content, const char * format, Args &&... args)
		{
			char buffer[MAX_SYM_NAME]{ 0 };

			auto len = ::snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);

			if (len < 0)
			{
				len = 0;
			}
			else if (len > MAX_SYM_NAME)
			{
				len = MAX_SYM_NAME;
			}

			buffer[len] = '\0';

			content.append(buffer, len);
			content.append(LINE_EOL);
		}

		/**
		 *
		 * 解析符号
		 *
		 * @param handle 句柄
		 * @param content 内容
		 *
		 */
		static void WINAPI ParseSymbol(HANDLE handle, std::string & content)
		{
			CONTEXT ctx{ 0 };

			ctx.ContextFlags = CONTEXT_FULL;

			::RtlCaptureContext(&ctx);

			STACKFRAME64 stackFrame{ 0 };

			::memset(&stackFrame, 0, sizeof(STACKFRAME64));

		#ifdef _M_IX86

			DWORD machineType = IMAGE_FILE_MACHINE_I386;

			stackFrame.AddrPC.Offset = ctx.Eip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = ctx.Ebp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = ctx.Esp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#elif _M_X64

			DWORD machineType = IMAGE_FILE_MACHINE_AMD64;

			stackFrame.AddrPC.Offset = ctx.Rip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = ctx.Rsp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = ctx.Rsp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#elif _M_IA64

			DWORD machineType = IMAGE_FILE_MACHINE_IA64;

			stackFrame.AddrPC.Offset = c.StIIP;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = c.IntSp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrBStore.Offset = c.RsBSP;
			stackFrame.AddrBStore.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = c.IntSp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

		#else
		#error "Platform not supported!"
		#endif

			IMAGEHLP_LINE64 line{ };

			::memset(&line, 0, sizeof(IMAGEHLP_LINE64));

			line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

			IMAGEHLP_MODULE64 module{ };

			::memset(&module, 0, sizeof(IMAGEHLP_MODULE64));

			module.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

			auto symbol = (IMAGEHLP_SYMBOL64 *)::malloc(sizeof(IMAGEHLP_SYMBOL64) + MAX_SYM_NAME);

			if (symbol == nullptr)
			{
				return;
			}

			::memset(symbol, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);

			symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
			symbol->MaxNameLength = MAX_SYM_NAME;

			auto hThread = ::GetCurrentThread();

			for (;;)
			{
				if (::StackWalk64(machineType, handle, hThread, &stackFrame, &ctx, nullptr, ::SymFunctionTableAccess64, ::SymGetModuleBase64, nullptr) == FALSE)
				{
					break;
				}

				if (stackFrame.AddrPC.Offset == 0)
				{
					break;
				}

				DWORD displacementLine{ 0 };
				DWORD64 displacementSym{ 0 };

				auto lineRet = ::SymGetLineFromAddr64(handle, stackFrame.AddrPC.Offset, &displacementLine, &line);
				auto moduleRet = ::SymGetModuleInfo64(handle, stackFrame.AddrPC.Offset, &module);
				auto symbolRet = ::SymGetSymFromAddr64(handle, stackFrame.AddrPC.Offset, &displacementSym, symbol);

				if (lineRet)
				{
					FormatSymbol(content, "    at %s:%ld(%s) [%s 0x%08llx]", line.FileName, line.LineNumber, symbolRet ? symbol->Name : "function-name not available", moduleRet ? module.ModuleName : "(module-name not available)", "(filename not available)", symbol->Address);
				}
				else
				{
					FormatSymbol(content, "    at %s(%s) [%s 0x%08llx]", "(filename not available)", symbolRet ? symbol->Name : "(function-name not available)", moduleRet ? module.ModuleName : "(module-name not available)", "(filename not available)");
				}
			}

			::free(symbol);
		}

	#elif PLATFORM_TYPE != PLATFORM_MIPS

		/**
		 *
		 * 解析符号
		 *
		 * @param symbol 符号
		 *
		 * @return 符号信息
		 *
		 */
		static std::string ParseSymbol(const std::string & symbol)
		{
			std::size_t pos = 0;
			std::size_t head;
			std::size_t tail;

			std::string content{ };

			while (pos < symbol.size())
			{
				head = symbol.find("_Z", pos);

				if (head == std::string::npos)
				{
					content += symbol.substr(pos);

					break;
				}

				tail = symbol.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", head);

				if (tail == std::string::npos)
				{
					tail = symbol.size();
				}

				int32_t status = 0;

				std::unique_ptr<char, void(*)(void *)> temp
				{
					abi::__cxa_demangle
					(
						symbol.substr(head, tail - head).c_str(),
						nullptr,
						nullptr,
						&status
					),
					std::free
				};

				if (status == 0)
				{
					content += symbol.substr(pos, head - pos);
					content += temp.get();

					pos = tail;
				}
				else
				{
					pos = head + 2;
				}
			}

			return content;
		}

	#endif


		////////////////////////////////////////////////////////////////////////////////////////////////////


		/**
		 *
		 * 内容
		 *
		 * @return 内容
		 *
		 */
		std::string StackTrace::Content()
		{
			std::string content{ };

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			HANDLE hProcess = ::GetCurrentProcess();

			if (::SymInitialize(hProcess, nullptr, TRUE) == FALSE)
			{
				return { };
			}

			::SymSetOptions(::SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_FAIL_CRITICAL_ERRORS);

			content += "StackTrace [pid=";
			content += std::to_string(::GetCurrentProcessId());
			content += "] :";
			content += LINE_EOL;

			ParseSymbol(hProcess, content);

		#elif PLATFORM_TYPE != PLATFORM_MIPS

			void * stack[1024]{ };

			auto size = ::backtrace(stack, 1024);

			if (size <= 0)
			{
				return { };
			}

			std::unique_ptr<char *, void(*)(void *)> symbols
			(
				::backtrace_symbols(stack, size),
				std::free
			);

			content += "StackTrace [pid=";
			content += std::to_string(::getpid());
			content += "] :";
			content += LINE_EOL;

			for (int32_t i = 0; i < size; ++i)
			{
				auto temp = ParseSymbol(symbols.get()[i]);

				if (temp.empty())
				{
					continue;
				}

				content += "    at ";
				content += temp;
				content += LINE_EOL;
			}

		#endif

			return content;
		}
	}
}
