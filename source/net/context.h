#ifndef __NET__CONTEXT__H__
#define __NET__CONTEXT__H__


/**
 *
 *  作者: hm
 *
 *  说明: 上下文
 *
 */


#include "type.h"
#include "define.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <winsock2.h>
#
#endif


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE Channel;

		class API_TYPE Context
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param option 操作
			 *
			 */
			explicit Context(NET_OPTION_TYPE option = NET_OPTION_TYPE::INVALID);

		public:
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			OVERLAPPED overlap{ 0 };

			WSABUF buffer{ 0 };

			int32_t bytes{ 0 };

			char temp[1460]{ 0 };

			bool status{ false };

		#endif

			Channel * channel{ nullptr };

			NET_OPTION_TYPE optionType{ NET_OPTION_TYPE::INVALID };

			SOCKET_HANDLE_TYPE handle{ SOCKET_HANDLE_INVALID };
		};
	}
}


#endif // __NET__CONTEXT__H__
