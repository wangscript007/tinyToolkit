/**
 *
 *  作者: hm
 *
 *  说明: tcp会话
 *
 */


#include "eventLoop.h"
#include "operation.h"
#include "tcpSession.h"


namespace net
{
	/**
	 *
	 * 构造函数
	 *
	 * @param eventLoop 事件循环器
	 * @param handle 句柄
	 * @param peerEndpoint 远端端点
	 * @param localEndpoint 本地端点
	 *
	 */
	TCPSession::TCPSession(EventLoop * eventLoop, SOCKET_HANDLE_TYPE handle, const Endpoint & peerEndpoint, const Endpoint & localEndpoint) : _socket(handle),
	                                                                                                                                          _peerEndpoint(peerEndpoint),
	                                                                                                                                          _localEndpoint(localEndpoint),
	                                                                                                                                          _eventLoop(eventLoop)
	{
		_isConnect = _socket.IsValid();

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		_sendChannel = std::make_shared<Channel>(eventLoop, handle, NET_OPTION_TYPE::SEND);
		_recvChannel = std::make_shared<Channel>(eventLoop, handle, NET_OPTION_TYPE::RECEIVE);

		_sendChannel->SetReadCallback( [this](){ DoRead();  });
		_sendChannel->SetWriteCallback([this](){ DoWrite(); });
		_sendChannel->SetErrorCallback([this](){ DoError(); });
		_sendChannel->SetCloseCallback([this](){ DoClose(); });

		_recvChannel->SetReadCallback( [this](){ DoRead();  });
		_recvChannel->SetWriteCallback([this](){ DoWrite(); });
		_recvChannel->SetErrorCallback([this](){ DoError(); });
		_recvChannel->SetCloseCallback([this](){ DoClose(); });

		_sendChannel->SetListenWritingStatus(true);
		_recvChannel->SetListenReadingStatus(true);

	#else

		_ioChannel = std::make_shared<Channel>(eventLoop, handle, NET_OPTION_TYPE::IO);

		_ioChannel->SetReadCallback( [this](){ DoRead();  });
		_ioChannel->SetWriteCallback([this](){ DoWrite(); });
		_ioChannel->SetErrorCallback([this](){ DoError(); });
		_ioChannel->SetCloseCallback([this](){ DoClose(); });

	#endif
	}

	/**
	 *
	 * 析构函数
	 *
	 */
	TCPSession::~TCPSession()
	{
		Shutdown();

	#if PLATFORM_TYPE != PLATFORM_WINDOWS

		if (_ioChannel)
		{
			_ioChannel->Remove();
		}

	#endif

		_socket.Close();
	}

	/**
	 *
	 * 发送
	 *
	 * @param buffer 内容
	 * @param length 长度
	 *
	 */
	void TCPSession::Send(const void * content, std::size_t length)
	{
		if (!_isConnect)
		{
			return;
		}

		_eventLoop->DoFunction
		(
			std::bind
			(
				[this](std::shared_ptr<Buffer> message)
				{
					_messageQueue.push_back(std::move(message));

				#if PLATFORM_TYPE == PLATFORM_WINDOWS

					if (!_isSend)
					{
						_isSend = true;

						auto & message = _messageQueue.front();

						if (_socket.Send(const_cast<char *>(message->Peek()), message->ReadableBytes(), _sendChannel->OwnerContext()) == SOCKET_ERROR)
						{
							DoError();
						}
					}

				#endif
				},
				std::make_shared<Buffer>(content, length)
			)
		);

	#if PLATFORM_TYPE != PLATFORM_WINDOWS

		if (!_ioChannel->IsListenWriting())
		{
			_ioChannel->SetListenWritingStatus(true);
		}

	#endif
	}

	/**
	 *
	 * 开始
	 *
	 */
	void TCPSession::Start()
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		_buffer.ExpansionWriteSpace(static_cast<std::size_t>(Operation::ReadableSize(_recvChannel->Handle())));

		if (_socket.Receive(_buffer.Entry(), _buffer.WritableBytes(), _recvChannel->OwnerContext()) == SOCKET_ERROR)
		{
			DoError();
		}

	#else

		_ioChannel->SetListenReadingStatus(true);

