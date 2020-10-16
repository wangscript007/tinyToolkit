/**
 *
 *  作者: hm
 *
 *  说明: 通道
 *
 */


#include "channel.h"
#include "eventLoop.h"

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
	 * @param eventLoop 事件循环器
	 * @param handle 句柄
	 * @param option 操作
	 *
	 */
	Channel::Channel(EventLoop * eventLoop, SOCKET_HANDLE_TYPE handle, NET_OPTION_TYPE option) : _context(option),
	                                                                                             _eventLoop(eventLoop),
	                                                                                             _handle(handle)
	{
		_context.handle = handle;
		_context.channel = this;
	}

	/**
	 *
	 * 设置读事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void Channel::SetReadCallback(std::function<void()> function)
	{
		_readCallback = std::move(function);
	}

	/**
	 *
	 * 设置错误事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void Channel::SetErrorCallback(std::function<void()> function)
	{
		_errorCallback = std::move(function);
	}

	/**
	 *
	 * 设置写事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void Channel::SetWriteCallback(std::function<void()> function)
	{
		_writeCallback = std::move(function);
	}

	/**
	 *
	 * 设置关闭事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void Channel::SetCloseCallback(std::function<void()> function)
	{
		_closeCallback = std::move(function);
	}

	/**
	 *
	 * 移除
	 *
	 * @return 是否移除成功
	 *
	 */
	bool Channel::Remove()
	{
		return _eventLoop->RemoveChannel(this);
	}

	/**
	 *
	 * 是否正在监听读操作
	 *
	 * @return 是否正在监听读操作
	 *
	 */
	bool Channel::IsListenReading() const
	{
		return _isListenReading;
	}

	/**
	 *
	 * 是否正在监听写操作
	 *
	 * @return 是否正在监听写操作
	 *
	 */
	bool Channel::IsListenWriting() const
	{
		return _isListenWriting;
	}

	/**
	 *
	 * 设置监听读操作状态
	 *
	 * @param on 状态
	 *
	 * @return 是否设置成功
	 *
	 */
	bool Channel::SetListenReadingStatus(bool on)
	{
		if (on)
		{
			if (_isListenWriting)
			{
				if (!_isListenReading)
				{
					_isListenReading = on;

					return _eventLoop->UpdateChannel(this);
				}
			}
			else
			{
				if (!_isListenReading)
				{
					_isListenReading = on;

					return _eventLoop->AppendChannel(this);
				}
			}
		}
		else
		{
			if (_isListenWriting)
			{
				if (_isListenReading)
				{
					_isListenReading = on;

					return _eventLoop->UpdateChannel(this);
				}
			}
			else
			{
				if (_isListenReading)
				{
					_isListenReading = on;

					return _eventLoop->RemoveChannel(this);
				}
			}
		}

		_isListenReading = on;

		return true;
	}

	/**
	 *
	 * 设置监听写操作状态
	 *
	 * @param on 状态
	 *
	 * @return 是否设置成功
	 *
	 */
	bool Channel::SetListenWritingStatus(bool on)
	{
		if (on)
		{
			if (_isListenReading)
			{
				if (!_isListenWriting)
				{
					_isListenWriting = on;

					return _eventLoop->UpdateChannel(this);
				}
			}
			else
			{
				if (!_isListenWriting)
				{
					_isListenWriting = on;

					return _eventLoop->AppendChannel(this);
				}
			}
		}
		else
		{
			if (_isListenReading)
			{
				if (_isListenWriting)
				{
					_isListenWriting = on;

					return _eventLoop->UpdateChannel(this);
				}
			}
			else
			{
				if (_isListenWriting)
				{
					_isListenWriting = on;

					return _eventLoop->RemoveChannel(this);
				}
			}
		}

		_isListenWriting = on;

		return true;
	}

	/**
	 *
	 * 上下文
	 *
	 * @return 上下文
	 *
	 */
	Context * Channel::OwnerContext()
	{
		return &_context;
	}

	/**
	 *
	 * 句柄
	 *
	 * @return 句柄
	 *
	 */
	SOCKET_HANDLE_TYPE Channel::Handle() const
	{
		return _handle;
	}

	/**
	 *
	 * 执行事件
	 *
	 * @param netContext 网络上下文
	 * @param sysContext 系统上下文
	 *
	 */
	void Channel::DoEvent(Context * netContext, void * sysContext)
	{
		switch (netContext->optionType)
		{
			case NET_OPTION_TYPE::IO:
			{
				DoIO(netContext, sysContext);

				break;
			}

			case NET_OPTION_TYPE::SEND:
			{
				DoSend(netContext, sysContext);

				break;
			}

			case NET_OPTION_TYPE::RECEIVE:
			{
				DoReceive(netContext, sysContext);

				break;
			}

			default:
			{
				throw std::logic_error("Channel option error");
			}
		}
	}

	/**
	 *
	 * 交互处理
	 *
	 * @param netContext 网络上下文
	 * @param sysContext 系统上下文
	 *
	 */
	void Channel::DoIO(Context * netContext, void * sysContext)
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		(void)netContext;
		(void)sysContext;

	#elif PLATFORM_TYPE == PLATFORM_APPLE

		auto pollContext = reinterpret_cast<const struct kevent *>(sysContext);

		if (pollContext->flags & EV_ERROR)
		{
			if (_errorCallback)
			{
				_errorCallback();
			}

			if (_closeCallback)
			{
				_closeCallback();
			}

			return;
		}

		if (pollContext->filter & EVFILT_READ)
		{
			DoReceive(netContext, sysContext);
		}

		if (pollContext->filter & EVFILT_WRITE)
		{
			DoSend(netContext, sysContext);
		}

	#else

		auto pollContext = reinterpret_cast<const struct epoll_event *>(sysContext);

		if (pollContext->events & EPOLLERR)
		{
			if (_errorCallback)
			{
				_errorCallback();
			}
		}

		if (pollContext->events & (EPOLLHUP | EPOLLRDHUP))
		{
			if (_closeCallback)
			{
				_closeCallback();
			}

			return;
		}

		if (pollContext->events & EPOLLIN)
		{
			DoReceive(netContext, sysContext);
		}

		if (pollContext->events & EPOLLOUT)
		{
			DoSend(netContext, sysContext);
		}

	#endif
	}

	/**
	 *
	 * 发送处理
	 *
	 * @param netContext 网络上下文
	 * @param sysContext 系统上下文
	 *
	 */
	void Channel::DoSend(Context * netContext, void * sysContext)
	{
		(void)netContext;
		(void)sysContext;

		if (_writeCallback)
		{
			_writeCallback();
		}
	}

	/**
	 *
	 * 接收处理
	 *
	 * @param netContext 网络上下文
	 * @param sysContext 系统上下文
	 *
	 */
	void Channel::DoReceive(Context * netContext, void * sysContext)
	{
		(void)netContext;
		(void)sysContext;

		if (_readCallback)
		{
			_readCallback();
		}
	}
}
