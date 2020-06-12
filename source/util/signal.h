#ifndef __UTIL__SIGNAL__H__
#define __UTIL__SIGNAL__H__


/**
 *
 *  作者: hm
 *
 *  说明: 信号处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <cstdint>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <cstdint>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <cstdint>
#
#endif


namespace util
{
	class API_TYPE Signal
	{
	public:
		/**
		 *
		 * 注册信号动作
		 *
		 * @param signalNo 信号量
		 * @param callback 回调函数
		 *
		 */
		static void RegisterAction(int32_t signalNo, void(* callback)(int32_t));

		/**
		 *
		 * 注册忽略信号
		 *
		 */
		static void RegisterIgnore();

		/**
		 *
		 * 注册结束信号
		 *
		 * @param callback 回调函数
		 *
		 */
		static void RegisterTerminate(void(* callback)(int32_t));

		/**
		 *
		 * 注册异常信号
		 *
		 * @param callback 回调函数
		 *
		 */
		static void RegisterException(void(* callback)(int32_t));

		/**
		 *
		 * 向自身发送信号
		 *
		 * @param signalNo 信号量
		 *
		 * @return 是否发送成功
		 *
		 */
		static bool Raise(int32_t signalNo);
	};
}


#endif // __UTIL__SIGNAL__H__
