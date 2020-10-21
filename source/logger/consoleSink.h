#ifndef __LOGGER__CONSOLE_SINK__H__
#define __LOGGER__CONSOLE_SINK__H__


/**
 *
 *  作者: hm
 *
 *  说明: 控制台节点
 *
 */


#include "sink.h"


namespace tinyToolkit
{
	namespace logger
	{
		class API_TYPE ConsoleSink : public ISink
		{
		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param name 名称
			 * @param file 句柄
			 *
			 */
			explicit ConsoleSink(std::string name, FILE * file = stdout);

			/**
			 *
			 * 析构函数
			 *
			 */
			~ConsoleSink() override;

			/**
			 *
			 * 关闭
			 *
			 */
			void Close() override;

			/**
			 *
			 * 刷新
			 *
			 */
			void Flush() override;

			/**
			 *
			 * 写入
			 *
			 * @param context 上下文
			 *
			 */
			void Write(const Context & context) override;

		private:
			FILE * _file{ nullptr };
		};
	}
}


#endif // __LOGGER__CONSOLE_SINK__H__
