#ifndef __COMMON__SYMBOL__H__
#define __COMMON__SYMBOL__H__


/**
 *
 *  作者: hm
 *
 *  说明: 符号信息
 *
 */


#if defined( _MSC_VER )
#
#  pragma warning(disable:4251)
#  pragma warning(disable:4275)
#
#  define SYMBOL_EXPORT __declspec(dllexport)
#  define SYMBOL_IMPORT __declspec(dllimport)
#
#elif defined( __GNUC__ )
#
#  define SYMBOL_EXPORT __attribute__((visibility("default")))
#  define SYMBOL_IMPORT
#
#else
#
#  define SYMBOL_EXPORT
#  define SYMBOL_IMPORT
#
#endif


#if defined(API_IMPORT)
#
#  define API_TYPE SYMBOL_IMPORT
#
#else
#
#  define API_TYPE SYMBOL_EXPORT
#
#endif


#endif // __COMMON__SYMBOL__H__
