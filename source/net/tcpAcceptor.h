#ifndef __NET__TCP_ACCEPTOR__H__
#define __NET__TCP_ACCEPTOR__H__


/**
 *
 *  作者: hm
 *
 *  说明: tcp接收器
 *
 */


#include "endpoint.h"

#include <memory>


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE TCPAcceptor
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param eventLoop 事件循环器
			 *
			 */
			explicit TCPAcceptor(EventLoop * eventLoop);

			/**
			 *
			 * 析构函数
			 *
			 */
			~TCPAcceptor();

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
			 * 设置接收端点事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetAcceptCallback(std::function<void()> function);

			/**
			 *
			 * 是否接收成功
			 *
			 * @return 是否接收成功
			 *
			 */
			bool IsAccept() const;

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

			/**
			 *
			 * 句柄
			 *
			 * @return 句柄
			 *
			 */
			SOCKET_HANDLE_TYPE Handle() const;

		private:
			/**
			 *
			 * 执行错误事件
			 *
			 */
			void DoError();

			/**
			 *
			 * 执行接收事件
			 *
			 */
			void DoAccept();

		private:
			bool _isWork{ false };
			bool _isAccept{ false };

			Endpoint _peerEndpoint{ };
			Endpoint _localEndpoint{ };

			EventLoop * _eventLoop{ nullptr };

		#if PLATFORM_TYPE == PLATFORM_MIPS || PLATFORM_TYPE == PLATFORM_APPLE || PLATFORM_TYPE == PLATFORM_LINUX

			SOCKET_HANDLE_TYPE _idleHandle{ SOCKET_HANDLE_INVALID };

		#endif

			std::function<void()> _acceptCallback;

			std::shared_ptr<Channel> _channel{ };
			std::shared_ptr<TCPSocket> _socket{ };
		};
	}
}


#endif // __NET__TCP_ACCEPTOR__H__
