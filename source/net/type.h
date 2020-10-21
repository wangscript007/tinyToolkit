#ifndef __NET__TYPE__H__
#define __NET__TYPE__H__


/**
 *
 *  作者: hm
 *
 *  说明: 类型
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <cstdint>


namespace tinyToolkit
{
	namespace net
	{
		enum class NET_OPTION_TYPE : uint8_t
		{
			IO,
			SEND,
			RECEIVE,
			INVALID,
		};
	}
}


#endif // __NET__TYPE__H__
