/**
 *
 *  作者: hm
 *
 *  说明: 系统处理
 *
 */


#include "system.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <windows.h>
#
#else
#
#  include <pwd.h>
#  include <unistd.h>
#
#endif


namespace tinyToolkit
{
	namespace util
	{
		/**
		 *
		 * 是否是大端字节序
		 *
		 * @return 是否是大端字节序
		 *
		 */
		bool System::IsBigEndian()
		{
			static uint32_t value = 0x0001;

			return *(reinterpret_cast<uint8_t *>(&value)) == 0;
		}

		/**
		 *
		 * 是否是小端字节序
		 *
		 * @return 是否是小端字节序
		 *
		 */
		bool System::IsLittleEndian()
		{
			static uint32_t value = 0x0001;

			return *(reinterpret_cast<uint8_t *>(&value)) == 1;
		}

		/**
		 *
		 * 处理器个数
		 *
		 * @return 处理器个数
		 *
		 */
		uint32_t System::ProcessorCount()
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			SYSTEM_INFO info{ };

			::GetSystemInfo(&info);

			return info.dwNumberOfProcessors;

		#else

			return static_cast<uint32_t>(::sysconf(_SC_NPROCESSORS_CONF));

		#endif
		}

		/**
		 *
		 * 用户名
		 *
		 * @return 用户名
		 *
		 */
		std::string System::UserName()
		{
			char name[NAME_MAX + 1]{ 0 };

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			DWORD size = NAME_MAX;

			if (::GetUserName(name, &size) == FALSE)
			{
				return { };
			}

		#else

			struct passwd   pwd{ };
			struct passwd * result = nullptr;

			::getpwuid_r(::getuid(), &pwd, name, NAME_MAX, &result);

			if (result == nullptr)
			{
				return { };
			}

		#endif

			return name;
		}

		/**
		 *
		 * 计算机名称
		 *
		 * @return 计算机名称
		 *
		 */
		std::string System::ComputerName()
		{
			char name[NAME_MAX + 1]{ 0 };

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			DWORD size = NAME_MAX;

			if (::GetComputerName(name, &size) == FALSE)
			{
				return { };
			}

		#else

			if (::gethostname(name, NAME_MAX))
			{
				return { };
			}

		#endif

			return name;
		}
	}
}
