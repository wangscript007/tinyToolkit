#ifndef __NET__TCP_CLIENT__H__
#define __NET__TCP_CLIENT__H__


/**
 *
 *  作者: hm
 *
 *  说明: tcp客户端
 *
 */


#include "tcpSession.h"


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE TCPConnector;

		class API_TYPE TCPClient
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param eventLoop 事件循环器
			 *
			 */
			explicit TCPClient(EventLoop * eventLoop);

			/**
			 *
			 * 析构函数
			 *
			 */
			~TCPClient();

			/**
			 *
			 * 连接
			 *
			 * @param peerEndpoint 对端端点
			 *
			 */
			void Connect(const Endpoint & peerEndpoint);

			/**
			 *
			 * 连接
			 *
			 * @param localEndpoint 本地端点
			 * @param peerEndpoint 对端端点
			 *
			 */
			void Connect(const Endpoint & localEndpoint, const Endpoint & peerEndpoint);

			/**
			 *
			 * 断开连接
			 *
			 */
			void Disconnect();

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
			 * 设置连接结果事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetConnectCallback(std::function<void(const std::shared_ptr<net::TCPSession> &)> function);

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
			 * 执行连接事件
			 *
			 */
			void DoConnect();

		private:
			EventLoop * _eventLoop{ nullptr };

			std::shared_ptr<TCPSession> _session{ };
			std::shared_ptr<TCPConnector> _connector{ };

			std::function<void(const std::shared_ptr<net::TCPSession> &)> _sendCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &)> _errorCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &)> _closeCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &)> _connectCallback{ };
			std::function<void(const std::shared_ptr<net::TCPSession> &, net::Buffer *)> _receiveCallback{ };
		};
	}
}


#endif // __NET__TCP_CLIENT__H__
