#ifndef __NET__TCP_SERVER__H__
#define __NET__TCP_SERVER__H__


/**
 *
 *  作者: hm
 *
 *  说明: tcp服务端
 *
 */


#include "tcpSession.h"

#include <unordered_set>


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE TCPAcceptor;

		class API_TYPE TCPServer
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param eventLoop 事件循环器
			 *
			 */
			explicit TCPServer(EventLoop * eventLoop);

			/**
			 *
			 * 析构函数
			 *
			 */
			~TCPServer();

			/**
			 *
			 * 关闭
			 *
			 */
			void Close();

			/**
			 *
			 * 监听
			 *
			 * @param localEndpoint 本地端点
			 *
			 */
			void Listen(const Endpoint & localEndpoint);

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
			 * 设置接收结果事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetAcceptCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function);

			/**
			 *
			 * 设置接收数据事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetReceiveCallback(std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> function);

		private:
			/**
			 *
			 * 执行关闭事件
			 *
			 * @param session 会话
			 *
			 */
			void DoClose(const std::shared_ptr<net::TCPSession> & session);

			/**
			 *
			 * 执行接收事件
			 *
			 */
			void DoAccept();

		private:
			EventLoop * _eventLoop{ nullptr };

			std::shared_ptr<TCPAcceptor> _acceptor{ };

			std::unordered_set<std::shared_ptr<TCPSession>> _sessions{ };

			std::function<void(const std::shared_ptr<net::TCPSession> &)> _sendCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &)> _errorCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &)> _closeCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &)> _acceptCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> _receiveCallback{ };
		};
	}
}


#endif // __NET__TCP_SERVER__H__
