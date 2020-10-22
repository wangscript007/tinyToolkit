/**
 *
 *  作者: hm
 *
 *  说明: tcp接收器
 *
 */


#include "socket.h"
#include "channel.h"
#include "operation.h"
#include "tcpAcceptor.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <MSWSock.h>
#
#else
#
#  if PLATFORM_TYPE == PLATFORM_APPLE
#
#    include <cerrno>
#
#  endif
#
#  include <fcntl.h>
#  include <zconf.h>
#
#endif


namespace tinyToolkit
{
	namespace net
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param eventLoop 事件循环器
		 *
		 */
		TCPAcceptor::TCPAcceptor(EventLoop * eventLoop) : _eventLoop(eventLoop)
		{
		#if PLATFORM_TYPE == PLATFORM_MIPS || PLATFORM_TYPE == PLATFORM_APPLE || PLATFORM_TYPE == PLATFORM_LINUX

			_idleHandle = ::open("/dev/null", O_RDONLY | O_CLOEXEC);

		#endif
		}

		/**
		 *
		 * 析构函数
		 *
		 */
		TCPAcceptor::~TCPAcceptor()
		{
			Close();
		}

		/**
		 *
		 * 关闭
		 *
		 */
		void TCPAcceptor::Close()
		{
			_isWork = false;

			if (_channel)
			{
				_channel->Remove();
			}

			if (_socket)
			{
				_socket->Close();
			}

		#if PLATFORM_TYPE == PLATFORM_MIPS || PLATFORM_TYPE == PLATFORM_APPLE || PLATFORM_TYPE == PLATFORM_LINUX

			if (_idleHandle >= 0)
			{
				::close(_idleHandle);
			}

		#endif
		}

		/**
		 *
		 * 监听
		 *
		 * @param localEndpoint 本地端点
		 *
		 */
		void TCPAcceptor::Listen(const Endpoint & localEndpoint)
		{
			if (_isWork)
			{
				return;
			}

			_isWork = true;

			_localEndpoint = localEndpoint;

			_socket = std::make_shared<TCPSocket>(localEndpoint.Family());

			if (!_socket->IsValid())
			{
				return;
			}

			_socket->SetBlockStatus(false);
			_socket->SetDelayStatus(false);
			_socket->SetSignalStatus(false);
			_socket->SetReusePortStatus(true);
			_socket->SetReuseAddressStatus(true);

			if (_socket->Bind(localEndpoint) == SOCKET_ERROR)
			{
				DoError();

				return;
			}

			if (_socket->Listen() == SOCKET_ERROR)
			{
				DoError();

				return;
			}

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			_channel = std::make_shared<Channel>(_eventLoop, _socket->Handle(), NET_OPTION_TYPE::RECEIVE);

		#else

			_channel = std::make_shared<Channel>(_eventLoop, _socket->Handle(), NET_OPTION_TYPE::IO);

		#endif

			_channel->SetReadCallback([this]()  { DoAccept(); });
			_channel->SetErrorCallback([this]() { DoError();  });

			_channel->SetListenReadingStatus(true);

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			_channel->OwnerContext()->handle = Operation::TCPSocketHandle(localEndpoint.Family());

			if (_socket->Accept(_channel->OwnerContext()) == SOCKET_ERROR)
			{
				DoError();

				return;
			}

		#endif
		}

		/**
		 *
		 * 设置接收端点事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TCPAcceptor::SetAcceptCallback(std::function<void()> function)
		{
			_acceptCallback = std::move(function);
		}

		/**
		 *
		 * 是否接收成功
		 *
		 * @return 是否接收成功
		 *
		 */
		bool TCPAcceptor::IsAccept() const
		{
			return _isAccept;
		}

		/**
		 *
		 * 对端端点
		 *
		 * @return 对端端点
		 *
		 */
		const Endpoint & TCPAcceptor::PeerEndpoint() const
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
		const Endpoint & TCPAcceptor::LocalEndpoint() const
		{
			return _localEndpoint;
		}

		/**
		 *
		 * 句柄
		 *
		 * @return 句柄
		 *
		 */
		SOCKET_HANDLE_TYPE TCPAcceptor::Handle() const
		{
			return _channel ? _channel->OwnerContext()->handle : SOCKET_HANDLE_INVALID;
		}

		/**
		 *
		 * 执行错误事件
		 *
		 */
		void TCPAcceptor::DoError()
		{
			_isAccept = false;

			if (_acceptCallback)
			{
				_acceptCallback();
			}
		}

		/**
		 *
		 * 执行接收事件
		 *
		 */
		void TCPAcceptor::DoAccept()
		{
			_isAccept = true;

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			auto handle = _socket->Handle();

			::setsockopt(_channel->OwnerContext()->handle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<const char *>(&handle), sizeof(handle));

			Operation::SetBlockStatus(_channel->OwnerContext()->handle, false);
			Operation::SetDelayStatus(_channel->OwnerContext()->handle, false);
			Operation::SetSignalStatus(_channel->OwnerContext()->handle, false);
			Operation::SetReusePortStatus(_channel->OwnerContext()->handle, true);
			Operation::SetReusePortStatus(_channel->OwnerContext()->handle, true);

		#else

			if (_socket->Accept(_channel->OwnerContext()) == SOCKET_ERROR)
			{
				_isAccept = false;

				if (errno == EMFILE)
				{
					::close(_idleHandle);

					_idleHandle = Operation::Accept(_socket->Handle(), SOCKET_HANDLE_INVALID, nullptr, nullptr);

					Operation::CloseSocketHandle(_idleHandle);

					_idleHandle = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
				}
			}
			else
			{
				Operation::SetBlockStatus(_channel->OwnerContext()->handle, false);
				Operation::SetDelayStatus(_channel->OwnerContext()->handle, false);
				Operation::SetSignalStatus(_channel->OwnerContext()->handle, false);
				Operation::SetReusePortStatus(_channel->OwnerContext()->handle, true);
				Operation::SetReusePortStatus(_channel->OwnerContext()->handle, true);
			}

		#endif

			if (_acceptCallback)
			{
				_acceptCallback();
			}

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			_channel->OwnerContext()->handle = Operation::TCPSocketHandle(localEndpoint.Family());

			if (_socket->Accept(_channel->OwnerContext()) == SOCKET_ERROR)
			{
				DoError();

				return;
			}

		#endif
		}
	}
}
