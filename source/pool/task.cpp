/**
 *
 *  作者: hm
 *
 *  说明: 任务池
 *
 */


#include "task.h"


namespace pool
{
	/**
	 *
	 * 构造函数
	 *
	 * @param count 线程个数
	 *
	 */
	TaskPool::TaskPool(std::size_t count)
	{
		_idles.store(count);

		for (std::size_t i = 0; i < count; ++i)
		{
			_threads.emplace_back
			(
				[this]()
				{
					std::function<void()> task{ };

					while (true)
					{
						{
							std::unique_lock<std::mutex> lock(_mutex);

							_condition.wait
							(
								lock,

								[this]
								{
									if (_tasks.empty())
									{
										return _isClose;
									}
									else
									{
										return !_isPause;
									}
								}
							);

							if (_isClose)
							{
								return;
							}

							task = std::move(_tasks.front());

							_tasks.pop();
						}

						--_idles;

						task();

						++_idles;
					}
				}
			);
		}

		_isValid = true;
	}

	/**
	 *
	 * 析构函数
	 *
	 */
	TaskPool::~TaskPool()
	{
		Close();

		_threads.clear();
		_threads.shrink_to_fit();
	}

	/**
	 *
	 * 等待
	 *
	 */
	void TaskPool::Wait() const
	{
		while (!IsIdle())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	/**
	 *
	 * 关闭
	 *
	 */
	void TaskPool::Close()
	{
		_isClose = true;

		_condition.notify_all();

		for (auto && thread : _threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
	}

	/**
	 *
	 * 暂停
	 *
	 */
	void TaskPool::Pause()
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_isPause = true;
	}

	/**
	 *
	 * 恢复
	 *
	 */
	void TaskPool::Resume()
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_isPause = false;

		_condition.notify_all();
	}

	/**
	 *
	 * 是否为空闲状态
	 *
	 * @return 是否为空闲状态
	 *
	 */
	bool TaskPool::IsIdle() const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		return _tasks.empty() && _idles == _threads.size();
	}

	/**
	 *
	 * 是否为关闭状态
	 *
	 * @return 是否为关闭状态
	 *
	 */
	bool TaskPool::IsClose() const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		return _isClose;
	}

	/**
	 *
	 * 是否为暂停状态
	 *
	 * @return 是否为暂停状态
	 *
	 */
	bool TaskPool::IsPause() const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		return _isPause;
	}

	/**
	 *
	 * 是否有效
	 *
	 * @return 是否有效
	 *
	 */
	bool TaskPool::IsValid() const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		return _isValid;
	}

	/**
	 *
	 * 任务个数
	 *
	 * @return 任务个数
	 *
	 */
	std::size_t TaskPool::TaskSize() const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		return _tasks.size();
	}

	/**
	 *
	 * 线程个数
	 *
	 * @return 线程个数
	 *
	 */
	std::size_t TaskPool::ThreadSize() const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		return _threads.size();
	}
}
