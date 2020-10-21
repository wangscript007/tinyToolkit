/**
 *
 *  作者: hm
 *
 *  说明: 操作
 *
 */


#include "operation.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <MSWSock.h>
#
#  pragma comment(lib,"ws2_32.lib")
#
#else
#
#  include <cerrno>
#
#  include <fcntl.h>
#  include <unistd.h>
#
#  include <sys/ioctl.h>
#
#  include <netinet/tcp.h>
#
#  if PLATFORM_TYPE == PLATFORM_APPLE
#
#    include <sys/event.h>
#
#  else
#
#    include <sys/epoll.h>
#
#  endif
#
#endif


namespace tinyToolkit
{
	namespace net
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		/**
		 *
		 * 异步发送处理
		 *
		 * @param handle 套接字句柄
		 * @param buffer 缓冲区
		 * @param count 缓冲区个数
		 * @param overlapped 结构指针
		 *
		 */
		static int32_t WINAPI SendEx(SOCKET_HANDLE_TYPE handle, LPWSABUF buffer, DWORD count, LPWSAOVERLAPPED overlapped)
		{
			DWORD flag = 0;
			DWORD bytes = 0;

			if (::WSASend(handle, buffer, count, &bytes, flag, overlapped, nullptr) == SOCKET_ERROR)
			{
				if (::WSAGetLastError() != WSA_IO_PENDING)
				{
					return SOCKET_ERROR;
				}
			}

			return 0;
		}

		/**
		 *
		 * 异步接收处理
		 *
		 * @param handle 套接字句柄
		 * @param buffer 缓冲区
		 * @param count 缓冲区个数
		 * @param overlapped 结构指针
		 *
		 */
		static int32_t WINAPI ReceiveEx(SOCKET_HANDLE_TYPE handle, LPWSABUF buffer, DWORD count, LPWSAOVERLAPPED overlapped)
		{
			DWORD flag = 0;
			DWORD bytes = 0;

			if (::WSARecv(handle, buffer, count, &bytes, &flag, overlapped, nullptr) == SOCKET_ERROR)
			{
				if (::WSAGetLastError() != WSA_IO_PENDING)
				{
					return SOCKET_ERROR;
				}
			}

			return 0;
		}

		/**
		 *
		 * 异步接收处理
		 *
		 * @param handle 套接字句柄
		 * @param buffer 缓冲区
		 * @param count 缓冲区个数
		 * @param address 地址
		 * @param addressLength 地址长度
		 * @param overlapped 结构指针
		 *
		 */
		static int32_t WINAPI ReceiveFromEx(SOCKET_HANDLE_TYPE handle, LPWSABUF buffer, DWORD count, struct sockaddr * address, socklen_t addressLength, LPWSAOVERLAPPED overlapped)
		{
			DWORD flag = 0;
			DWORD bytes = 0;

			if (::WSARecvFrom(handle, buffer, count, &bytes, &flag, address, &addressLength, overlapped, nullptr) == SOCKET_ERROR)
			{
				if (::WSAGetLastError() != WSA_IO_PENDING)
				{
					return SOCKET_ERROR;
				}
			}

			return 0;
		}

		/**
		 *
		 * 异步接收处理
		 *
		 * @param listenHandle 监听套接字句柄
		 * @param acceptHandle 连接套接字句柄
		 * @param buffer 缓冲区
		 * @param overlapped 结构指针
		 *
		 * @return 是否处理成功
		 *
		 */
		static int32_t WINAPI AcceptEx(SOCKET_HANDLE_TYPE listenHandle, SOCKET_HANDLE_TYPE acceptHandle, PVOID buffer, LPOVERLAPPED overlapped)
		{
			static LPFN_ACCEPTEX function = nullptr;

			if (function == nullptr)
			{
				GUID guid = WSAID_ACCEPTEX;

				DWORD byte = 0;

				::WSAIoctl
				(
					listenHandle,
					SIO_GET_EXTENSION_FUNCTION_POINTER,
					&guid,
					sizeof(guid),
					&function,
					sizeof(function),
					&byte,
					nullptr,
					nullptr
				);
			}

			if (function == nullptr)
			{
				return SOCKET_ERROR;
			}

			DWORD byte = 0;

			if (function(listenHandle, acceptHandle, buffer, 0, sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, &byte, overlapped) == FALSE)
			{
				if (::WSAGetLastError() != WSA_IO_PENDING)
				{
					return SOCKET_ERROR;
				}
			}

			return 0;
		}

