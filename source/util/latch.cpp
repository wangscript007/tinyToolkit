/**
 *
 *  作者: hm
 *
 *  说明: 闭锁
 *
 */


#include "latch.h"


namespace tinyToolkit
{
	namespace util
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param count 计数
		 *
		 */
		CountLatch::CountLatch(uint32_t count) : _count(count)
		{

		}

		/**
		 *
		 * 等待
		 *
		 */
		void CountLatch::Wait()
		{
			std::unique_lock<std::mutex> lock(_mutex);

			_condition.wait
			(
				lock,

				[this]()
				{
					return _count == 0;
				}
			);
		}

		/**
		 *
		 * 触发
		 *
		 */
		void CountLatch::Down()
		{
			std::lock_guard<std::mutex> lock(_mutex);

			if (_count == 0)
			{
				return;
			}

			if (--_count == 0)
			{
				_condition.notify_all();
			}
		}

		/**
		 *
		 * 剩余计数
		 *
		 * @return 剩余计数
		 *
		 */
		uint32_t CountLatch::RemainingCount()
		{
			std::lock_guard<std::mutex> lock(_mutex);

			return _count;
		}
	}
}
