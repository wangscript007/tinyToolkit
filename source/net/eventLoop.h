#ifndef __NET__EVENT_LOOP__H__
#define __NET__EVENT_LOOP__H__


/**
 *
 *  作者: hm
 *
 *  说明: 事件循环器
 *
 */


#include "eventPoll.h"

#include <mutex>
#include <vector>
#include <memory>


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE EventLoop
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 */
			EventLoop();

			/**
			 *
			 * 开始循环
			 *
			 */
			void Loop();

			/**
			 *
			 * 退出循环
			 *
			 */
			void Quit();

			/**
			 *
			 * 唤醒
			 *
			 */
			void Wakeup();

			/**
			 *
			 * 执行函数
			 *
			 * @param function 函数
			 *
			 */
			void DoFunction(std::function<void()> function);

			/**
			 *
			 * 插入函数
			 *
			 * @param function 函数
			 *
			 */
			void PushFunction(std::function<void()> function);

			/**
			 *
			 * 执行函数列表
			 *
			 */
			void DoFunctionList();

			/**
			 *
			 * 是否在事件循环线程
			 *
			 * @return 是否在事件循环线程
			 *
			 */
			bool IsInLoopThread() const;

			/**
			 *
			 * 添加管道
			 *
			 * @param channel 管道
			 *
			 * @return 是否添加成功
			 *
			 */
			bool AppendChannel(Channel * channel);

			/**
			 *
			 * 更新管道
			 *
			 * @param channel 管道
			 *
			 * @return 是否更新成功
			 *
			 */
			bool UpdateChannel(Channel * channel);

			/**
			 *
			 * 移除管道
			 *
			 * @param channel 管道
			 *
			 * @return 是否移除成功
			 *
			 */
			bool RemoveChannel(Channel * channel);

		private:
			bool _isLoop{ false };
			bool _isHandleFunction{ false };

			uint64_t _threadID{ 0 };

			EventPoll _eventPoll{ };

			std::mutex _mutex{ };

			std::vector<std::function<void()>> _functionList{ };

			std::shared_ptr<Channel> _wakeupChannel{ };
		};
	}
}


#endif // __NET__EVENT_LOOP__H__