		/**
		 *
		 * 异步连接处理
		 *
		 * @param handle 套接字句柄
		 * @param address 地址
		 * @param addressLength 地址长度
		 * @param overlapped 结构指针
		 *
		 * @return 是否处理成功
		 *
		 */
		static int32_t WINAPI ConnectEx(SOCKET_HANDLE_TYPE handle, const struct sockaddr * address, socklen_t addressLength, LPOVERLAPPED overlapped)
		{
			static LPFN_CONNECTEX function = nullptr;

			if (function == nullptr)
			{
				GUID guid = WSAID_CONNECTEX;

				DWORD byte = 0;

				::WSAIoctl
				(
					handle,
					SIO_GET_EXTENSION_FUNCTION_POINTER,
					&guid,
					sizeof(guid),
					&function,
					sizeof(function),
					&byte,
					nullptr,
					nullptr
				);
			}

			if (function == nullptr)
			{
				return SOCKET_ERROR;
			}

			DWORD byte = 0;

			if (function(handle, address, addressLength, nullptr, 0, &byte, overlapped) == FALSE)
			{
				if (::WSAGetLastError() != WSA_IO_PENDING)
				{
					return SOCKET_ERROR;
				}
			}

			return 0;
		}

	#endif


		////////////////////////////////////////////////////////////////////////////////////////////////////


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
		bool Operation::GetPeerAddress(SOCKET_HANDLE_TYPE handle, struct sockaddr * address)
		{
			socklen_t length = sizeof(struct sockaddr_in6);

			return ::getpeername(handle, address, &length) == 0;
		}

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
		bool Operation::GetLocalAddress(SOCKET_HANDLE_TYPE handle, struct sockaddr * address)
		{
			socklen_t length = sizeof(struct sockaddr_in6);

			return ::getsockname(handle, address, &length) == 0;
		}

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
		bool Operation::SetBlockStatus(SOCKET_HANDLE_TYPE handle, bool on)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			u_long val = on ? 0 : 1;

			return ::ioctlsocket(handle, FIONBIO, &val) == 0;

		#else

			if (on)
			{
				return ::fcntl(handle, F_SETFL, ::fcntl(handle, F_GETFL, 0) & ~O_NONBLOCK) == 0;
			}
			else
			{
				return ::fcntl(handle, F_SETFL, ::fcntl(handle, F_GETFL, 0) |  O_NONBLOCK) == 0 &&
				       ::fcntl(handle, F_SETFD, ::fcntl(handle, F_GETFD, 0) |  FD_CLOEXEC) == 0;
			}

