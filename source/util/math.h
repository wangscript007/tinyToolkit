#ifndef __UTIL__MATH__H__
#define __UTIL__MATH__H__


/**
 *
 *  作者: hm
 *
 *  说明: 数学处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <type_traits>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <type_traits>
#
#endif


namespace util
{
	class API_TYPE Math
	{
	public:
		/***
		 *
		 * 是否为奇数
		 *
		 * @param content 内容
		 *
		 * @return 是否为奇数
		 *
		 */
		template <typename ContentTypeT>
		static bool IsOdd(ContentTypeT content)
		{
			static_assert(std::is_integral<ContentTypeT>::value, "Template must be an integral type");

			return (content & 1) != 0;
		}

		/**
		 *
		 * 是否为偶数
		 *
		 * @param content 数字
		 *
		 * @return 是否为偶数
		 *
		 */
		template <typename ContentTypeT>
		static bool IsEven(ContentTypeT content)
		{
			static_assert(std::is_integral<ContentTypeT>::value, "Template must be an integral type");

			return (content & 1) == 0;
		}
	};
}


#endif // __UTIL__MATH__H__
