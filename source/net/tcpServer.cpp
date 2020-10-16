/**
 *
 *  作者: hm
 *
 *  说明: tcp服务端
 *
 */


#include "tcpServer.h"
#include "operation.h"
#include "tcpAcceptor.h"


namespace net
{
	/**
	 *
	 * 构造函数
	 *
	 * @param eventLoop 事件循环器
	 *
	 */
	TCPServer::TCPServer(EventLoop * eventLoop) : _eventLoop(eventLoop),
	                                              _acceptor(std::make_shared<TCPAcceptor>(eventLoop))
	{
		_acceptor->SetAcceptCallback([this](){ DoAccept(); });
	}

	/**
	 *
	 * 析构函数
	 *
	 */
	TCPServer::~TCPServer()
	{
		Close();
	}

	/**
	 *
	 * 关闭
	 *
	 */
	void TCPServer::Close()
	{
		if (_acceptor)
		{
			_acceptor->Close();
		}

		for (auto && session : _sessions)
		{
			session->Shutdown();
		}
	}

	/**
	 *
	 * 监听
	 *
	 * @param localEndpoint 本地端点
	 *
	 */
	void TCPServer::Listen(const Endpoint & localEndpoint)
	{
		_acceptor->Listen(localEndpoint);
	}

	/**
	 *
	 * 设置发送数据事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPServer::SetSendCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
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
	void TCPServer::SetErrorCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
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
	void TCPServer::SetCloseCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_closeCallback = std::move(function);
	}

	/**
	 *
	 * 设置接收结果事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPServer::SetAcceptCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function)
	{
		_acceptCallback = std::move(function);
	}

	/**
	 *
	 * 设置接收数据事件回调函数
	 *
	 * @param function 函数
	 *
	 */
	void TCPServer::SetReceiveCallback(std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> function)
	{
		_receiveCallback = std::move(function);
	}

	/**
	 *
	 * 执行关闭事件
	 *
	 * @param session 会话
	 *
	 */
	void TCPServer::DoClose(const std::shared_ptr<net::TCPSession> & session)
	{
		if (_closeCallback)
		{
			_closeCallback(session);
		}

		_sessions.erase(session);
	}

	/**
	 *
	 * 执行接收事件
	 *
	 */
	void TCPServer::DoAccept()
	{
		Endpoint peerEndpoint{ };
		Endpoint localEndpoint{ };

		if (_acceptor->PeerEndpoint().HostEndianPort() == 0)
		{
			Operation::GetPeerAddress(_acceptor->Handle(), peerEndpoint.SocketAddress());
		}
		else
		{
			peerEndpoint = _acceptor->PeerEndpoint();
		}

		if (_acceptor->LocalEndpoint().HostEndianPort() == 0)
		{
			Operation::GetLocalAddress(_acceptor->Handle(), localEndpoint.SocketAddress());
		}
		else
		{
			localEndpoint = _acceptor->LocalEndpoint();
		}

		auto session = std::make_shared<TCPSession>(_eventLoop, _acceptor->IsAccept() ? _acceptor->Handle() : SOCKET_HANDLE_INVALID, peerEndpoint, localEndpoint);

		if (_acceptor->IsAccept())
		{
			_sessions.insert(session);

			session->Start();

			session->SetSendCallback(_sendCallback);
			session->SetErrorCallback(_errorCallback);
			session->SetCloseCallback([this](const std::shared_ptr<net::TCPSession> & session_){ DoClose(session_); });
			session->SetReceiveCallback(_receiveCallback);
		}

		if (_acceptCallback)
		{
			_acceptCallback(session);
		}

		if (!_acceptor->IsAccept())
		{
			session.reset();
		}
	}
}