		#endif
		}

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
		bool Operation::SetDelayStatus(SOCKET_HANDLE_TYPE handle, bool on)
		{
			int32_t val = on ? 0 : 1;

			return ::setsockopt(handle, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;
		}

		/**
		 *
		 * 设置延时关闭状态
		 *
		 * @param handle 句柄
		 * @param on 状态
		 * @param timeout 超时时长
		 *
		 * @return 是否设置成功
		 *
		 */
		bool Operation::SetLingerStatus(SOCKET_HANDLE_TYPE handle, int32_t timeout, bool on)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			LINGER val{ };

		#else

			struct linger val{ };

		#endif

			val.l_onoff = on ? 1 : 0;
			val.l_linger = timeout;

			return ::setsockopt(handle, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;
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
		bool Operation::SetKeepaliveStatus(SOCKET_HANDLE_TYPE handle, bool on)
		{
			int32_t val = on ? 0 : 1;

			return ::setsockopt(handle, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;
		}

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
		bool Operation::SetReusePortStatus(SOCKET_HANDLE_TYPE handle, bool on)
		{
		#ifdef SO_REUSEPORT

			int32_t val = on ? 1 : 0;

			return ::setsockopt(handle, SOL_SOCKET, SO_REUSEPORT, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;

		#else

			(void)on;
			(void)handle;

			return false;

		#endif
		}

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
		bool Operation::SetReuseAddressStatus(SOCKET_HANDLE_TYPE handle, bool on)
		{
			int32_t val = on ? 1 : 0;

			return ::setsockopt(handle, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;
		}

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
		bool Operation::SetSendTimeout(SOCKET_HANDLE_TYPE handle, int32_t timeout)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			int64_t val = timeout * 1000;

		#else

			struct timeval val
			{
				.tv_sec = timeout,
				.tv_usec = 0
			};

		#endif

			return ::setsockopt(handle, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;
		}

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
		bool Operation::SetReceiveTimeout(SOCKET_HANDLE_TYPE handle, int32_t timeout)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			int64_t val = timeout * 1000;

		#else

			struct timeval val
			{
				.tv_sec = timeout,
				.tv_usec = 0
			};

		#endif

			return ::setsockopt(handle, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&val), static_cast<socklen_t>(sizeof(val))) == 0;
		}

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
		bool Operation::SetSendBufferSize(SOCKET_HANDLE_TYPE handle, int32_t size)
		{
			return ::setsockopt(handle, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<const char *>(&size), static_cast<socklen_t>(sizeof(size))) == 0;
		}

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
		bool Operation::SetReceiveBufferSize(SOCKET_HANDLE_TYPE handle, int32_t size)
		{
			return ::setsockopt(handle, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char *>(&size), static_cast<socklen_t>(sizeof(size))) == 0;
		}

		/**
		 *
		 * 关闭轮询句柄
		 *
		 * @param handle 句柄
		 *
		 * @return 是否关闭成功
		 *
		 */
		bool Operation::ClosePollHandle(POLL_HANDLE_TYPE handle)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			::WSACleanup();

			return ::CloseHandle(handle) == TRUE;

		#else

			return ::close(handle) == 0;

		#endif
		}

		/**
		 *
		 * 关闭套接字句柄
		 *
		 * @param handle 句柄
		 *
		 * @return 是否关闭成功
		 *
		 */
		bool Operation::CloseSocketHandle(SOCKET_HANDLE_TYPE handle)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			::WSACleanup();

			return ::closesocket(handle) == 0;

		#else

			return ::close(handle) == 0;

		#endif
		}

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
		bool Operation::ShutdownSocketHandle(SOCKET_HANDLE_TYPE handle, bool read, bool write)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			if (read && write)
			{
				return ::shutdown(handle, SD_BOTH) == 0;
			}
			else if (read)
			{
				return ::shutdown(handle, SD_RECEIVE) == 0;
			}
			else if (write)
			{
				return ::shutdown(handle, SD_SEND) == 0;
			}

		#else

			if (read && write)
			{
				return ::shutdown(handle, SHUT_RDWR) == 0;
			}
			else if (read)
			{
				return ::shutdown(handle, SHUT_RD) == 0;
			}
			else if (write)
			{
				return ::shutdown(handle, SHUT_WR) == 0;
			}

		#endif

			return false;
		}

		/**
		 *
		 * 轮询句柄是否有效
		 *
		 * @param handle 句柄
		 *
		 * @return 轮询句柄是否有效
		 *
		 */
		bool Operation::IsValidPollHandle(POLL_HANDLE_TYPE handle)
		{
			return handle != POLL_HANDLE_INVALID;
		}

		/**
		 *
		 * 套接字句柄是否有效
		 *
		 * @param handle 句柄
		 *
		 * @return 套接字句柄是否有效
		 *
		 */
		bool Operation::IsValidSocketHandle(SOCKET_HANDLE_TYPE handle)
		{
			return handle != SOCKET_HANDLE_INVALID;
		}

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
		int32_t Operation::Bind(SOCKET_HANDLE_TYPE handle, const struct sockaddr * address)
		{
			return ::bind(handle, address, static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
		}

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
		int32_t Operation::Listen(SOCKET_HANDLE_TYPE handle, int32_t backlog)
		{
			return ::listen(handle, backlog);
		}

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
		int32_t Operation::Accept(SOCKET_HANDLE_TYPE handle, SOCKET_HANDLE_TYPE acceptHandle, void * buffer, void * context)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return AcceptEx(handle, acceptHandle, buffer, reinterpret_cast<LPOVERLAPPED>(context));

		#else

			(void)context;
			(void)acceptHandle;

			socklen_t length = buffer ? static_cast<socklen_t>(sizeof(struct sockaddr_in6)) : 0;

			#if defined (NO_ACCEPT4)

				return ::accept(handle, reinterpret_cast<struct sockaddr *>(buffer), &length);

			#else

				return ::accept4(handle, reinterpret_cast<struct sockaddr *>(buffer), &length, SOCK_NONBLOCK | SOCK_CLOEXEC);

			#endif

		#endif
		}

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
		int32_t Operation::Connect(SOCKET_HANDLE_TYPE handle, const struct sockaddr * address, void * context)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return ConnectEx(handle, address, static_cast<socklen_t>(sizeof(struct sockaddr_in6)), reinterpret_cast<LPOVERLAPPED>(context));

		#else

			(void)context;

			return ::connect(handle, address, static_cast<socklen_t>(sizeof(struct sockaddr_in6)));

		#endif
		}

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
		int32_t Operation::Send(SOCKET_HANDLE_TYPE handle, void * buffer, std::size_t length, void * context)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return SendEx(handle, reinterpret_cast<LPWSABUF>(buffer), static_cast<DWORD>(length), reinterpret_cast<LPWSAOVERLAPPED>(context));

		#elif PLATFORM_TYPE == PLATFORM_APPLE

			(void)context;

			return static_cast<int32_t>(::send(handle, buffer, length, SO_NOSIGPIPE));

		#else

			(void)context;

			return static_cast<int32_t>(::send(handle, buffer, length, MSG_NOSIGNAL));

		#endif
		}

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
		int32_t Operation::Receive(SOCKET_HANDLE_TYPE handle, void * buffer, std::size_t length, void * context)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return ReceiveEx(handle, reinterpret_cast<LPWSABUF>(buffer), static_cast<DWORD>(length), reinterpret_cast<LPWSAOVERLAPPED>(context));

		#elif PLATFORM_TYPE == PLATFORM_APPLE

			(void)context;

			return static_cast<int32_t>(::recv(handle, buffer, length, SO_NOSIGPIPE));

		#else

			(void)context;

			return static_cast<int32_t>(::recv(handle, buffer, length, MSG_NOSIGNAL));

		#endif
		}

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
		int32_t Operation::ReceiveFrom(SOCKET_HANDLE_TYPE handle, void * buffer, std::size_t length, struct sockaddr * address, std::size_t addressLength, void * context)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return ReceiveFromEx(handle, reinterpret_cast<LPWSABUF>(buffer), static_cast<DWORD>(length), address, static_cast<socklen_t>(addressLength), reinterpret_cast<LPWSAOVERLAPPED>(context));

		#elif PLATFORM_TYPE == PLATFORM_APPLE

			(void)context;

			return static_cast<int32_t>(::recvfrom(handle, buffer, length, SO_NOSIGPIPE, address, reinterpret_cast<socklen_t *>(&addressLength)));

		#else

			(void)context;

			return static_cast<int32_t>(::recvfrom(handle, buffer, length, MSG_NOSIGNAL, address, reinterpret_cast<socklen_t *>(&addressLength)));

		#endif
		}

		/**
		 *
		 * 可读数据大小
		 *
		 * @param handle 句柄
		 *
		 * @return 可读数据大小
		 *
		 */
		int32_t Operation::ReadableSize(SOCKET_HANDLE_TYPE handle)
		{
			int32_t val = 0;

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return ::ioctlsocket(handle, FIONBIO, reinterpret_cast<u_long *>(&val)) == 0 ? val : 0;

		#else

			return ::ioctl(handle, FIONREAD, &val) == 0 ? val : 0;

		#endif
		}

		/**
		 *
		 * 发送缓冲区大小
		 *
		 * @param handle 句柄
		 *
		 * @return 发送缓冲区大小
		 *
		 */
		int32_t Operation::SendBufferSize(SOCKET_HANDLE_TYPE handle)
		{
			int32_t val = 0;

			socklen_t length = sizeof(val);

			return ::getsockopt(handle, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char *>(&val), &length) == 0 ? val : 0;
		}

		/**
		 *
		 * 接收缓冲区大小
		 *
		 * @param handle 句柄
		 *
		 * @return 接收缓冲区大小
		 *
		 */
		int32_t Operation::ReceiveBufferSize(SOCKET_HANDLE_TYPE handle)
		{
			int32_t val = 0;

			socklen_t length = sizeof(val);

			return ::getsockopt(handle, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char *>(&val), &length) == 0 ? val : 0;
		}

		/**
		 *
		 * 套接字错误号
		 *
		 * @param handle 句柄
		 *
		 * @return 套接字错误号
		 *
		 */
		int32_t Operation::SocketErrorCode(SOCKET_HANDLE_TYPE handle)
		{
			int32_t val = 0;

			socklen_t length = sizeof(val);

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			return ::getsockopt(handle, SOL_SOCKET, SO_ERROR, reinterpret_cast<char *>(&val), &length) == 0 ? val : ::GetLastError();

		#else

			return ::getsockopt(handle, SOL_SOCKET, SO_ERROR, reinterpret_cast<char *>(&val), &length) == 0 ? val : errno;

		#endif
		}

		/**
		 *
		 * 轮询句柄
		 *
		 * @return 轮询句柄
		 *
		 */
		POLL_HANDLE_TYPE Operation::PollHandle()
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			WSADATA wsaData{ };

			if (::WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
			{
				return POLL_HANDLE_INVALID;
			}

			if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
			{
				::WSACleanup();

				return POLL_HANDLE_INVALID;
			}

			return ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);

		#elif PLATFORM_TYPE == PLATFORM_APPLE

			return ::kqueue();

		#else

			return ::epoll_create1(EPOLL_CLOEXEC);

		#endif
		}

		/**
		 *
		 * tcp套接字句柄
		 *
		 * @param family 协议族
		 *
		 * @return tcp套接字句柄
		 *
		 */
		SOCKET_HANDLE_TYPE Operation::TCPSocketHandle(uint16_t family)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			WSADATA wsaData{ };

			if (::WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
			{
				return SOCKET_HANDLE_INVALID;
			}

			if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
			{
				::WSACleanup();

				return SOCKET_HANDLE_INVALID;
			}

			return ::WSASocketW(family, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);

		#else

			return ::socket(family, SOCK_STREAM, IPPROTO_TCP);

		#endif
		}

		/**
		 *
		 * udp套接字句柄
		 *
		 * @param family 协议族
		 *
		 * @return udp套接字句柄
		 *
		 */
		SOCKET_HANDLE_TYPE Operation::UDPSocketHandle(uint16_t family)
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			WSADATA wsaData{ };

			if (::WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
			{
				return SOCKET_HANDLE_INVALID;
			}

			if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
			{
				::WSACleanup();

				return SOCKET_HANDLE_INVALID;
			}

			return ::WSASocketW(family, SOCK_DGRAM, IPPROTO_UDP, nullptr, 0, WSA_FLAG_OVERLAPPED);

		#else

			return ::socket(family, SOCK_DGRAM, IPPROTO_UDP);

		#endif
		}
	}
}
