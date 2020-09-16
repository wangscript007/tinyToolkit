#ifndef __UTIL__LATCH__H__
#define __UTIL__LATCH__H__


/**
 *
 *  作者: hm
 *
 *  说明: 闭锁
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <condition_variable>


namespace util
{
	class API_TYPE CountLatch
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param count 计数
		 *
		 */
		explicit CountLatch(uint32_t count);

		/**
		 *
		 * 等待
		 *
		 */
		void Wait();

		/**
		 *
		 * 触发
		 *
		 */
		void Down();

		/**
		 *
		 * 剩余计数
		 *
		 * @return 剩余计数
		 *
		 */
		uint32_t RemainingCount();

	private:
		uint32_t _count{ 0 };

		std::mutex _mutex{ };

		std::condition_variable _condition{ };
	};
}


#endif // __UTIL__LATCH__H__
