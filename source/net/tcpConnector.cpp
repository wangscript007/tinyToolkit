/**
 *
 *  作者: hm
 *
 *  说明: tcp连接器
 *
 */


#include "socket.h"
#include "channel.h"
#include "tcpConnector.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <MSWSock.h>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <cerrno>
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
		TCPConnector::TCPConnector(EventLoop * eventLoop) : _eventLoop(eventLoop)
		{

		}

		/**
		 *
		 * 析构函数
		 *
		 */
		TCPConnector::~TCPConnector()
		{
			Close();
		}

		/**
		 *
		 * 关闭
		 *
		 */
		void TCPConnector::Close()
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
		}

		/**
		 *
		 * 连接
		 *
		 * @param peerEndpoint 对端端点
		 *
		 */
		void TCPConnector::Connect(const Endpoint & peerEndpoint)
		{
			Endpoint localEndpoint(0);

			Connect(localEndpoint, peerEndpoint);
		}

		/**
		 *
		 * 连接
		 *
		 * @param localEndpoint 本地端点
		 * @param peerEndpoint 对端端点
		 *
		 */
		void TCPConnector::Connect(const Endpoint & localEndpoint, const Endpoint & peerEndpoint)
		{
			if (_isWork)
			{
				return;
			}

			_isWork = true;

			_peerEndpoint  = peerEndpoint;
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

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			_channel = std::make_shared<Channel>(_eventLoop, _socket->Handle(), NET_OPTION_TYPE::SEND);

			_channel->SetErrorCallback([this]() { DoError();   });
			_channel->SetWriteCallback([this]() { DoConnect(); });

			_channel->SetListenWritingStatus(true);

			auto ret = _socket->Connect(peerEndpoint, _channel->OwnerContext());

			if (ret < 0)
			{
				DoError();
			}

		#else

			auto ret = _socket->Connect(peerEndpoint, nullptr);

			if (ret == 0)
			{
				DoConnect();
			}
			else if (errno == EINTR || errno == EISCONN || errno == EINPROGRESS)
			{
				_channel = std::make_shared<Channel>(_eventLoop, _socket->Handle(), NET_OPTION_TYPE::IO);

				_channel->SetErrorCallback([this]() { DoError();   });
				_channel->SetWriteCallback([this]() { DoConnect(); });

				_channel->SetListenWritingStatus(true);
			}
			else
			{
				DoError();
			}

		#endif
		}

		/**
		 *
		 * 设置连接端点事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void TCPConnector::SetConnectCallback(std::function<void()> function)
		{
			_connectCallback = std::move(function);
		}

		/**
		 *
		 * 是否连接成功
		 *
		 * @return 是否连接成功
		 *
		 */
		bool TCPConnector::IsConnect() const
		{
			return _isConnect;
		}

		/**
		 *
		 * 对端端点
		 *
		 * @return 对端端点
		 *
		 */
		const Endpoint & TCPConnector::PeerEndpoint() const
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
		const Endpoint & TCPConnector::LocalEndpoint() const
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
		SOCKET_HANDLE_TYPE TCPConnector::Handle() const
		{
			return _socket ? _socket->Handle() : SOCKET_HANDLE_INVALID;
		}

		/**
		 *
		 * 执行错误事件
		 *
		 */
		void TCPConnector::DoError()
		{
			_isConnect = false;

			if (_channel)
			{
				_channel->Remove();
			}

			if (_connectCallback)
			{
				_connectCallback();
			}
		}

		/**
		 *
		 * 执行连接事件
		 *
		 */
		void TCPConnector::DoConnect()
		{
			_isConnect = true;

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			::setsockopt(_socket->Handle(), SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, nullptr, 0);

			_isConnect = _channel->OwnerContext()->status;

		#endif

			if (_channel)
			{
				_channel->Remove();
			}

			if (_connectCallback)
			{
				_connectCallback();
			}
		}
	}
}
