#ifndef __UTIL__FILESYSTEM__H__
#define __UTIL__FILESYSTEM__H__


/**
 *
 *  作者: hm
 *
 *  说明: 文件处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <windows.h>
#
#endif

#include <regex>


namespace tinyToolkit
{
	namespace util
	{
		class API_TYPE Filesystem
		{
		public:
			/**
			 *
			 * 是否存在
			 *
			 * @param path 路径
			 *
			 * @return 是否存在
			 *
			 */
			static bool Exists(const std::string & path);

			/**
			 *
			 * 是否为目录
			 *
			 * @param path 路径
			 *
			 * @return 是否为目录
			 *
			 */
			static bool IsDirectory(const std::string & path);

			/**
			 *
			 * 删除路径
			 *
			 * @param path 路径
			 *
			 * @return 是否删除成功
			 *
			 */
			static bool Remove(const std::string & path);

			/**
			 *
			 * 更改名称
			 *
			 * @param src 待更改路径
			 * @param dst 被更改路径
			 *
			 * @return 是否更改成功
			 *
			 */
			static bool Rename(const std::string & src, const std::string & dst);

			/**
			 *
			 * 读取文件
			 *
			 * @param path 路径
			 * @param result 结果
			 * @param keepEmpty 是否保留空行
			 *
			 * @return 是否读取成功
			 *
			 */
			static bool ReadFile(const std::string & path, std::vector<std::string> & result, bool keepEmpty = false);

			/**
			 *
			 * 读取文件
			 *
			 * @param path 路径
			 * @param keepEmpty 是否保留空行
			 *
			 * @return 内容集合
			 *
			 */
			static std::vector<std::string> ReadFile(const std::string & path, bool keepEmpty = false);

			/**
			 *
			 * 写入文件
			 *
			 * @param path 路径
			 * @param content 内容
			 *
			 * @return 是否写入成功
			 *
			 */
			static bool WriteFile(const std::string & path, const std::string & content);

			/**
			 *
			 * 创建文件
			 *
			 * @param path 路径
			 *
			 * @return 是否创建成功
			 *
			 */
			static bool CreateFile(const std::string & path);

			/**
			 *
			 * 遍历文件
			 *
			 * @param path 路径
			 * @param result 结果
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 是否遍历成功
			 *
			 */
			static bool TraverseFile(const std::string & path, std::vector<std::string> & result, bool subdirectory = false);

			/**
			 *
			 * 遍历文件
			 *
			 * @param path 路径
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 文件集合
			 *
			 */
			static std::vector<std::string> TraverseFile(const std::string & path, bool subdirectory = false);

			/**
			 *
			 * 遍历文件
			 *
			 * @param path 路径
			 * @param result 结果
			 * @param rule 规则
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 是否遍历成功
			 *
			 */
			static bool TraverseFile(const std::string & path, std::vector<std::string> & result, const std::regex & rule, bool subdirectory = false);

			/**
			 *
			 * 遍历文件
			 *
			 * @param path 路径
			 * @param rule 规则
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 文件集合
			 *
			 */
			static std::vector<std::string> TraverseFile(const std::string & path, const std::regex & rule, bool subdirectory = false);

			/**
			 *
			 * 创建文件夹
			 *
			 * @param path 路径
			 *
			 * @return 是否创建成功
			 *
			 */
			static bool CreateDirectory(const std::string & path);

			/**
			 *
			 * 创建多级文件夹
			 *
			 * @param path 路径
			 *
			 * @return 是否创建成功
			 *
			 */
			static bool CreateDirectories(const std::string & path);

			/**
			 *
			 * 遍历目录
			 *
			 * @param path 路径
			 * @param result 结果
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 是否遍历成功
			 *
			 */
			static bool TraverseDirectory(const std::string & path, std::vector<std::string> & result, bool subdirectory = false);

			/**
			 *
			 * 遍历目录
			 *
			 * @param path 路径
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 目录集合
			 *
			 */
			static std::vector<std::string> TraverseDirectory(const std::string & path,  bool subdirectory = false);

			/**
			 *
			 * 遍历目录
			 *
			 * @param path 路径
			 * @param result 结果
			 * @param rule 规则
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 是否遍历成功
			 *
			 */
			static bool TraverseDirectory(const std::string & path, std::vector<std::string> & result, const std::regex & rule, bool subdirectory = false);

			/**
			 *
			 * 遍历目录
			 *
			 * @param path 路径
			 * @param rule 规则
			 * @param subdirectory 是否遍历子目录
			 *
			 * @return 目录集合
			 *
			 */
			static std::vector<std::string> TraverseDirectory(const std::string & path, const std::regex & rule, bool subdirectory = false);

			/**
			 *
			 * 上次访问时间
			 *
			 * @param path 路径
			 *
			 * @return 上次访问时间
			 *
			 */
			static int64_t LastTime(const std::string &path);

			/**
			 *
			 * 文件大小
			 *
			 * @param path 路径
			 *
			 * @return 文件大小
			 *
			 */
			static std::size_t Size(const std::string & path);

			/**
			 *
			 * 当前路径
			 *
			 * @return 当前路径
			 *
			 */
			static std::string CurrentDirectory();

			/**
			 *
			 * 父级路径
			 *
			 * @param path 路径
			 *
			 * @return 父级路径
			 *
			 */
			static std::string ParentDirectory(const std::string & path);

			/**
			 *
			 * 文件名称
			 *
			 * @param path 路径
			 *
			 * @return 文件名称
			 *
			 */
			static std::string Name(const std::string & path);

			/**
			 *
			 * 文件前缀
			 *
			 * @param path 路径
			 *
			 * @return 文件前缀
			 *
			 */
			static std::string Steam(const std::string & path);

			/**
			 *
			 * 文件扩展名
			 *
			 * @param path 路径
			 *
			 * @return 文件扩展名
			 *
			 */
			static std::string Extension(const std::string & path);

			/**
			 *
			 * 文件内容
			 *
			 * @param path 路径
			 *
			 * @return 文件内容
			 *
			 */
			static std::string Content(const std::string & path);

			/**
			 *
			 * 绝对路径
			 *
			 * @param path 路径
			 *
			 * @return 绝对路径
			 *
			 */
			static std::string Canonical(const std::string & path);
		};
	}
}


#endif // __UTIL__FILESYSTEM__H__
