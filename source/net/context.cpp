/**
 *
 *  作者: hm
 *
 *  说明: 上下文
 *
 */


#include "context.h"


namespace tinyToolkit
{
	namespace net
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param option 操作
		 *
		 */
		Context::Context(NET_OPTION_TYPE option) : optionType(option)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			::memset(&buffer,  0, sizeof(WSABUF));
			::memset(&overlap, 0, sizeof(OVERLAPPED));

		#endif
		}
	}
}
