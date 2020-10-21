#ifndef __LOGGER__LAYOUT__H__
#define __LOGGER__LAYOUT__H__


/**
 *
 *  作者: hm
 *
 *  说明: 布局
 *
 */


#include "context.h"


namespace tinyToolkit
{
	namespace logger
	{
		class API_TYPE ILayout
		{
		public:
			/**
			 *
			 * 析构函数
			 *
			 */
			virtual ~ILayout() = default;

			/**
			 *
			 * 格式化
			 *
			 * @param context 上下文
			 *
			 * @return 格式化后内容
			 *
			 */
			virtual std::string Format(const Context & context) = 0;
		};
	}
}


#endif // __LOGGER__LAYOUT__H__
