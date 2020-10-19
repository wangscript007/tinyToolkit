#ifndef __NET__SOCKET__H__
#define __NET__SOCKET__H__


/**
 *
 *  作者: hm
 *
 *  说明: 套接字
 *
 */


#include "context.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <winsock2.h>
#
#else
#
#  include <netinet/in.h>
#
#endif

#include <cstring>
#include <cstdint>


namespace net
{
	class API_TYPE Endpoint;

	class API_TYPE ISocket
	{
	public:
		/**
		 *
		 * 析构函数
		 *
		 */
		virtual ~ISocket() = default;

		/**
		 *
		 * 关闭
		 *
		 * @return 是否关闭成功
		 *
		 */
		bool Close() const;

		/**
		 *
		 * 关闭
		 *
		 * @param read 读操作
		 * @param write 写操作
		 *
		 * @return 是否关闭成功
		 *
		 */
		bool Shutdown(bool read = false, bool write = true) const;

		/**
		 *
		 * 是否有效
		 *
		 * @return 是否有效
		 *
		 */
		bool IsValid() const;

		/**
		 *
		 * 设置堵塞状态
		 *
		 * @param on 状态
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetBlockStatus(bool on = true) const;

		/**
		 *
		 * 设置延时关闭状态
		 *
		 * @param timeout 超时时长
		 * @param on 状态
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetLingerStatus(int32_t timeout, bool on = true) const;

		/**
		 *
		 * 设置心跳检测状态
		 *
		 * @param handle 句柄
		 * @param on 状态
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetKeepaliveStatus(bool on = true) const;

		/**
		 *
		 * 设置端口复用状态
		 *
		 * @param on 状态
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetReusePortStatus(bool on = true) const;

		/**
		 *
		 * 设置地址复用状态
		 *
		 * @param on 状态
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetReuseAddressStatus(bool on = true) const;

		/**
		 *
		 * 设置发送超时时间
		 *
		 * @param timeout 超时时间
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetSendTimeout(int32_t timeout) const;

		/**
		 *
		 * 设置接收超时时间
		 *
		 * @param timeout 超时时间
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetReceiveTimeout(int32_t timeout) const;

		/**
		 *
		 * 设置发送缓冲区大小
		 *
		 * @param size 缓冲区大小
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetSendBufferSize(int32_t size) const;

		/**
		 *
		 * 设置接收缓冲区大小
		 *
		 * @param size 缓冲区大小
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetReceiveBufferSize(int32_t size) const;

		/**
		 *
		 * 绑定
		 *
		 * @param endpoint 端点
		 *
		 * @return 绑定结果
		 *
		 */
		int32_t Bind(const Endpoint & endpoint) const;

		/**
		 *
		 * 监听
		 *
		 * @param backlog 上限
		 *
		 * @return 监听结果
		 *
		 */
		int32_t Listen(int32_t backlog = SOMAXCONN) const;

		/**
		 *
		 * 错误号
		 *
		 * @return 错误号
		 *
		 */
		int32_t ErrorCode() const;

		/**
		 *
		 * 可读数据大小
		 *
		 * @return 可读数据大小
		 *
		 */
		int32_t ReadableSize() const;

		/**
		 *
		 * 发送缓冲区大小
		 *
		 * @return 发送缓冲区大小
		 *
		 */
		int32_t SendBufferSize() const;

		/**
		 *
		 * 接收缓冲区大小
		 *
		 * @return 接收缓冲区大小
		 *
		 */
		int32_t ReceiveBufferSize() const;

		/**
		 *
		 * 句柄
		 *
		 * @return 句柄
		 *
		 */
		SOCKET_HANDLE_TYPE Handle() const;

	protected:
		SOCKET_HANDLE_TYPE _handle{ SOCKET_HANDLE_INVALID };
	};

	class API_TYPE TCPSocket : public ISocket
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param family 协议族
		 *
		 */
		explicit TCPSocket(uint16_t family);

		/**
		 *
		 * 构造函数
		 *
		 * @param handle 句柄
		 *
		 */
		explicit TCPSocket(SOCKET_HANDLE_TYPE handle);

		/**
		 *
		 * 析构函数
		 *
		 */
		~TCPSocket() override = default;

		/**
		 *
		 * 设置延时发送状态
		 *
		 * @param on 状态
		 *
		 * @return 是否设置成功
		 *
		 */
		bool SetDelayStatus(bool on = true) const;

		/**
		 *
		 * 发送
		 *
		 * @param buffer 内容
		 * @param length 长度
		 * @param context 上下文
		 *
		 * @return 发送字节数
		 *
		 */
		int32_t Send(void * buffer, std::size_t length, Context * context) const;

		/**
		 *
		 * 接受
		 *
		 * @param context 上下文
		 *
		 * @return 接受结果
		 *
		 */
		int32_t Accept(Context * context) const;

		/**
		 *
		 * 连接
		 *
		 * @param endpoint 端点
		 * @param context 上下文
		 *
		 * @return 连接结果
		 *
		 */
		int32_t Connect(const Endpoint & endpoint, Context * context) const;

		/**
		 *
		 * 接收
		 *
		 * @param buffer 内容
		 * @param length 长度
		 * @param context 上下文
		 *
		 * @return 接收字节数
		 *
		 */
		int32_t Receive(void * buffer, std::size_t length, Context * context) const;
	};
}


#endif // __NET__SOCKET__H__
