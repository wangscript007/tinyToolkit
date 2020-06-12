#ifndef __TIMER__TASK__H__
#define __TIMER__TASK__H__


/**
 *
 *  作者: hm
 *
 *  说明: 任务
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


namespace timer
{
	class API_TYPE ITask
	{
		friend class Event;

	public:
		/**
		 *
		 * 析构函数
		 *
		 */
		virtual ~ITask() = default;

		/**
		 *
		 * 杀死事件
		 *
		 */
		virtual void OnKill();

		/**
		 *
		 * 暂停事件
		 *
		 */
		virtual void OnPause();

		/**
		 *
		 * 恢复事件
		 *
		 */
		virtual void OnResume();

		/**
		 *
		 * 完成事件
		 *
		 */
		virtual void OnFinish();

		/**
		 *
		 * 触发事件
		 *
		 */
		virtual void OnTrigger();

		/**
		 *
		 * 任务次数
		 *
		 * @return 任务次数
		 *
		 */
		int64_t TotalCount();

		/**
		 *
		 * 触发次数
		 *
		 * @return 触发次数
		 *
		 */
		int64_t TriggerCount();

	private:
		int64_t _totalCount{ 0 };
		int64_t _triggerCount{ 0 };
	};
}


#endif // __TIMER__TASK__H__
