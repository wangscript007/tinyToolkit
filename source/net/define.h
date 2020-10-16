#ifndef __NET__DEFINE__H__
#define __NET__DEFINE__H__


/**
 *
 *  作者: hm
 *
 *  说明:  定义
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  ifndef POLL_HANDLE_TYPE
#  define POLL_HANDLE_TYPE				HANDLE
#  endif
#
#  ifndef POLL_HANDLE_INVALID
#  define POLL_HANDLE_INVALID			nullptr
#  endif
#
#  ifndef SOCKET_HANDLE_TYPE
#  define SOCKET_HANDLE_TYPE			SOCKET
#  endif
#
#  ifndef SOCKET_HANDLE_INVALID
#  define SOCKET_HANDLE_INVALID			INVALID_SOCKET
#  endif
#
#else
#
#  ifndef POLL_HANDLE_TYPE
#  define POLL_HANDLE_TYPE				int32_t
#  endif
#
#  ifndef POLL_HANDLE_INVALID
#  define POLL_HANDLE_INVALID			-1
#  endif
#
#  ifndef SOCKET_ERROR
#  define SOCKET_ERROR					-1
#  endif
#
#  ifndef SOCKET_HANDLE_TYPE
#  define SOCKET_HANDLE_TYPE			int32_t
#  endif
#
#  ifndef SOCKET_HANDLE_INVALID
#  define SOCKET_HANDLE_INVALID			-1
#  endif
#
#endif


#endif // __NET__DEFINE__H__