	#endif
	}

	/**
	 *
	 * 关闭
	 *
	 */
	void TCPSession::Shutdown()
	{
		_isConnect = false;
	}

	/**
	 *
	 * 设置发送数据事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPSession::SetSendCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_sendCallback = std::move(function);
	}

	/**
	 *
	 * 设置错误信息事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPSession::SetErrorCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_errorCallback = std::move(function);
	}

	/**
	 *
	 * 设置连接关闭事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPSession::SetCloseCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_closeCallback = std::move(function);
	}

	/**
	 *
	 * 设置接收数据事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPSession::SetReceiveCallback(std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> function)
	{
		_receiveCallback = std::move(function);
	}

	/**
	 *
	 * 是否连接
	 *
	 * @return 是否连接
	 *
	 */
	bool TCPSession::IsConnect() const
	{
		return _isConnect;
	}

	/**
	 *
	 * 总共发送字节数
	 *
	 * @return 总共发送字节数
	 *
	 */
	uint64_t TCPSession::TotalSendBytes() const
	{
		return _totalSendBytes;
	}

	/**
	 *
	 * 本次发送字节数
	 *
	 * @return 本次发送字节数
	 *
	 */
	uint64_t TCPSession::CurrentSendBytes() const
	{
		return _currentSendBytes;
	}

	/**
	 *
	 * 总共接收字节数
	 *
	 * @return 总共接收字节数
	 *
	 */
	uint64_t TCPSession::TotalReceiveBytes() const
	{
		return _totalReceiveBytes;
	}

	/**
	 *
	 * 本次接收字节数
	 *
	 * @return 本次接收字节数
	 *
	 */
	uint64_t TCPSession::CurrentReceiveBytes() const
	{
		return _currentReceiveBytes;
	}

	/**
	 *
	 * 对端端点
	 *
	 * @return 对端端点
	 *
	 */
	const Endpoint & TCPSession::PeerEndpoint() const
	{
		return _peerEndpoint;
	}

	/**
	 *
	 * 对端端点
	 *
	 * @return 对端端点
	 *
	 */
	const Endpoint & TCPSession::LocalEndpoint() const
	{
		return _localEndpoint;
	}

	/**
	 *
	 * 执行读事件
	 *
	 */
	void TCPSession::DoRead()
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		auto bytes = _recvChannel->OwnerContext()->bytes;

		if (bytes > 0)
		{
			_totalReceiveBytes += static_cast<uint64_t>(bytes);
			_currentReceiveBytes += static_cast<uint64_t>(bytes);

			_buffer.RetrieveWriteBytes(static_cast<std::size_t>(bytes));

			if (_receiveCallback)
			{
				_receiveCallback(shared_from_this(), &_buffer);

				_currentReceiveBytes = 0;
			}

			if (!_isConnect && _messageQueue.empty())
			{
				_socket.Shutdown();
			}

			_buffer.ExpansionWriteSpace(static_cast<std::size_t>(Operation::ReadableSize(_recvChannel->Handle())));

			if (_socket.Receive(_buffer.Entry(), _buffer.WritableBytes(), _recvChannel->OwnerContext()) == SOCKET_ERROR)
			{
				DoError();
			}
		}
		else if (bytes == 0)
		{
			DoClose();
		}
		else
		{
			DoError();
		}

	#else

		_buffer.ExpansionWriteSpace(static_cast<std::size_t>(Operation::ReadableSize(_ioChannel->Handle())));

		auto bytes = _socket.Receive(_buffer.Entry(), _buffer.WritableBytes(), nullptr);

		if (bytes > 0)
		{
			_totalReceiveBytes += static_cast<uint64_t>(bytes);
			_currentReceiveBytes += static_cast<uint64_t>(bytes);

			_buffer.RetrieveWriteBytes(static_cast<std::size_t>(bytes));

			if (_receiveCallback)
			{
				_receiveCallback(shared_from_this(), &_buffer);

				_currentReceiveBytes = 0;
			}

			if (!_isConnect && _messageQueue.empty())
			{
				_socket.Shutdown();
			}
		}
		else if (errno == EINTR || errno == EAGAIN)
		{
			DoError();
		}
		else
		{
			DoClose();
		}

	#endif
	}

	/**
	 *
	 * 执行写事件
	 *
	 */
	void TCPSession::DoWrite()
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		_isSend = false;

		auto bytes = _sendChannel->OwnerContext()->bytes;

		if (bytes > 0)
		{
			_totalSendBytes += static_cast<uint64_t>(bytes);
			_currentSendBytes += static_cast<uint64_t>(bytes);

			_messageQueue.pop_front();

			if (_messageQueue.empty())
			{
				if (_sendCallback)
				{
					_sendCallback(shared_from_this());

					_currentSendBytes = 0;
				}

				if (!_isConnect)
				{
					_socket.Shutdown();
				}
			}
			else
			{
				_isSend = true;

				auto & message = _messageQueue.front();

				if (_socket.Send(const_cast<char *>(message->Peek()), message->ReadableBytes(), _sendChannel->OwnerContext()) == SOCKET_ERROR)
				{
					DoError();
				}
			}
		}
		else if (bytes == 0)
		{
			DoClose();
		}
		else
		{
			DoError();
		}

	#else

		auto & message = _messageQueue.front();

		for (int32_t i = 0; i < 3; ++i)
		{
			auto bytes = _socket.Send(const_cast<char *>(message->Peek()), message->ReadableBytes(), nullptr);

			if (bytes > 0)
			{
				_totalSendBytes += static_cast<uint64_t>(bytes);
				_currentSendBytes += static_cast<uint64_t>(bytes);

				message->RetrieveReadBytes(static_cast<std::size_t>(bytes));

				if (message->ReadableBytes())
				{
					continue;
				}

				_messageQueue.pop_front();

				if (!_messageQueue.empty())
				{
					message = _messageQueue.front();

					continue;
				}

				_ioChannel->SetListenWritingStatus(false);

				if (_sendCallback)
				{
					_sendCallback(shared_from_this());

					_currentSendBytes = 0;
				}

				if (!_isConnect)
				{
					_socket.Shutdown();
				}

				break;
			}
			else if (errno == EINTR || errno == EAGAIN)
			{
				DoError();

				break;
			}
			else
			{
				DoClose();

				break;
			}
		}

	#endif
	}

	/**
	 *
	 * 执行错误事件
	 *
	 */
	void TCPSession::DoError()
	{
		if (_errorCallback)
		{
			_errorCallback(shared_from_this());
		}
	}

	/**
	 *
	 * 执行关闭事件
	 *
	 */
	void TCPSession::DoClose()
	{
		_isConnect = false;

	#if PLATFORM_TYPE != PLATFORM_WINDOWS

		_ioChannel->Remove();

	#endif

		_socket.Close();

		if (_closeCallback)
		{
			_closeCallback(shared_from_this());
		}
	}
}
