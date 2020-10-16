/**
 *
 *  作者: hm
 *
 *  说明: 端点
 *
 */


#include "endpoint.h"

#if PLATFORM_TYPE != PLATFORM_WINDOWS
#
#  include <arpa/inet.h>
#
#endif

#include <cstring>


namespace net
{
	/**
	 *
	 * 构造函数
	 *
	 * @param address 地址
	 *
	 */
	Endpoint::Endpoint(const struct sockaddr_in & address)
	{
		_address.v4 = address;
	}

	/**
	 *
	 * 构造函数
	 *
	 * @param address 地址
	 *
	 */
	Endpoint::Endpoint(const struct sockaddr_in6 & address)
	{
		_address.v6 = address;
	}

	/**
	 *
	 * 构造函数
	 *
	 * @param port 端口
	 * @param isIPV6 是否为ipv6
	 *
	 */
	Endpoint::Endpoint(uint16_t port, bool isIPV6)
	{
		if (isIPV6)
		{
			::memset(&_address.v6, 0, sizeof(_address.v6));

			_address.v6.sin6_addr = IN6ADDR_ANY_INIT;
			_address.v6.sin6_port = htons(port);
			_address.v6.sin6_family = AF_INET6;
		}
		else
		{
			::memset(&_address.v4, 0, sizeof(_address.v4));

			_address.v4.sin_addr.s_addr = INADDR_ANY;
			_address.v4.sin_port = htons(port);
			_address.v4.sin_family = AF_INET;
		}
	}

	/**
	 *
	 * 构造函数
	 *
	 * @param host 地址
	 * @param port 端口
	 * @param isIPV6 是否位ipv6
	 *
	 */
	Endpoint::Endpoint(const char * host, uint16_t port, bool isIPV6)
	{
		if (isIPV6)
		{
			::memset(&_address.v6, 0, sizeof(_address.v6));

			::inet_pton(AF_INET6, host, &_address.v6.sin6_addr);

			_address.v6.sin6_port = htons(port);
			_address.v6.sin6_family = AF_INET6;
		}
		else
		{
			::memset(&_address.v4, 0, sizeof(_address.v4));

			::inet_pton(AF_INET, host, &_address.v4.sin_addr);

			_address.v4.sin_port = htons(port);
			_address.v4.sin_family = AF_INET;
		}
	}

	/**
	 *
	 * 设置标识范围
	 *
	 * @param id 标识
	 *
	 */
	void Endpoint::SetScopeID(uint32_t id)
	{
		if (Family() == AF_INET6)
		{
			_address.v6.sin6_scope_id = id;
		}
	}

	/**
	 *
	 * 协议族
	 *
	 * @return 协议族
	 *
	 */
	uint16_t Endpoint::Family() const
	{
		return _address.v4.sin_family;
	}

	/**
	 *
	 * 网络字节序地址
	 *
	 * @return 网络字节序地址
	 *
	 */
	uint32_t Endpoint::NetEndianIP() const
	{
		return _address.v4.sin_addr.s_addr;
	}

	/**
	 *
	 * 主机字节序地址
	 *
	 * @return 主机字节序地址
	 *
	 */
	uint32_t Endpoint::HostEndianIP() const
	{
		return ntohl(NetEndianIP());
	}

	/**
	 *
	 * 网络字节序端口
	 *
	 * @return 网络字节序端口
	 *
	 */
	uint16_t Endpoint::NetEndianPort() const
	{
		return _address.v4.sin_port;
	}

	/**
	 *
	 * 主机字节序端口
	 *
	 * @return 主机字节序端口
	 *
	 */
	uint16_t Endpoint::HostEndianPort() const
	{
		return ntohs(NetEndianPort());
	}

	/**
	 *
	 * 格式化字符串
	 *
	 * @return 格式化字符串
	 *
	 */
	std::string Endpoint::AsString() const
	{
		std::string content{ };

		switch (Family())
		{
			case AF_INET:
			{
				char str[INET_ADDRSTRLEN]{ 0 };

				content += ::inet_ntop(AF_INET, &_address.v4.sin_addr, str, INET_ADDRSTRLEN) ? str : "";
				content += ":";
				content += std::to_string(HostEndianPort());

				break;
			}

			case AF_INET6:
			{
				char str[INET6_ADDRSTRLEN]{ 0 };

				content += ::inet_ntop(AF_INET6, &_address.v6.sin6_addr, str, INET6_ADDRSTRLEN) ? str : "";
				content += ":";
				content += std::to_string(HostEndianPort());

				break;
			}

			default:
			{
				break;
			}
		}

		return content;
	}

	/**
	 *
	 * 套接字地址
	 *
	 * @return 套接字地址
	 *
	 */
	struct sockaddr * Endpoint::SocketAddress()
	{
		return reinterpret_cast<struct sockaddr *>(&_address.v6);
	}

	/**
	 *
	 * 套接字地址
	 *
	 * @return 套接字地址
	 *
	 */
	const struct sockaddr * Endpoint::SocketAddress() const
	{
		return reinterpret_cast<const struct sockaddr *>(&_address.v6);
	}
}
