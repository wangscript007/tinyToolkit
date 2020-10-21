#ifndef __CONTAINER__QUEUE__H__
#define __CONTAINER__QUEUE__H__


/**
 *
 *  作者: hm
 *
 *  说明: 队列
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <queue>
#include <condition_variable>


namespace tinyToolkit
{
	namespace container
	{
		template<typename ValueTypeT>
		class API_TYPE LockQueue
		{
		public:
			/**
			 *
			 * 压入
			 *
			 * @param value 内容
			 *
			 */
			void Push(ValueTypeT && value)
			{
				std::lock_guard<std::mutex> lock(_mutex);

				_queue.push(std::forward<ValueTypeT>(value));

				_condition.notify_one();
			}

			/**
			 *
			 * 弹出
			 *
			 */
			void Pop()
			{
				std::lock_guard<std::mutex> lock(_mutex);

				_queue.pop();
			}

			/**
			 *
			 * 弹出
			 *
			 * @param value 数据
			 *
			 */
			void Pop(ValueTypeT & value)
			{
				std::lock_guard<std::mutex> lock(_mutex);

				value = std::move(_queue.front());

				_queue.pop();
			}

			/**
			 *
			 * 等待弹出
			 *
			 */
			void WaitAndPop()
			{
				std::unique_lock<std::mutex> lock(_mutex);

				_condition.wait
				(
					lock,

					[this]()
					{
						return !_queue.empty();
					}
				);

				_queue.pop();
			}

			/**
			 *
			 * 等待弹出
			 *
			 * @param value 数据
			 *
			 */
			void WaiAndPop(ValueTypeT & value)
			{
				std::unique_lock<std::mutex> lock(_mutex);

				_condition.wait
				(
					lock,

					[this]()
					{
						return !_queue.empty();
					}
				);

				value = std::move(_queue.front());

				_queue.pop();
			}

			/**
			 *
			 * 尝试弹出
			 *
			 * @return 是否弹出成功
			 *
			 */
			bool TryPop()
			{
				std::lock_guard<std::mutex> lock(_mutex);

				if (_queue.empty())
				{
					return false;
				}

				_queue.pop();

				return true;
			}

			/**
			 *
			 * 尝试弹出
			 *
			 * @param value 数据
			 *
			 * @return 是否弹出成功
			 *
			 */
			bool TryPop(ValueTypeT & value)
			{
				std::lock_guard<std::mutex> lock(_mutex);

				if (_queue.empty())
				{
					return false;
				}

				value = std::move(_queue.front());

				_queue.pop();

				return true;
			}

			/**
			 *
			 * 是否为空
			 *
			 * @return 是否为空
			 *
			 */
			bool Empty() const
			{
				std::lock_guard<std::mutex> lock(_mutex);

				return _queue.empty();
			}

			/**
			 *
			 * 队列大小
			 *
			 * @return 队列大小
			 *
			 */
			std::size_t Size() const
			{
				std::lock_guard<std::mutex> lock(_mutex);

				return _queue.size();
			}

			/**
			 *
			 * 尾部
			 *
			 * @return 数据
			 *
			 */
			ValueTypeT & Back()
			{
				std::lock_guard<std::mutex> lock(_mutex);

				return _queue.back();
			}

			/**
			 *
			 * 尾部
			 *
			 * @return 数据
			 *
			 */
			const ValueTypeT & Back() const
			{
				std::lock_guard<std::mutex> lock(_mutex);

				return _queue.back();
			}

			/**
			 *
			 * 头部
			 *
			 * @return 数据
			 *
			 */
			ValueTypeT & Front()
			{
				std::lock_guard<std::mutex> lock(_mutex);

				return _queue.front();
			}

			/**
			 *
			 * 头部
			 *
			 * @return 数据
			 *
			 */
			const ValueTypeT & Front() const
			{
				std::lock_guard<std::mutex> lock(_mutex);

				return _queue.front();
			}

		private:
			mutable std::mutex _mutex{ };

			std::queue<ValueTypeT> _queue{ };

			std::condition_variable _condition{ };
		};
	}
}


#endif // __CONTAINER__QUEUE__H__
