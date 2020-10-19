/**
 *
 *  作者: hm
 *
 *  说明: 事件轮询器
 *
 */


#include "eventPoll.h"
#include "operation.h"

#if PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <sys/event.h>
#
#elif PLATFORM_TYPE != PLATFORM_WINDOWS
#
#  include <sys/epoll.h>
#
#endif


namespace net
{
	/**
	 *
	 * 构造函数
	 *
	 * @param loop 事件循环器
	 *
	 */
	EventPoll::EventPoll() : _handle(Operation::PollHandle())
	{

	}

	/**
	 *
	 * 析构函数
	 *
	 */
	EventPoll::~EventPoll()
	{
		Operation::ClosePollHandle(_handle);
	}

	/**
	 *
	 * 是否有效
	 *
	 * @return 是否有效
	 *
	 */
	bool EventPoll::IsValid() const
	{
		return Operation::IsValidPollHandle(_handle);
	}

	/**
	 *
	 * 执行事件
	 *
	 * @param timeout 超时时间
	 *
	 * @return 是否执行成功
	 *
	 */
	bool EventPoll::DoEvent(int32_t timeout)
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		auto handle = SOCKET_HANDLE_INVALID;

		DWORD bytes = 0;

		Context * context = nullptr;

		if (::GetQueuedCompletionStatus(_handle, &bytes, (PULONG_PTR)&handle, (LPOVERLAPPED *)&context, timeout))
		{
			if (context && context->channel)
			{
				context->bytes = bytes;
				context->status = true;

				context->channel->DoEvent(context, nullptr);
			}
		}
		else
		{
			if (context && context->channel)
			{
				context->bytes = bytes;
				context->status = false;

				context->channel->DoEvent(context, nullptr);
			}
			else
			{
				return ::GetLastError() == WAIT_TIMEOUT;
			}
		}

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		struct kevent events[32]{ };

		struct timespec timestamp{ };

		timestamp.tv_sec = 0;
		timestamp.tv_nsec = timeout * 1000000;

		int32_t count = ::kevent(_handle, nullptr, 0, events, static_cast<int32_t>(sizeof(events) / sizeof(events[0])), &timestamp);

		if (count == -1)
		{
			return errno == EINTR;
		}

		for (int32_t i = 0; i < count; ++i)
		{
			auto context = reinterpret_cast<Context *>(events[i].udata);

			if (context && context->channel)
			{
				context->channel->DoEvent(context, &events[i]);
			}
		}

	#else

		struct epoll_event events[32]{ };

		int32_t count = ::epoll_wait(_handle, events, static_cast<int32_t>(sizeof(events) / sizeof(events[0])), timeout * 1000);

		if (count == -1)
		{
			return errno == EINTR;
		}

		for (int32_t i = 0; i < count; ++i)
		{
			auto context = reinterpret_cast<Context *>(events[i].data.ptr);

			if (context && context->channel)
			{
				context->channel->DoEvent(context, &events[i]);
			}
		}

	#endif

		return true;
	}

	/**
	 *
	 * 添加管道监控
	 *
	 * @param channel 通道
	 *
	 * @return 是否添加成功
	 *
	 */
	bool EventPoll::AppendChannel(Channel * channel) const
	{
		if (!IsValid())
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		return ::CreateIoCompletionPort(reinterpret_cast<HANDLE>(channel->Handle()), _handle, static_cast<ULONG_PTR>(channel->Handle()), 0) == _handle;

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		struct kevent event[2]{ };

		EV_SET(&event[0], channel->Handle(), EVFILT_READ,  EV_ADD | (channel->IsListenReading() ? EV_ENABLE : EV_DISABLE), 0, 0, &channel->_context);
		EV_SET(&event[1], channel->Handle(), EVFILT_WRITE, EV_ADD | (channel->IsListenWriting() ? EV_ENABLE : EV_DISABLE), 0, 0, &channel->_context);

		return ::kevent(_handle, event, 2, nullptr, 0, nullptr) != -1;

	#else

		struct epoll_event event{ };

		event.events = (channel->IsListenReading() ? EPOLLIN : 0) | (channel->IsListenWriting() ? EPOLLOUT : 0);
		event.data.ptr = &channel->_context;

		return ::epoll_ctl(_handle, EPOLL_CTL_ADD, channel->Handle(), &event) != -1;

	#endif
	}

	/**
	 *
	 * 更新管道监控
	 *
	 * @param channel 通道
	 *
	 * @return 是否更新成功
	 *
	 */
	bool EventPoll::UpdateChannel(Channel * channel) const
	{
		if (!IsValid())
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		(void)channel;

		return true;

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		struct kevent event[2]{ };

		EV_SET(&event[0], channel->Handle(), EVFILT_READ,  channel->IsListenReading() ? EV_ENABLE : EV_DISABLE, 0, 0, &channel->_context);
		EV_SET(&event[1], channel->Handle(), EVFILT_WRITE, channel->IsListenWriting() ? EV_ENABLE : EV_DISABLE, 0, 0, &channel->_context);

		return ::kevent(_handle, event, 2, nullptr, 0, nullptr) != -1;

	#else

		struct epoll_event event{ };

		event.events = (channel->IsListenReading() ? EPOLLIN : 0) | (channel->IsListenWriting() ? EPOLLOUT : 0);
		event.data.ptr = &channel->_context;

		return ::epoll_ctl(_handle, EPOLL_CTL_MOD, channel->Handle(), &event) != -1;

	#endif
	}

	/**
	 *
	 * 移除管道监控
	 *
	 * @param channel 通道
	 *
	 * @return 是否移除成功
	 *
	 */
	bool EventPoll::RemoveChannel(Channel * channel) const
	{
		if (!IsValid())
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		(void)channel;

		return true;

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		struct kevent event[2]{ };

		EV_SET(&event[0], channel->Handle(), EVFILT_READ,  EV_DELETE, 0, 0, &channel->_context);
		EV_SET(&event[1], channel->Handle(), EVFILT_WRITE, EV_DELETE, 0, 0, &channel->_context);

		return ::kevent(_handle, event, 2, nullptr, 0, nullptr) != -1;

	#else

		struct epoll_event event{ };

		event.events =  EPOLLIN | EPOLLOUT;
		event.data.ptr = &channel->_context;

		return ::epoll_ctl(_handle, EPOLL_CTL_DEL, channel->Handle(), &event) != -1;

	#endif
	}
}
