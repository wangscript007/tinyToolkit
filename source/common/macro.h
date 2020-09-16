#ifndef __COMMON__MACRO__H__
#define __COMMON__MACRO__H__


/**
 *
 *  作者: hm
 *
 *  说明: 宏定义
 *
 */


#include "platform.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  ifndef CURRENT_FILE
#  define CURRENT_FILE						__FILE__
#  endif
#
#  ifndef CURRENT_LINE
#  define CURRENT_LINE						__LINE__
#  endif
#
#  ifndef CURRENT_FUNC
#  define CURRENT_FUNC						__FUNCSIG__
#  endif
#
#else
#
#  ifndef CURRENT_FILE
#  define CURRENT_FILE						__FILE__
#  endif
#
#  ifndef CURRENT_LINE
#  define CURRENT_LINE						__LINE__
#  endif
#
#  ifndef CURRENT_FUNC
#  define CURRENT_FUNC						__PRETTY_FUNCTION__
#  endif
#
#endif


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  ifndef NAME_MAX
#  define NAME_MAX						_MAX_FNAME
#  endif
#
#  ifndef PATH_MAX
#  define PATH_MAX						_MAX_PATH
#  endif
#
#  ifndef PATH_SEP
#  define PATH_SEP						"\\"
#  endif
#
#  ifndef LINE_EOL
#  define LINE_EOL						"\r\n"
#  endif
#
#else
#
#  ifndef NAME_MAX
#  define NAME_MAX						255
#  endif
#
#  ifndef PATH_MAX
#  define PATH_MAX						4096
#  endif
#
#  ifndef PATH_SEP
#  define PATH_SEP						"/"
#  endif
#
#  ifndef LINE_EOL
#  define LINE_EOL						"\n"
#  endif
#
#endif


#endif // __COMMON__MACRO__H__
