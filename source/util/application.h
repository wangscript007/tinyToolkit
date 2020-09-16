#ifndef __UTIL__APPLICATION__H__
#define __UTIL__APPLICATION__H__


/**
 *
 *  作者: hm
 *
 *  说明: 应用处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <string>


namespace util
{
	class API_TYPE Application
	{
	public:
		/**
		 *
		 * 应用是否存在
		 *
		 * @param name 名称
		 *
		 * @return 应用是否存在
		 *
		 */
		static bool Exist(const std::string & name);

		/**
		 *
		 * 线程序列号
		 *
		 * @return 线程序列号
		 *
		 */
		static uint64_t ThreadID();

		/**
		 *
		 * 进程序列号
		 *
		 * @return 进程序列号
		 *
		 */
		static uint64_t ProcessID();

		/**
		 *
		 * 路径
		 *
		 * @return 路径
		 *
		 */
		static std::string Path();

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		static std::string Name();

		/**
		 *
		 * 编译时间
		 *
		 * @param date 日期
		 * @param time 时间
		 *
		 * @return 编译时间
		 *
		 */
		static std::string CompileTime(const char * date = __DATE__, const char * time = __TIME__);
	};
}


#endif // __UTIL__APPLICATION__H__
