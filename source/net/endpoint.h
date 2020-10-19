#ifndef __NET__ENDPOINT__H__
#define __NET__ENDPOINT__H__


/**
 *
 *  作者: hm
 *
 *  说明: 端点
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <WS2tcpip.h>
#
#else
#
#  include <netinet/in.h>
#
#endif

#include <string>


namespace net
{
	class API_TYPE Endpoint
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		explicit Endpoint() = default;

		/**
		 *
		 * 构造函数
		 *
		 * @param address 地址
		 *
		 */
		explicit Endpoint(const struct sockaddr_in & address);

		/**
		 *
		 * 构造函数
		 *
		 * @param address 地址
		 *
		 */
		explicit Endpoint(const struct sockaddr_in6 & address);

		/**
		 *
		 * 构造函数
		 *
		 * @param port 端口
		 * @param isIPV6 是否为ipv6
		 *
		 */
		explicit Endpoint(uint16_t port, bool isIPV6 = false);

		/**
		 *
		 * 构造函数
		 *
		 * @param host 地址
		 * @param port 端口
		 * @param isIPV6 是否位ipv6
		 *
		 */
		explicit Endpoint(const char * host, uint16_t port, bool isIPV6 = false);

		/**
		 *
		 * 设置标识范围
		 *
		 * @param id 标识
		 *
		 */
		void SetScopeID(uint32_t id);

		/**
		 *
		 * 协议族
		 *
		 * @return 协议族
		 *
		 */
		uint16_t Family() const;

		/**
		 *
		 * 网络字节序地址
		 *
		 * @return 网络字节序地址
		 *
		 */
		uint32_t NetEndianIP() const;

		/**
		 *
		 * 主机字节序地址
		 *
		 * @return 主机字节序地址
		 *
		 */
		uint32_t HostEndianIP() const;

		/**
		 *
		 * 网络字节序端口
		 *
		 * @return 网络字节序端口
		 *
		 */
		uint16_t NetEndianPort() const;

		/**
		 *
		 * 主机字节序端口
		 *
		 * @return 主机字节序端口
		 *
		 */
		uint16_t HostEndianPort() const;

		/**
		 *
		 * 格式化字符串
		 *
		 * @return 格式化字符串
		 *
		 */
		std::string AsString() const;

		/**
		 *
		 * 套接字地址
		 *
		 * @return 套接字地址
		 *
		 */
		struct sockaddr * SocketAddress();

		/**
		 *
		 * 套接字地址
		 *
		 * @return 套接字地址
		 *
		 */
		const struct sockaddr * SocketAddress() const;

	private:
		union
		{
			struct sockaddr_in v4;
			struct sockaddr_in6 v6;
		}_address{ };
	};
}


#endif // __NET__ENDPOINT__H__
