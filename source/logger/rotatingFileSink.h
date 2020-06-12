#ifndef __LOGGER__ROTATING_FILE_SINK__H__
#define __LOGGER__ROTATING_FILE_SINK__H__


/**
 *
 *  作者: hm
 *
 *  说明: 旋转文件节点
 *
 */


#include "file.h"
#include "sink.h"


namespace logger
{
	class API_TYPE RotatingFileSink : public ISink
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 * @param path 路径
		 * @param maxSize 大小
		 * @param maxCount 个数
		 *
		 */
		RotatingFileSink(std::string name, std::string path, std::size_t maxSize, std::size_t maxCount);

		/**
		 *
		 * 析构函数
		 *
		 */
		~RotatingFileSink() override;

		/**
		 *
		 * 关闭节点
		 *
		 */
		void Close() override;

		/**
		 *
		 * 刷新节点
		 *
		 */
		void Flush() override;

		/**
		 *
		 * 写入内容
		 *
		 * @param context 上下文
		 *
		 */
		void Write(const Context & context) override;

	protected:
		/**
		 *
		 * 旋转
		 *
		 */
		void Rotating();

		/**
		 *
		 * 格式化路径
		 *
		 * @param index 索引
		 *
		 * @return 路径
		 *
		 */
		std::string FormatPath(std::size_t index);

	protected:
		File _file{ };

		std::size_t _maxSize{ 0 };
		std::size_t _maxCount{ 0 };

		std::string _path{ };
	};
}


#endif // __LOGGER__ROTATING_FILE_SINK__H__
