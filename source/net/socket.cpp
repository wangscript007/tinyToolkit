/**
 *
 *  作者: hm
 *
 *  说明: 套接字
 *
 */


#include "socket.h"
#include "endpoint.h"
#include "operation.h"


namespace net
{
	/**
	 *
	 * 关闭
	 *
	 * @return 是否关闭成功
	 *
	 */
	bool ISocket::Close() const
	{
		return Operation::CloseSocketHandle(_handle);
	}

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
	bool ISocket::Shutdown(bool read, bool write) const
	{
		return Operation::ShutdownSocketHandle(_handle, read, write);
	}

	/**
	 *
	 * 是否有效
	 *
	 * @return 是否有效
	 *
	 */
	bool ISocket::IsValid() const
	{
		return Operation::IsValidSocketHandle(_handle);
	}

	/**
	 *
	 * 设置堵塞状态
	 *
	 * @param on 状态
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetBlockStatus(bool on) const
	{
		return Operation::SetBlockStatus(_handle, on);
	}

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
	bool ISocket::SetLingerStatus(int32_t timeout, bool on) const
	{
		return Operation::SetLingerStatus(_handle, timeout, on);
	}

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
	bool ISocket::SetKeepaliveStatus(bool on) const
	{
		return Operation::SetKeepaliveStatus(_handle, on);
	}

	/**
	 *
	 * 设置端口复用状态
	 *
	 * @param on 状态
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetReusePortStatus(bool on) const
	{
		return Operation::SetReusePortStatus(_handle, on);
	}

	/**
	 *
	 * 设置地址复用状态
	 *
	 * @param on 状态
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetReuseAddressStatus(bool on) const
	{
		return Operation::SetReuseAddressStatus(_handle, on);
	}

	/**
	 *
	 * 设置发送超时时间
	 *
	 * @param timeout 超时时间
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetSendTimeout(int32_t timeout) const
	{
		return Operation::SetSendTimeout(_handle, timeout);
	}

	/**
	 *
	 * 设置接收超时时间
	 *
	 * @param timeout 超时时间
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetReceiveTimeout(int32_t timeout) const
	{
		return Operation::SetReceiveTimeout(_handle, timeout);
	}

	/**
	 *
	 * 设置发送缓冲区大小
	 *
	 * @param size 缓冲区大小
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetSendBufferSize(int32_t size) const
	{
		return Operation::SetSendBufferSize(_handle, size);
	}

	/**
	 *
	 * 设置接收缓冲区大小
	 *
	 * @param size 缓冲区大小
	 *
	 * @return 是否设置成功
	 *
	 */
	bool ISocket::SetReceiveBufferSize(int32_t size) const
	{
		return Operation::SetReceiveBufferSize(_handle, size);
	}

	/**
	 *
	 * 绑定
	 *
	 * @param endpoint 端点
	 *
	 * @return 绑定结果
	 *
	 */
	int32_t ISocket::Bind(const Endpoint & endpoint) const
	{
		return Operation::Bind(_handle, endpoint.SocketAddress());
	}

	/**
	 *
	 * 监听
	 *
	 * @param backlog 上限
	 *
	 * @return 监听结果
	 *
	 */
	int32_t ISocket::Listen(int32_t backlog) const
	{
		return Operation::Listen(_handle, backlog);
	}

	/**
	 *
	 * 错误号
	 *
	 * @return 错误号
	 *
	 */
	int32_t ISocket::ErrorCode() const
	{
		return Operation::SocketErrorCode(_handle);
	}

	/**
	 *
	 * 可读数据大小
	 *
	 * @return 可读数据大小
	 *
	 */
	int32_t ISocket::ReadableSize() const
	{
		return Operation::ReadableSize(_handle);
	}

	/**
	 *
	 * 发送缓冲区大小
	 *
	 * @return 发送缓冲区大小
	 *
	 */
	int32_t ISocket::SendBufferSize() const
	{
		return Operation::SendBufferSize(_handle);
	}

	/**
	 *
	 * 接收缓冲区大小
	 *
	 * @return 接收缓冲区大小
	 *
	 */
	int32_t ISocket::ReceiveBufferSize() const
	{
		return Operation::ReceiveBufferSize(_handle);
	}

	/**
	 *
	 * 句柄
	 *
	 * @return 句柄
	 *
	 */
	SOCKET_HANDLE_TYPE ISocket::Handle() const
	{
		return _handle;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	 *
	 * 构造函数
	 *
	 * @param family 协议族
	 *
	 */
	TCPSocket::TCPSocket(uint16_t family)
	{
		_handle = Operation::TCPSocketHandle(family);
	}

	/**
	 *
	 * 构造函数
	 *
	 * @param handle 句柄
	 *
	 */
	TCPSocket::TCPSocket(SOCKET_HANDLE_TYPE handle)
	{
		_handle = handle;
	}

	/**
	 *
	 * 设置延时发送状态
	 *
	 * @param on 状态
	 *
	 * @return 是否设置成功
	 *
	 */
	bool TCPSocket::SetDelayStatus(bool on) const
	{
		return Operation::SetDelayStatus(_handle, on);
	}

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
	int32_t TCPSocket::Send(void * buffer, std::size_t length, Context * context) const
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::memset(&context->overlap, 0, sizeof(OVERLAPPED));

		context->buffer.buf = reinterpret_cast<CHAR *>(buffer);
		context->buffer.len = static_cast<ULONG>(length);

		return Operation::Send(_handle, &context->buffer, 1, context);

	#else

		return Operation::Send(_handle, buffer, length, context);

	#endif
	}

	/**
	 *
	 * 接受
	 *
	 * @param context 上下文
	 *
	 * @return 接受结果
	 *
	 */
	int32_t TCPSocket::Accept(Context * context) const
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::memset(&context->overlap, 0, sizeof(OVERLAPPED));

		context->buffer.buf = reinterpret_cast<CHAR *>(context->temp);
		context->buffer.len = static_cast<ULONG>(sizeof(context->temp));

		if (Operation::Accept(_handle, context->handle, context->temp, context) == SOCKET_ERROR)
		{
			Operation::CloseSocketHandle(context->handle);

			context->handle = SOCKET_HANDLE_INVALID;

			return SOCKET_ERROR;
		}

	#else

		context->handle = Operation::Accept(_handle, SOCKET_HANDLE_INVALID, nullptr, nullptr);

		if (context->handle == SOCKET_HANDLE_INVALID)
		{
			return SOCKET_ERROR;
		}

	#endif

		return 0;
	}

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
	int32_t TCPSocket::Connect(const Endpoint & endpoint, Context * context) const
	{
		return Operation::Connect(_handle, endpoint.SocketAddress(), context);
	}

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
	int32_t TCPSocket::Receive(void * buffer, std::size_t length, Context * context) const
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		::memset(&context->overlap, 0, sizeof(OVERLAPPED));

		context->buffer.buf = reinterpret_cast<CHAR *>(buffer);
		context->buffer.len = static_cast<ULONG>(length);

		return Operation::Receive(_handle, &context->buffer, 1, context);

	#else

		return Operation::Receive(_handle, buffer, length, context);

	#endif
	}
}
