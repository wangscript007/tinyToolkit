/**
 *
 *  作者: hm
 *
 *  说明: 文件节点
 *
 */


#include "fileSink.h"


namespace logger
{
	/**
	 *
	 * 构造函数
	 *
	 * @param name 名称
	 * @param path 路径
	 * @param truncate 是否截断
	 *
	 */
	FileSink::FileSink(std::string name, std::string path, bool truncate) : ISink(std::move(name)),
	                                                                        _path(std::move(path))
	{
		if (!_file.Open(_path, truncate))
		{
			throw std::logic_error("Open log file failed : " + _file.Path());
		}
	}

	/**
	 *
	 * 析构函数
	 *
	 */
	FileSink::~FileSink()
	{
		_file.Close();
	}

	/**
	 *
	 * 关闭
	 *
	 */
	void FileSink::Close()
	{
		_file.Flush();
		_file.Close();
	}

	/**
	 *
	 * 刷新
	 *
	 */
	void FileSink::Flush()
	{
		_file.Flush();
	}

	/**
	 *
	 * 写入
	 *
	 * @param context 上下文
	 *
	 */
	void FileSink::Write(const Context & context)
	{
		if (Filter() && Filter()->Decide(context))
		{
			return;
		}

		_file.Write(Layout() ? Layout()->Format(context) : context.content);

		if (IsAutoFlush())
		{
			Flush();
		}
	}
}
