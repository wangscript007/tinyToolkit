#ifndef __OPTION__DESCRIPTION__H__
#define __OPTION__DESCRIPTION__H__


/**
 *
 *  作者: hm
 *
 *  说明: 描述
 *
 */


#include "value.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <vector>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <vector>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <vector>
#
#endif


namespace option
{
	class API_TYPE DescriptionInfo
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 * @param info 信息
		 *
		 */
		DescriptionInfo(const char * name, const char * info);

		/**
		 *
		 * 构造函数
		 *
		 * @param name 名称
		 * @param mode 方式
		 * @param info 信息
		 * @param value 数据
		 *
		 */
		DescriptionInfo(const char * name, const char * mode, const char * info, std::shared_ptr<SemanticValue> value);

		/**
		 *
		 * 更新
		 *
		 */
		void Update();

		/**
		 *
		 * 更新
		 *
		 * @param content 内容
		 *
		 */
		void Update(const std::string & content);

		/**
		 *
		 * 是否有效
		 *
		 * @return 是否有效
		 *
		 */
		bool IsValid();

		/**
		 *
		 * 是否需要数据
		 *
		 * @return 是否需要数据
		 *
		 */
		bool IsRequired();

		/**
		 *
		 * 信息
		 *
		 * @return 信息
		 *
		 */
		const std::string & Info() const;

		/**
		 *
		 * 方式
		 *
		 * @return 方式
		 *
		 */
		const std::string & Mode() const;

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		const std::string & LongName() const;

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		const std::string & ShortName() const;

		/**
		 *
		 * 名称
		 *
		 * @return 名称
		 *
		 */
		const std::string & OptionName() const;

		/**
		 *
		 * 数据
		 *
		 * @return 数据
		 *
		 */
		const std::shared_ptr<SemanticValue> & Value() const;

	private:
		/**
		 *
		 * 设置名称
		 *
		 * @param name 名称
		 *
		 */
		void SetName(const char * name);

	private:
		bool _isValid{ false };

		std::string _info{ };
		std::string _mode{ };
		std::string _longName{ };
		std::string _shortName{ };
		std::string _optionName{ };

		std::shared_ptr<SemanticValue> _value{ };
	};

	class API_TYPE DescriptionGroup
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param caption 标题
		 *
		 */
		explicit DescriptionGroup(const char * caption);

		/**
		 *
		 * 添加选项
		 *
		 * @return 对象
		 *
		 */
		DescriptionGroup & AddOption();

		/**
		 *
		 * 标题
		 *
		 * @return 标题
		 *
		 */
		const std::string & Caption() const;

		/**
		 *
		 * 选项组
		 *
		 * @return 选项组
		 *
		 */
		const std::vector<std::shared_ptr<DescriptionInfo>> & Options() const;

		/**
		 *
		 * 重载()操作
		 *
		 * @param name 名称
		 * @param info 信息
		 *
		 * @return 对象
		 *
		 */
		DescriptionGroup & operator()(const char * name, const char * info);

		/**
		 *
		 * 重载()操作
		 *
		 * @param name 名称
		 * @param mode 方式
		 * @param info 信息
		 * @param value 数据
		 *
		 * @return 对象
		 *
		 */
		DescriptionGroup & operator()(const char * name, const char * mode, const char * info, const std::shared_ptr<SemanticValue> & value);

	private:
		std::string _caption{ };

		std::vector<std::shared_ptr<DescriptionInfo>> _options{ };
	};
}


#endif // __OPTION__DESCRIPTION__H__
