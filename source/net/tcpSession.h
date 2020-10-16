#ifndef __NET__TCP_SESSION__H__
#define __NET__TCP_SESSION__H__


/**
 *
 *  作者: hm
 *
 *  说明: tcp会话
 *
 */


#include "buffer.h"
#include "socket.h"
#include "channel.h"
#include "endpoint.h"

#include <list>
#include <memory>


namespace net
{
	class API_TYPE TCPSession : public std::enable_shared_from_this<TCPSession>
	{
	public:
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
		explicit TCPSession(EventLoop * eventLoop, SOCKET_HANDLE_TYPE handle, const Endpoint & peerEndpoint, const Endpoint & localEndpoint);

		/**
		 *
		 * 析构函数
		 *
		 */
		~TCPSession();

		/**
		 *
		 * 发送
		 *
		 * @param buffer 内容
		 * @param length 长度
		 *
		 */
		void Send(const void * content, std::size_t length);

		/**
		 *
		 * 开始
		 *
		 */
		void Start();

		/**
		 *
		 * 关闭
		 *
		 */
		void Shutdown();

		/**
		 *
		 * 设置发送数据事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void SetSendCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function);

		/**
		 *
		 * 设置错误信息事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void SetErrorCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function);

		/**
		 *
		 * 设置连接关闭事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void SetCloseCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function);

		/**
		 *
		 * 设置接收数据事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void SetReceiveCallback(std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> function);

		/**
		 *
		 * 是否连接
		 *
		 * @return 是否连接
		 *
		 */
		bool IsConnect() const;

		/**
		 *
		 * 总共发送字节数
		 *
		 * @return 总共发送字节数
		 *
		 */
		uint64_t TotalSendBytes() const;

		/**
		 *
		 * 本次发送字节数
		 *
		 * @return 本次发送字节数
		 *
		 */
		uint64_t CurrentSendBytes() const;

		/**
		 *
		 * 总共接收字节数
		 *
		 * @return 总共接收字节数
		 *
		 */
		uint64_t TotalReceiveBytes() const;

		/**
		 *
		 * 本次接收字节数
		 *
		 * @return 本次接收字节数
		 *
		 */
		uint64_t CurrentReceiveBytes() const;

		/**
		 *
		 * 对端端点
		 *
		 * @return 对端端点
		 *
		 */
		const Endpoint & PeerEndpoint() const;

		/**
		 *
		 * 对端端点
		 *
		 * @return 对端端点
		 *
		 */
		const Endpoint & LocalEndpoint() const;

	private:
		/**
		 *
		 * 执行读事件
		 *
		 */
		void DoRead();

		/**
		 *
		 * 执行写事件
		 *
		 */
		void DoWrite();

		/**
		 *
		 * 执行错误事件
		 *
		 */
		void DoError();

		/**
		 *
		 * 执行关闭事件
		 *
		 */
		void DoClose();

	private:
		bool _isConnect{ true };

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		bool _isSend{ false };

		std::shared_ptr<Channel> _sendChannel{ };
		std::shared_ptr<Channel> _recvChannel{ };

	#else

		std::shared_ptr<Channel> _ioChannel{ };

	#endif

		Buffer _buffer{ };

		uint64_t _totalSendBytes{ 0 };
		uint64_t _currentSendBytes{ 0 };
		uint64_t _totalReceiveBytes{ 0 };
		uint64_t _currentReceiveBytes{ 0 };

		TCPSocket _socket;

		Endpoint _peerEndpoint{ };
		Endpoint _localEndpoint{ };

		EventLoop * _eventLoop{ nullptr };

		std::list<std::shared_ptr<Buffer>> _messageQueue{ };

		std::function<void(const std::shared_ptr<net::TCPSession> &)> _sendCallback{ };
		std::function<void(const std::shared_ptr<net::TCPSession> &)> _errorCallback{ };
		std::function<void(const std::shared_ptr<net::TCPSession> &)> _closeCallback{ };
		std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> _receiveCallback{ };

	};
}


#endif // __NET__TCP_SESSION__H__
