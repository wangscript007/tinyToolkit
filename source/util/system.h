#ifndef __UTIL__SYSTEM__H__
#define __UTIL__SYSTEM__H__


/**
 *
 *  作者: hm
 *
 *  说明: 系统处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <string>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <string>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <string>
#
#endif


namespace util
{
	class API_TYPE System
	{
	public:
		/**
		 *
		 * 是否是大端字节序
		 *
		 * @return 是否是大端字节序
		 *
		 */
		static bool IsBigEndian();

		/**
		 *
		 * 是否是小端字节序
		 *
		 * @return 是否是小端字节序
		 *
		 */
		static bool IsLittleEndian();

		/**
		 *
		 * 处理器个数
		 *
		 * @return 处理器个数
		 *
		 */
		static uint32_t ProcessorCount();

		/**
		 *
		 * 用户名
		 *
		 * @return 用户名
		 *
		 */
		static std::string UserName();

		/**
		 *
		 * 计算机名称
		 *
		 * @return 计算机名称
		 *
		 */
		static std::string ComputerName();
	};
}


#endif // __UTIL__SYSTEM__H__
