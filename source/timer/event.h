#ifndef __TIMER__EVENT__H__
#define __TIMER__EVENT__H__


/**
 *
 *  作者: hm
 *
 *  说明: 事件
 *
 */


#include "task.h"

#include <ctime>
#include <memory>


namespace timer
{
	class API_TYPE Event
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param task 任务
		 * @param count 次数
		 * @param expire 到期时间
		 * @param interval 间隔(毫秒)
		 *
		 */
		Event(std::shared_ptr<ITask> task, int64_t count, int64_t expire, int64_t interval);

		/**
		 *
		 * 析构函数
		 *
		 */
		~Event();

		/**
		 *
		 * 杀死
		 *
		 */
		void Kill();

		/**
		 *
		 * 触发
		 *
		 */
		void Trigger();

		/**
		 *
		 * 暂停
		 *
		 * @param tick 时间戳
		 *
		 */
		void Pause(int64_t tick);

		/**
		 *
		 * 恢复
		 *
		 * @param tick 时间戳
		 *
		 */
		void Resume(int64_t tick);

		/**
		 *
		 * 修正过期时间
		 *
		 * @param tick 时间戳
		 *
		 */
		void RevisedExpire(int64_t tick);

		/**
		 *
		 * 是否有效
		 *
		 * @return 是否有效
		 *
		 */
		bool IsValid() const;

		/**
		 *
		 * 是否暂停
		 *
		 * @return 是否暂停
		 *
		 */
		bool IsPause() const;

		/**
		 *
		 * 过期时间
		 *
		 * @return 过期时间
		 *
		 */
		int64_t Expire() const;

		/**
		 *
		 * 任务
		 *
		 * @return 任务
		 *
		 */
		std::shared_ptr<ITask> Task();

	private:
		bool _isValid{ true };
		bool _isPause{ false };

		int64_t _count{ 0 };
		int64_t _expire{ 0 };
		int64_t _interval{ 0 };
		int64_t _pauseTick{ 0 };

		std::shared_ptr<ITask> _task{ };
	};
}


#endif // __TIMER__EVENT__H__
