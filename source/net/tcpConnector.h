#ifndef __NET__TCP_CONNECTOR__H__
#define __NET__TCP_CONNECTOR__H__


/**
 *
 *  作者: hm
 *
 *  说明: tcp连接器
 *
 */


#include "endpoint.h"

#include <memory>


namespace net
{
	class API_TYPE TCPConnector
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param eventLoop 事件循环器
		 *
		 */
		explicit TCPConnector(EventLoop * eventLoop);

		/**
		 *
		 * 析构函数
		 *
		 */
		~TCPConnector();

		/**
		 *
		 * 关闭
		 *
		 */
		void Close();

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
		 * 设置连接端点事件回调函数
		 *
		 * @param function 函数
		 *
		 */
		void SetConnectCallback(std::function<void()> function);

		/**
		 *
		 * 是否连接成功
		 *
		 * @return 是否连接成功
		 *
		 */
		bool IsConnect() const;

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
		 * 执行连接事件
		 *
		 */
		void DoConnect();

	private:
		bool _isWork{ false };
		bool _isConnect{ false };

		Endpoint _peerEndpoint{ };
		Endpoint _localEndpoint{ };

		EventLoop * _eventLoop{ nullptr };

		std::function<void()> _connectCallback;

		std::shared_ptr<Channel> _channel{ };
		std::shared_ptr<TCPSocket> _socket{ };
	};
}


#endif // __NET__TCP_CONNECTOR__H__
