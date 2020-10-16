/**
 *
 *  作者: hm
 *
 *  说明: tcp客户端
 *
 */


#include "tcpClient.h"
#include "operation.h"
#include "tcpConnector.h"


namespace net
{
	/**
	 *
	 * 构造函数
	 *
	 * @param eventLoop 事件循环器
	 *
	 */
	TCPClient::TCPClient(EventLoop * eventLoop) : _eventLoop(eventLoop),
	                                              _connector(std::make_shared<TCPConnector>(eventLoop))
	{
		_connector->SetConnectCallback([this](){ DoConnect(); });
	}

	/**
	 *
	 * 析构函数
	 *
	 */
	TCPClient::~TCPClient()
	{
		Disconnect();
	}

	/**
	 *
	 * 连接
	 *
	 * @param peerEndpoint 对端端点
	 *
	 */
	void TCPClient::Connect(const Endpoint & peerEndpoint)
	{
		_connector->Connect(peerEndpoint);
	}

	/**
	 *
	 * 连接
	 *
	 * @param localEndpoint 本地端点
	 * @param peerEndpoint 对端端点
	 *
	 */
	void TCPClient::Connect(const Endpoint & localEndpoint, const Endpoint & peerEndpoint)
	{
		_connector->Connect(localEndpoint, peerEndpoint);
	}

	/**
	 *
	 * 断开连接
	 *
	 */
	void TCPClient::Disconnect()
	{
		if (_connector)
		{
			_connector->Close();
		}

		if (_session)
		{
			_session->Shutdown();
		}
	}

	/**
	 *
	 * 设置发送数据事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPClient::SetSendCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
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
	void TCPClient::SetErrorCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
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
	void TCPClient::SetCloseCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_closeCallback = std::move(function);
	}

	/**
	 *
	 * 设置连接结果事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPClient::SetConnectCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_connectCallback = std::move(function);
	}

	/**
	 *
	 * 设置接收数据事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPClient::SetReceiveCallback(std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> function)
	{
		_receiveCallback = std::move(function);
	}

	/**
	 *
	 * 执行连接事件
	 *
	 */
	void TCPClient::DoConnect()
	{
		Endpoint peerEndpoint{ };
		Endpoint localEndpoint{ };

		if (_connector->PeerEndpoint().HostEndianPort() == 0)
		{
			Operation::GetPeerAddress(_connector->Handle(), peerEndpoint.SocketAddress());
		}
		else
		{
			peerEndpoint = _connector->PeerEndpoint();
		}

		if (_connector->LocalEndpoint().HostEndianPort() == 0)
		{
			Operation::GetLocalAddress(_connector->Handle(), localEndpoint.SocketAddress());
		}
		else
		{
			localEndpoint = _connector->LocalEndpoint();
		}

		_session = std::make_shared<TCPSession>(_eventLoop, _connector->IsConnect() ? _connector->Handle() : SOCKET_HANDLE_INVALID, peerEndpoint, localEndpoint);

		if (_connector->IsConnect())
		{
			_session->Start();

			_session->SetSendCallback(_sendCallback);
			_session->SetErrorCallback(_errorCallback);
			_session->SetCloseCallback(_closeCallback);
			_session->SetReceiveCallback(_receiveCallback);
		}
		else
		{
			_connector->Close();
		}

		if (_connectCallback)
		{
			_connectCallback(_session);
		}

		if (!_connector->IsConnect())
		{
			_session.reset();
		}
	}
}
