/**
 *
 *  作者: hm
 *
 *  说明: 控制台节点
 *
 */


#include "consoleSink.h"


namespace tinyToolkit
{
	namespace logger
	{
		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 * @param file 句柄
		 *
		 */
		ConsoleSink::ConsoleSink(std::string name, FILE * file) : ISink(std::move(name)),
		                                                          _file(file)
		{

		}

		/**
		 *
		 * 析构函数
		 *
		 */
		ConsoleSink::~ConsoleSink()
		{
			if (_file)
			{
				fflush(_file);
			}
		}

		/**
		 *
		 * 关闭
		 *
		 */
		void ConsoleSink::Close()
		{
			Flush();
		}

		/**
		 *
		 * 刷新
		 *
		 */
		void ConsoleSink::Flush()
		{
			if (_file == nullptr)
			{
				return;
			}

			fflush(_file);
		}

		/**
		 *
		 * 写入
		 *
		 * @param context 上下文
		 *
		 */
		void ConsoleSink::Write(const Context & context)
		{
			if (_file == nullptr)
			{
				return;
			}

			if (Filter() && Filter()->Decide(context))
			{
				return;
			}

			if (Layout())
			{
				std::string content(Layout()->Format(context));

				::fwrite(content.c_str(), sizeof(char), content.size(), _file);
			}
			else
			{
				::fwrite(context.content.c_str(), sizeof(char), context.content.size(), _file);
			}

			if (IsAutoFlush())
			{
				Flush();
			}
		}
	}
}
