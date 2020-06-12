#ifndef __DEBUG__DUMP__H__
#define __DEBUG__DUMP__H__


/**
 *
 *  作者: hm
 *
 *  说明: 转储
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


namespace debug
{
	class API_TYPE Dump
	{
	public:
		/**
		 *
		 * 注册
		 *
		 */
		static void Register();

		/**
		 *
		 * 注销
		 *
		 */
		static void UnRegister();
	};
}


#endif // __DEBUG__DUMP__H__
