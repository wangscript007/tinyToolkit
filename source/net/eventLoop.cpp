/**
 *
 *  作者: hm
 *
 *  说明: 事件循环器
 *
 */


#include "eventLoop.h"
#include "operation.h"

#if PLATFORM_TYPE == PLATFORM_APPLE
#
#
#
#elif PLATFORM_TYPE == PLATFORM_WINDOWS
#
#
#
#else
#
#  include <unistd.h>
#
#  include <sys/syscall.h>
#  include <sys/eventfd.h>
#
#endif


namespace net
{
	/**
	 *
	 * 线程序列号
	 *
	 * @return 线程序列号
	 *
	 */
	uint64_t ThreadID()
	{
		static thread_local uint64_t tid = 0;

		if (tid == 0)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			tid = ::GetCurrentThreadId();

		#elif PLATFORM_TYPE == PLATFORM_APPLE

			::pthread_threadid_np(nullptr, &tid);

		#else

			tid = static_cast<uint64_t>(::syscall(SYS_gettid));

		#endif
		}

		return tid;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * 构造函数
	 *
	 */
	EventLoop::EventLoop() : _threadID(ThreadID())
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

	#else

		_wakeupChannel = std::make_shared<Channel>(this, ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC));

		_wakeupChannel->SetReadCallback([this]()
		{
			uint64_t val{ 0 };

			::read(_wakeupChannel->Handle(), &val, sizeof(val));
		});

		_wakeupChannel->SetListenReadingStatus(true);

	#endif
	}

	/**
	 *
	 * 开始循环
	 *
	 */
	void EventLoop::Loop()
	{
		_isLoop = true;

		while (_isLoop)
		{
			_eventPoll.DoEvent(5);

			DoFunctionList();
		}
	}

	/**
	 *
	 * 退出循环
	 *
	 */
	void EventLoop::Quit()
	{
		_isLoop = false;

		if (!IsInLoopThread())
		{
			Wakeup();
		}
	}

	/**
	 *
	 * 唤醒
	 *
	 */
	void EventLoop::Wakeup()
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS



	#else

		uint64_t val{ 666 };

		::write(_wakeupChannel->Handle(), &val, sizeof(val));

	#endif
	}

	/**
	 *
	 * 执行函数
	 *
	 * @param function 函数
	 *
	 */
	void EventLoop::DoFunction(std::function<void()> function)
	{
		if (IsInLoopThread())
		{
			function();
		}
		else
		{
			PushFunction(std::move(function));
		}
	}

	/**
	 *
	 * 插入函数
	 *
	 * @param function 函数
	 *
	 */
	void EventLoop::PushFunction(std::function<void()> function)
	{
		{
			std::lock_guard<std::mutex> lock(_mutex);

			_functionList.push_back(std::move(function));
		}

		if (!IsInLoopThread() || _isHandleFunction)
		{
			Wakeup();
		}
	}

	/**
	 *
	 * 执行函数列表
	 *
	 */
	void EventLoop::DoFunctionList()
	{
		_isHandleFunction = true;

		std::vector<std::function<void()>> functionList{ };

		{
			std::lock_guard<std::mutex> lock(_mutex);

			functionList.swap(_functionList);
		}

		for (auto && function : functionList)
		{
			function();
		}

		_isHandleFunction = false;
	}

	/**
	 *
	 * 是否在事件循环线程
	 *
	 * @return 是否在事件循环线程
	 *
	 */
	bool EventLoop::IsInLoopThread() const
	{
		return _threadID == ThreadID();
	}

	/**
	 *
	 * 添加管道
	 *
	 * @param channel 管道
	 *
	 * @return 是否添加成功
	 *
	 */
	bool EventLoop::AppendChannel(Channel * channel)
	{
		return _eventPoll.AppendChannel(channel);
	}

	/**
	 *
	 * 更新管道
	 *
	 * @param channel 管道
	 *
	 * @return 是否更新成功
	 *
	 */
	bool EventLoop::UpdateChannel(Channel * channel)
	{
		return _eventPoll.UpdateChannel(channel);
	}

	/**
	 *
	 * 移除管道
	 *
	 * @param channel 管道
	 *
	 * @return 是否移除成功
	 *
	 */
	bool EventLoop::RemoveChannel(Channel * channel)
	{
		return _eventPoll.RemoveChannel(channel);
	}
}
