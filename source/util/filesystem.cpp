/**
 *
 *  作者: hm
 *
 *  说明: 文件处理
 *
 */


#include "filesystem.h"

#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <io.h>
#  include <direct.h>
#
#else
#
#  include <unistd.h>
#  include <dirent.h>
#
#  include <sys/stat.h>
#
#endif

#include <cstring>
#include <fstream>
#include <functional>


namespace util
{
	/**
	 *
	 * 是否存在
	 *
	 * @param path 路径
	 *
	 * @return 是否存在
	 *
	 */
	bool Filesystem::Exists(const std::string & path)
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		return ::_access(path.c_str(), S_OK) == 0;

	#else

		return ::access(path.c_str(), F_OK) == 0;

	#endif
	}

	/**
	 *
	 * 是否为目录
	 *
	 * @param path 路径
	 *
	 * @return 是否为目录
	 *
	 */
	bool Filesystem::IsDirectory(const std::string & path)
	{
		if (!Exists(path))
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		return ::GetFileAttributesA(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY;

	#else

		struct stat status{ };

		if (::stat(path.c_str(), &status) == -1)
		{
			return false;
		}

		return S_ISDIR(status.st_mode);

	#endif
	}

	/**
	 *
	 * 删除路径
	 *
	 * @param path 路径
	 *
	 * @return 是否删除成功
	 *
	 */
	bool Filesystem::Remove(const std::string & path)
	{
		if (!Exists(path))
		{
			return true;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		if (!IsDirectory(path))
		{
			return ::DeleteFile(path.c_str()) == TRUE;
		}

		std::string dir{ };

		if (path[path.size() - 1] == PATH_SEP[0])
		{
			dir.append(path);
			dir.append("*.*");
		}
		else
		{
			dir.append(path);
			dir.append(PATH_SEP);
			dir.append("*.*");
		}

		WIN32_FIND_DATA finder{ };

		std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hFind
		(
			::FindFirstFile(dir.c_str(), &finder),

			[](HANDLE handle)
			{
				if (handle && handle != INVALID_HANDLE_VALUE)
				{
					::FindClose(handle);
				}
			}
		);

		if (hFind == nullptr || hFind.get() == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder.cFileName, ".") == 0 || ::strcmp(finder.cFileName, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				value.append(path);
				value.append(finder.cFileName);
			}
			else
			{
				value.append(path);
				value.append(PATH_SEP);
				value.append(finder.cFileName);
			}

			if (finder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (!Remove(value))
				{
					return false;
				}
			}
			else
			{
				if (::DeleteFile(value.c_str()) == FALSE)
				{
					return false;
				}
			}
		}
		while (::FindNextFile(hFind.get(), &finder));

		if (::RemoveDirectory(path.c_str()) == FALSE)
		{
			return false;
		}

	#else

		if (!IsDirectory(path))
		{
			return std::remove(path.c_str()) == 0;
		}

		std::unique_ptr<DIR, std::function<void(DIR *)>> dir
		(
			::opendir(path.c_str()),

			[](DIR * handle)
			{
				if (handle)
				{
					::closedir(handle);
				}
			}
		);

		if (dir == nullptr)
		{
			return false;
		}

		struct dirent * finder = ::readdir(dir.get());

		if (finder == nullptr)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder->d_name, ".") == 0 || ::strcmp(finder->d_name, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				value.append(path);
				value.append(finder->d_name);
			}
			else
			{
				value.append(path);
				value.append(PATH_SEP);
				value.append(finder->d_name);
			}

			if (IsDirectory(value))
			{
				if (!Remove(value))
				{
					return false;
				}
			}
			else
			{
				if (std::remove(value.c_str()) == -1)
				{
					return false;
				}
			}
		}
		while ((finder = ::readdir(dir.get())));

		if (::rmdir(path.c_str()) == -1)
		{
			return false;
		}

	#endif

		return true;
	}

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
	bool Filesystem::Rename(const std::string & src, const std::string & dst)
	{
		return std::rename(src.c_str(), dst.c_str()) == 0;
	}

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
	bool Filesystem::ReadFile(const std::string & path, std::vector<std::string> & result, bool keepEmpty)
	{
		if (!Exists(path))
		{
			return false;
		}

		std::ifstream ifs(path, std::ios::binary);

		if (!ifs.is_open())
		{
			return false;
		}

		std::string content{ };

		while (!ifs.eof())
		{
			std::getline(ifs, content);

			if (keepEmpty || !content.empty())
			{
				result.push_back(content);
			}
		}

		ifs.close();

		return true;
	}

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
	std::vector<std::string> Filesystem::ReadFile(const std::string & path, bool keepEmpty)
	{
		std::vector<std::string> result{ };

		ReadFile(path, result, keepEmpty);

		return result;
	}

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
	bool Filesystem::WriteFile(const std::string & path, const std::string & content)
	{
		std::ofstream ofs(path, std::ios::binary);

		if (!ofs.is_open())
		{
			return false;
		}

		ofs << content;

		ofs.close();

		return true;
	}

	/**
	 *
	 * 创建文件
	 *
	 * @param path 路径
	 *
	 * @return 是否创建成功
	 *
	 */
	bool Filesystem::CreateFile(const std::string & path)
	{
		std::ofstream ofs(path, std::ios::binary);

		if (!ofs.is_open())
		{
			return false;
		}

		ofs.close();

		return true;
	}

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
	bool Filesystem::TraverseFile(const std::string & path, std::vector<std::string> & result, bool subdirectory)
	{
		if (!Exists(path))
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::string dir{ };

		if (path[path.size() - 1] == PATH_SEP[0])
		{
			dir.append(path);
			dir.append("*.*");
		}
		else
		{
			dir.append(path);
			dir.append(PATH_SEP);
			dir.append("*.*");
		}

		WIN32_FIND_DATA finder{ };

		std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hFind
		(
			::FindFirstFile(dir.c_str(), &finder),

			[](HANDLE handle)
			{
				if (handle && handle != INVALID_HANDLE_VALUE)
				{
					::FindClose(handle);
				}
			}
		);

		if (hFind == nullptr || hFind.get() == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder.cFileName, ".") == 0 || ::strcmp(finder.cFileName, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder.cFileName);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder.cFileName);
			}

			if (finder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (subdirectory)
				{
					if (!TraverseFile(value, result, subdirectory))
					{
						return false;
					}
				}
			}
			else
			{
				result.push_back(value);
			}
		}
		while (::FindNextFile(hFind.get(), &finder));

	#else

		std::unique_ptr<DIR, std::function<void(DIR *)>> dir
		(
			::opendir(path.c_str()),

			[](DIR * handle)
			{
				if (handle)
				{
					::closedir(handle);
				}
			}
		);

		if (dir == nullptr)
		{
			return false;
		}

		struct dirent * finder = ::readdir(dir.get());

		if (finder == nullptr)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder->d_name, ".") == 0 || ::strcmp(finder->d_name, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder->d_name);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder->d_name);
			}

			if (IsDirectory(value))
			{
				if (subdirectory)
				{
					if (!TraverseFile(value, result, subdirectory))
					{
						return false;
					}
				}
			}
			else
			{
				result.push_back(value);
			}
		}
		while ((finder = ::readdir(dir.get())));

	#endif

		return true;
	}

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
	std::vector<std::string> Filesystem::TraverseFile(const std::string & path, bool subdirectory)
	{
		std::vector<std::string> result{ };

		TraverseFile(path, result, subdirectory);

		return result;
	}

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
	bool Filesystem::TraverseFile(const std::string & path, std::vector<std::string> & result, const std::regex & rule, bool subdirectory)
	{
		if (!Exists(path))
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::string dir{ };

		if (path[path.size() - 1] == PATH_SEP[0])
		{
			dir.append(path);
			dir.append("*.*");
		}
		else
		{
			dir.append(path);
			dir.append(PATH_SEP);
			dir.append("*.*");
		}

		WIN32_FIND_DATA finder{ };

		std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hFind
		(
			::FindFirstFile(dir.c_str(), &finder),

			[](HANDLE handle)
			{
				if (handle && handle != INVALID_HANDLE_VALUE)
				{
					::FindClose(handle);
				}
			}
		);

		if (hFind == nullptr || hFind.get() == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder.cFileName, ".") == 0 || ::strcmp(finder.cFileName, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder.cFileName);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder.cFileName);
			}

			if (finder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (subdirectory)
				{
					if (!TraverseFile(value, result, rule, subdirectory))
					{
						return false;
					}
				}
			}
			else
			{
				if (std::regex_match(value, rule))
				{
					result.push_back(value);
				}
			}
		}
		while (::FindNextFile(hFind.get(), &finder));

	#else

		std::unique_ptr<DIR, std::function<void(DIR *)>> dir
		(
			::opendir(path.c_str()),

			[](DIR * handle)
			{
				if (handle)
				{
					::closedir(handle);
				}
			}
		);

		if (dir == nullptr)
		{
			return false;
		}

		struct dirent * finder = ::readdir(dir.get());

		if (finder == nullptr)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder->d_name, ".") == 0 || ::strcmp(finder->d_name, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder->d_name);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder->d_name);
			}

			if (IsDirectory(value))
			{
				if (subdirectory)
				{
					if (!TraverseFile(value, result, rule, subdirectory))
					{
						return false;
					}
				}
			}
			else
			{
				if (std::regex_match(value, rule))
				{
					result.push_back(value);
				}
			}
		}
		while ((finder = ::readdir(dir.get())));

	#endif

		return true;
	}

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
	std::vector<std::string> Filesystem::TraverseFile(const std::string & path, const std::regex & rule, bool subdirectory)
	{
		std::vector<std::string> result{ };

		TraverseFile(path, result, rule, subdirectory);

		return result;
	}

	/**
	 *
	 * 创建文件夹
	 *
	 * @param path 路径
	 *
	 * @return 是否创建成功
	 *
	 */
	bool Filesystem::CreateDirectory(const std::string & path)
	{
	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		if (::_mkdir(path.c_str()) == -1)
		{
			return Exists(path);
		}

	#else

		if (::mkdir(path.c_str(), 0777) == -1)
		{
			return Exists(path);
		}

	#endif

		return true;
	}

	/**
	 *
	 * 创建多级文件夹
	 *
	 * @param path 路径
	 *
	 * @return 是否创建成功
	 *
	 */
	bool Filesystem::CreateDirectories(const std::string & path)
	{
		std::size_t length = path.length();

		for (std::size_t i = 0; i < length; ++i)
		{
			if (i == (length - 1))
			{
				if (!CreateDirectory(path))
				{
					return false;
				}
			}
			else if (path[i] == PATH_SEP[0])
			{
				if (i == 0)
				{
					continue;
				}

				if (!CreateDirectory(path.substr(0, i)))
				{
					return false;
				}
			}
		}

		return true;
	}

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
	bool Filesystem::TraverseDirectory(const std::string & path, std::vector<std::string> & result, bool subdirectory)
	{
		if (!Exists(path))
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::string dir{ };

		if (path[path.size() - 1] == PATH_SEP[0])
		{
			dir.append(path);
			dir.append("*.*");
		}
		else
		{
			dir.append(path);
			dir.append(PATH_SEP);
			dir.append("*.*");
		}

		WIN32_FIND_DATA finder{ };

		std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hFind
		(
			::FindFirstFile(dir.c_str(), &finder),

			[](HANDLE handle)
			{
				if (handle && handle != INVALID_HANDLE_VALUE)
				{
					::FindClose(handle);
				}
			}
		);

		if (hFind == nullptr || hFind.get() == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder.cFileName, ".") == 0 || ::strcmp(finder.cFileName, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder.cFileName);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder.cFileName);
			}

			if (finder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				result.push_back(value);

				if (subdirectory)
				{
					if (!TraverseDirectory(value, result, subdirectory))
					{
						return false;
					}
				}
			}
		}
		while (::FindNextFile(hFind.get(), &finder));

	#else

		std::unique_ptr<DIR, std::function<void(DIR *)>> dir
		(
			::opendir(path.c_str()),

			[](DIR * handle)
			{
				if (handle)
				{
					::closedir(handle);
				}
			}
		);

		if (dir == nullptr)
		{
			return false;
		}

		struct dirent * finder = ::readdir(dir.get());

		if (finder == nullptr)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder->d_name, ".") == 0 || ::strcmp(finder->d_name, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder->d_name);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder->d_name);
			}

			if (IsDirectory(value))
			{
				result.push_back(value);

				if (subdirectory)
				{
					if (!TraverseDirectory(value, result, subdirectory))
					{
						return false;
					}
				}
			}
		}
		while ((finder = ::readdir(dir.get())));

	#endif

		return true;
	}

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
	std::vector<std::string> Filesystem::TraverseDirectory(const std::string & path,  bool subdirectory)
	{
		std::vector<std::string> result{ };

		TraverseDirectory(path, result, subdirectory);

		return result;
	}

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
	bool Filesystem::TraverseDirectory(const std::string & path, std::vector<std::string> & result, const std::regex & rule, bool subdirectory)
	{
		if (!Exists(path))
		{
			return false;
		}

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::string dir{ };

		if (path[path.size() - 1] == PATH_SEP[0])
		{
			dir.append(path);
			dir.append("*.*");
		}
		else
		{
			dir.append(path);
			dir.append(PATH_SEP);
			dir.append("*.*");
		}

		WIN32_FIND_DATA finder{ };

		std::unique_ptr<typename std::remove_pointer<HANDLE>::type, std::function<void(HANDLE)>> hFind
		(
			::FindFirstFile(dir.c_str(), &finder),

			[](HANDLE handle)
			{
				if (handle && handle != INVALID_HANDLE_VALUE)
				{
					::FindClose(handle);
				}
			}
		);

		if (hFind == nullptr || hFind.get() == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder.cFileName, ".") == 0 || ::strcmp(finder.cFileName, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder.cFileName);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder.cFileName);
			}

			if (finder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (std::regex_match(value, rule))
				{
					result.push_back(value);
				}

				if (subdirectory)
				{
					if (!TraverseDirectory(value, result, rule, subdirectory))
					{
						return false;
					}
				}
			}
		}
		while (::FindNextFile(hFind.get(), &finder));

	#else

		std::unique_ptr<DIR, std::function<void(DIR *)>> dir
		(
			::opendir(path.c_str()),

			[](DIR * handle)
			{
				if (handle)
				{
					::closedir(handle);
				}
			}
		);

		if (dir == nullptr)
		{
			return false;
		}

		struct dirent * finder = ::readdir(dir.get());

		if (finder == nullptr)
		{
			return false;
		}

		do
		{
			if (::strcmp(finder->d_name, ".") == 0 || ::strcmp(finder->d_name, "..") == 0)
			{
				continue;
			}

			std::string value{ };

			if (path[path.size() - 1] == PATH_SEP[0])
			{
				if (path != ".")
				{
					value.append(path);
				}

				value.append(finder->d_name);
			}
			else
			{
				if (path != ".")
				{
					value.append(path);
					value.append(PATH_SEP);
				}

				value.append(finder->d_name);
			}

			if (IsDirectory(value))
			{
				if (std::regex_match(value, rule))
				{
					result.push_back(value);
				}

				if (subdirectory)
				{
					if (!TraverseDirectory(value, result, rule, subdirectory))
					{
						return false;
					}
				}
			}
		}
		while ((finder = ::readdir(dir.get())));

	#endif

		return true;
	}

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
	std::vector<std::string> Filesystem::TraverseDirectory(const std::string & path, const std::regex & rule, bool subdirectory)
	{
		std::vector<std::string> result{ };

		TraverseDirectory(path, result, rule, subdirectory);

		return result;
	}

	/**
	 *
	 * 上次访问时间
	 *
	 * @param path 路径
	 *
	 * @return 上次访问时间
	 *
	 */
	int64_t Filesystem::LastTime(const std::string & path)
	{
		if (!Exists(path))
		{
			return 0;
		}

		struct stat status
		{
		};

		if (::stat(path.c_str(), &status) == -1)
		{
			return 0;
		}

		return status.st_mtime;
	}

	/**
	 *
	 * 文件大小
	 *
	 * @param path 路径
	 *
	 * @return 文件大小
	 *
	 */
	std::size_t Filesystem::Size(const std::string & path)
	{
		if (!Exists(path))
		{
			return 0;
		}

		std::ifstream ifs(path, std::ifstream::ate | std::ifstream::binary);

		if (!ifs.is_open())
		{
			return 0;
		}

		std::size_t size = static_cast<std::size_t>(ifs.tellg());

		ifs.close();

		return size;
	}

	/**
	 *
	 * 当前路径
	 *
	 * @return 当前路径
	 *
	 */
	std::string Filesystem::CurrentDirectory()
	{
		char directory[PATH_MAX + 1]{ 0 };

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		if (::_getcwd(directory, PATH_MAX) == nullptr)
		{
			return { };
		}

	#else

		if (::getcwd(directory, PATH_MAX) == nullptr)
		{
			return { };
		}

	#endif

		return directory;
	}

	/**
	 *
	 * 父级路径
	 *
	 * @param path 路径
	 *
	 * @return 父级路径
	 *
	 */
	std::string Filesystem::ParentDirectory(const std::string & path)
	{
		if (!Exists(path))
		{
			return { };
		}

		std::size_t pos = path.rfind(PATH_SEP[0]);

		if (pos == std::string::npos)
		{
			return CurrentDirectory();
		}

		return Canonical(path);
	}

	/**
	 *
	 * 文件名称
	 *
	 * @param path 路径
	 *
	 * @return 文件名称
	 *
	 */
	std::string Filesystem::Name(const std::string & path)
	{
		std::size_t pos = path.rfind(PATH_SEP[0]);

		if (pos == std::string::npos)
		{
			return path;
		}

		return path.substr(pos + 1);
	}

	/**
	 *
	 * 文件前缀
	 *
	 * @param path 路径
	 *
	 * @return 文件前缀
	 *
	 */
	std::string Filesystem::Steam(const std::string & path)
	{
		std::size_t sepPos = path.rfind(PATH_SEP[0]);

		if (sepPos == std::string::npos)
		{
			std::size_t dotPos = path.rfind('.');

			if (dotPos == std::string::npos)
			{
				return path;
			}

			return path.substr(0, dotPos);
		}

		std::size_t dotPos = path.find('.', sepPos);

		if (dotPos == std::string::npos)
		{
			return path.substr(sepPos + 1);
		}

		return path.substr(sepPos + 1, dotPos - sepPos - 1);
	}

	/**
	 *
	 * 文件扩展名
	 *
	 * @param path 路径
	 *
	 * @return 文件扩展名
	 *
	 */
	std::string Filesystem::Extension(const std::string & path)
	{
		std::size_t sepPos = path.rfind(PATH_SEP[0]);

		if (sepPos == std::string::npos)
		{
			std::size_t dotPos = path.rfind('.');

			if (dotPos == std::string::npos)
			{
				return { };
			}

			return path.substr(dotPos);
		}

		std::size_t dotPos = path.find('.', sepPos);

		if (dotPos == std::string::npos)
		{
			return { };
		}

		return path.substr(dotPos);
	}

	/**
	 *
	 * 文件内容
	 *
	 * @param path 路径
	 *
	 * @return 文件内容
	 *
	 */
	std::string Filesystem::Content(const std::string & path)
	{
		if (!Exists(path))
		{
			return { };
		}

		std::ifstream ifs(path, std::ios::binary);

		if (!ifs.is_open())
		{
			return { };
		}

		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

		ifs.close();

		return content;
	}

	/**
	 *
	 * 绝对路径
	 *
	 * @param path 路径
	 *
	 * @return 绝对路径
	 *
	 */
	std::string Filesystem::Canonical(const std::string & path)
	{
		char directory[PATH_MAX + 1]{ 0 };

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		if (::_fullpath(directory, path.c_str(), PATH_MAX) == nullptr)
		{
			return { };
		}

	#else

		if (::realpath(path.c_str(), directory) == nullptr)
		{
			return { };
		}

	#endif

		return directory;
	}
}
