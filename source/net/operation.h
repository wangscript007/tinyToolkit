#ifndef __NET__OPERATION__H__
#define __NET__OPERATION__H__


/**
 *
 *  作者: hm
 *
 *  说明: 操作
 *
 */


#include "define.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <WS2tcpip.h>
#
#else
#
#  include <netinet/in.h>
#
#endif

#include <cstring>
#include <cstdint>


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE Operation
		{
		public:
			/**
			 *
			 * 获取目标地址结构
			 *
			 * @param handle 句柄
			 * @param address 地址结构
			 *
			 * @return 是否获取成功
			 *
			 */
			static bool GetPeerAddress(SOCKET_HANDLE_TYPE handle, struct sockaddr * address);

			/**
			 *
			 * 获取本地地址结构
			 *
			 * @param handle 句柄
			 * @param address 地址结构
			 *
			 * @return 是否获取成功
			 *
			 */
			static bool GetLocalAddress(SOCKET_HANDLE_TYPE handle, struct sockaddr * address);

			/**
			 *
			 * 设置堵塞状态
			 *
			 * @param handle 句柄
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetBlockStatus(SOCKET_HANDLE_TYPE handle, bool on = true);

			/**
			 *
			 * 设置延时发送状态
			 *
			 * @param handle 句柄
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetDelayStatus(SOCKET_HANDLE_TYPE handle, bool on = true);

			/**
			 *
			 * 设置信号处理状态
			 *
			 * @param handle 句柄
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetSignalStatus(SOCKET_HANDLE_TYPE handle, bool on = true);

			/**
			 *
			 * 设置延时关闭状态
			 *
			 * @param handle 句柄
			 * @param timeout 超时时长
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetLingerStatus(SOCKET_HANDLE_TYPE handle, int32_t timeout, bool on = true);

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
			static bool SetKeepaliveStatus(SOCKET_HANDLE_TYPE handle, bool on = true);

			/**
			 *
			 * 设置端口复用状态
			 *
			 * @param handle 句柄
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetReusePortStatus(SOCKET_HANDLE_TYPE handle, bool on = true);

			/**
			 *
			 * 设置地址复用状态
			 *
			 * @param handle 句柄
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetReuseAddressStatus(SOCKET_HANDLE_TYPE handle, bool on = true);

			/**
			 *
			 * 设置发送超时时间
			 *
			 * @param handle 句柄
			 * @param timeout 超时时间
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetSendTimeout(SOCKET_HANDLE_TYPE handle, int32_t timeout);

			/**
			 *
			 * 设置接收超时时间
			 *
			 * @param handle 句柄
			 * @param timeout 超时时间
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetReceiveTimeout(SOCKET_HANDLE_TYPE handle, int32_t timeout);

			/**
			 *
			 * 设置发送缓冲区大小
			 *
			 * @param handle 句柄
			 * @param size 缓冲区大小
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetSendBufferSize(SOCKET_HANDLE_TYPE handle, int32_t size);

			/**
			 *
			 * 设置接收缓冲区大小
			 *
			 * @param handle 句柄
			 * @param size 缓冲区大小
			 *
			 * @return 是否设置成功
			 *
			 */
			static bool SetReceiveBufferSize(SOCKET_HANDLE_TYPE handle, int32_t size);

			/**
			 *
			 * 关闭轮询句柄
			 *
			 * @param handle 句柄
			 *
			 * @return 是否关闭成功
			 *
			 */
			static bool ClosePollHandle(POLL_HANDLE_TYPE handle);

			/**
			 *
			 * 关闭套接字句柄
			 *
			 * @param handle 句柄
			 *
			 * @return 是否关闭成功
			 *
			 */
			static bool CloseSocketHandle(SOCKET_HANDLE_TYPE handle);

			/**
			 *
			 * 关闭套接字句柄
			 *
			 * @param handle 句柄
			 * @param read 读操作
			 * @param write 写操作
			 *
			 * @return 是否关闭成功
			 *
			 */
			static bool ShutdownSocketHandle(SOCKET_HANDLE_TYPE handle, bool read = false, bool write = true);

			/**
			 *
			 * 轮询句柄是否有效
			 *
			 * @param handle 句柄
			 *
			 * @return 轮询句柄是否有效
			 *
			 */
			static bool IsValidPollHandle(POLL_HANDLE_TYPE handle);

			/**
			 *
			 * 套接字句柄是否有效
			 *
			 * @param handle 句柄
			 *
			 * @return 套接字句柄是否有效
			 *
			 */
			static bool IsValidSocketHandle(SOCKET_HANDLE_TYPE handle);

			/**
			 *
			 * 绑定
			 *
			 * @param handle 句柄
			 * @param address 地址
			 *
			 * @return 绑定结果
			 *
			 */
			static int32_t Bind(SOCKET_HANDLE_TYPE handle, const struct sockaddr * address);

			/**
			 *
			 * 监听
			 *
			 * @param handle 句柄
			 * @param backlog 上限
			 *
			 * @return 监听结果
			 *
			 */
			static int32_t Listen(SOCKET_HANDLE_TYPE handle, int32_t backlog = SOMAXCONN);

			/**
			 *
			 * 接受
			 *
			 * @param handle 句柄
			 * @param acceptHandle 接受句柄
			 * @param buffer 缓冲区
			 * @param context 上下文
			 *
			 * @return 接受结果
			 *
			 */
			static int32_t Accept(SOCKET_HANDLE_TYPE handle, SOCKET_HANDLE_TYPE acceptHandle, void * buffer, void * context);

			/**
			 *
			 * 连接
			 *
			 * @param handle 句柄
			 * @param address 地址
			 * @param context 上下文
			 *
			 * @return 连接结果
			 *
			 */
			static int32_t Connect(SOCKET_HANDLE_TYPE handle, const struct sockaddr * address, void * context);

			/**
			 *
			 * 发送
			 *
			 * @param handle 句柄
			 * @param buffer 内容
			 * @param length 长度
			 * @param context 上下文
			 *
			 * @return 发送结果
			 *
			 */
			static int32_t Send(SOCKET_HANDLE_TYPE handle, void * buffer, std::size_t length, void * context);

			/**
			 *
			 * 接收
			 *
			 * @param handle 句柄
			 * @param buffer 内容
			 * @param length 长度
			 * @param context 上下文
			 *
			 * @return 接收结果
			 *
			 */
			static int32_t Receive(SOCKET_HANDLE_TYPE handle, void * buffer, std::size_t length, void * context);

			/**
			 *
			 * 接收
			 *
			 * @param handle 句柄
			 * @param buffer 内容
			 * @param length 长度
			 * @param address 地址
			 * @param addressLength 地址长度
			 * @param context 上下文
			 *
			 * @return 接收结果
			 *
			 */
			static int32_t ReceiveFrom(SOCKET_HANDLE_TYPE handle, void * buffer, std::size_t length, struct sockaddr * address, std::size_t addressLength, void * context);

			/**
			 *
			 * 可读数据大小
			 *
			 * @param handle 句柄
			 *
			 * @return 可读数据大小
			 *
			 */
			static int32_t ReadableSize(SOCKET_HANDLE_TYPE handle);

			/**
			 *
			 * 发送缓冲区大小
			 *
			 * @param handle 句柄
			 *
			 * @return 发送缓冲区大小
			 *
			 */
			static int32_t SendBufferSize(SOCKET_HANDLE_TYPE handle);

			/**
			 *
			 * 接收缓冲区大小
			 *
			 * @param handle 句柄
			 *
			 * @return 接收缓冲区大小
			 *
			 */
			static int32_t ReceiveBufferSize(SOCKET_HANDLE_TYPE handle);

			/**
			 *
			 * 套接字错误号
			 *
			 * @param handle 句柄
			 *
			 * @return 套接字错误号
			 *
			 */
			static int32_t SocketErrorCode(SOCKET_HANDLE_TYPE handle);

			/**
			 *
			 * 轮询句柄
			 *
			 * @return 轮询句柄
			 *
			 */
			static POLL_HANDLE_TYPE PollHandle();

			/**
			 *
			 * tcp套接字句柄
			 *
			 * @param family 协议族
			 *
			 * @return tcp套接字句柄
			 *
			 */
			static SOCKET_HANDLE_TYPE TCPSocketHandle(uint16_t family);

			/**
			 *
			 * udp套接字句柄
			 *
			 * @param family 协议族
			 *
			 * @return udp套接字句柄
			 *
			 */
			static SOCKET_HANDLE_TYPE UDPSocketHandle(uint16_t family);
		};
	}
}


#endif // __NET__OPERATION__H__
