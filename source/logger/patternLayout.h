#ifndef __LOGGER__PATTERN_LAYOUT__H__
#define __LOGGER__PATTERN_LAYOUT__H__


/**
 *
 *  作者: hm
 *
 *  说明: 模式布局
 *
 */


#include "layout.h"


namespace logger
{
	class API_TYPE PatternLayout : public ILayout
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param pattern 模式
		 *
		 */
		explicit PatternLayout(std::string pattern);

		/**
		 *
		 * 格式化
		 *
		 * @param context 上下文
		 *
		 * @return 格式化后内容
		 *
		 */
		std::string Format(const Context & context) override;

	private:
		std::string _pattern{ };
	};
}


#endif // __LOGGER__PATTERN_LAYOUT__H__
