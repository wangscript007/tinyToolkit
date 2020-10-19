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


namespace debug
{
#if PLATFORM_TYPE == PLATFORM_WINDOWS

	/**
	 *
	 * 解析符号
	 *
	 * @param handle 句柄
	 * @param address 地址
	 *
	 * @return 符号信息
	 *
	 */
	static std::string WINAPI ParseSymbol(HANDLE handle, DWORD64 address)
	{
		DWORD displacementLine = 0;
		DWORD64 displacementSym = 0;

		char buffer[sizeof(IMAGEHLP_SYMBOL) + MAX_SYM_NAME]{ 0 };

		IMAGEHLP_LINE line{ };

		line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

		auto symbol = reinterpret_cast<PIMAGEHLP_SYMBOL64>(buffer);

		symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
		symbol->MaxNameLength = MAX_SYM_NAME;

		if (::SymGetSymFromAddr64(handle, address, &displacementSym, symbol) &&
		    ::SymGetLineFromAddr64(handle, address, &displacementLine, &line))
		{
			char content[1024]{ 0 };

			auto len = ::snprintf
			(
				content,
				sizeof(content),
				"%s:%ld(%s) [0x%008lx]",
				line.FileName,
				line.LineNumber,
				symbol->Name,
				static_cast<DWORD>(symbol->Address)
			);

			if (len < 0)
			{
				len = 0;
			}
			else if (len > NAME_MAX)
			{
				len = NAME_MAX;
			}

			content[len] = '\0';

			return content;
		}

		return { };
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

		void * stack[1024]{ };

		HANDLE hProcess = ::GetCurrentProcess();

		::SymInitialize(hProcess, nullptr, TRUE);

		WORD size = ::CaptureStackBackTrace(0, 1024, stack, nullptr);

		if (size <= 0)
		{
			return { };
		}

		content += "StackTrace [pid=";
		content += std::to_string(::GetCurrentProcessId());
		content += "] :";
		content += LINE_EOL;

		for (WORD i = 0; i < size; ++i)
		{
			auto temp = ParseSymbol(hProcess, reinterpret_cast<DWORD64>(stack[i]));

			if (temp.empty())
			{
				continue;
			}

			content += "    at ";
			content += temp;
			content += LINE_EOL;
		}

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
