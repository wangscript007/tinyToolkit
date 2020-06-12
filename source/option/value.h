#ifndef __OPTION__VALUE__H__
#define __OPTION__VALUE__H__


/**
 *
 *  作者: hm
 *
 *  说明: 内容
 *
 */


#include "any.h"
#include "traits.h"


namespace option
{
	class API_TYPE SemanticValue
	{
	public:
		/**
		 *
		 * 析构函数
		 *
		 */
		virtual ~SemanticValue() = default;

		/**
		 *
		 * 是否有数据
		 *
		 * @return 是否有数据
		 *
		 */
		virtual bool HasValue() = 0;

		/**
		 *
		 * 是否有默认值
		 *
		 * @return 是否有默认值
		 *
		 */
		virtual bool HasDefault() = 0;

		/**
		 *
		 * 类型
		 *
		 * @return 类型
		 *
		 */
		virtual OPTION_TYPE Type() = 0;

		/**
		 *
		 * 内容
		 *
		 * @return 内容
		 *
		 */
		virtual std::string Content() = 0;
	};

	template<class ValueTypeT>
	class API_TYPE RealValue : public SemanticValue
	{
		public:
		/**
		 *
		 * 构造函数
		 *
		 */
		RealValue() : _type(Traits<ValueTypeT>::type)
		{

		}

		/**
		 *
		 * 移动构造函数
		 *
		 * @param rhs 右值对象
		 *
		 */
		RealValue(RealValue && rhs) noexcept : _value(std::move(rhs._value)),
		                                       _default(std::move(rhs._default)),
		                                       _type(rhs._type)
		{

		}

		/**
		 *
		 * 拷贝构造函数
		 *
		 * @param lhs 左值对象
		 *
		 */
		RealValue(const RealValue & lhs) : _value(lhs._value),
		                                   _default(lhs._default),
		                                   _type(lhs._type)
		{

		}

		/**
		 *
		 * 构造函数
		 *
		 * @param value 默认数据
		 *
		 */
		explicit RealValue(ValueTypeT && value) : _value(std::forward<ValueTypeT>(value)),
		                                          _default(std::forward<ValueTypeT>(value)),
		                                          _type(Traits<ValueTypeT>::type)
		{

		}

		/**
		 *
		 * 析构函数
		 *
		 */
		~RealValue() override = default;

		/**
		 *
		 * 是否有数据
		 *
		 * @return 是否有数据
		 *
		 */
		bool HasValue() override
		{
			return _value.IsValid();
		}

		/**
		 *
		 * 是否有默认值
		 *
		 * @return 是否有默认值
		 *
		 */
		bool HasDefault() override
		{
			return _default.IsValid();
		}

		/**
		 *
		 * 类型
		 *
		 * @return 类型
		 *
		 */
		OPTION_TYPE Type() override
		{
			return _type;
		}

		/**
		 *
		 * 内容
		 *
		 * @return 内容
		 *
		 */
		std::string Content() override
		{
			return ToString<ValueTypeT>(_default.Get<ValueTypeT>());
		}

	private:
		/**
		 *
		 * 转换字符串
		 *
		 * @param content 内容
		 *
		 * @return 转换后内容
		 *
		 */
		template<typename ContentTypeT>
		typename std::enable_if
		<
			std::is_same<ContentTypeT, bool>::value, std::string
		>::type
		ToString(ContentTypeT content)
		{
			return content ? "true" : "false";
		}

		/**
		 *
		 * 转换字符串
		 *
		 * @param content 内容
		 *
		 * @return 转换后内容
		 *
		 */
		template<typename ContentTypeT>
		typename std::enable_if
		<
			std::is_same<ContentTypeT, float>::value ||
			std::is_same<ContentTypeT, double>::value ||
			std::is_same<ContentTypeT, long double>::value ||
			std::is_same<ContentTypeT, int8_t>::value ||
			std::is_same<ContentTypeT, uint8_t>::value ||
			std::is_same<ContentTypeT, int16_t>::value ||
			std::is_same<ContentTypeT, uint16_t>::value ||
			std::is_same<ContentTypeT, int32_t>::value ||
			std::is_same<ContentTypeT, uint32_t>::value ||
			std::is_same<ContentTypeT, int64_t>::value ||
			std::is_same<ContentTypeT, uint64_t>::value,
			std::string
		>::type
		ToString(ContentTypeT content)
		{
			return std::to_string(content);
		}

		/**
		 *
		 * 转换字符串
		 *
		 * @param content 内容
		 *
		 * @return 转换后内容
		 *
		 */
		template<typename ContentTypeT>
		typename std::enable_if
		<
			std::is_same<ContentTypeT, std::string>::value, std::string
		>::type
		ToString(ContentTypeT content)
		{
			return content;
		}

	public:
		Any _value{ };
		Any _default{ };

		OPTION_TYPE _type{ OPTION_TYPE::UNKNOWN };
	};

	template<typename ValueTypeT>
	std::shared_ptr<RealValue<ValueTypeT>> Value()
	{
		return std::make_shared<RealValue<ValueTypeT>>();
	}

	template<typename ValueTypeT>
	std::shared_ptr<RealValue<ValueTypeT>> Value(ValueTypeT && value)
	{
	return std::make_shared<RealValue<ValueTypeT>>(std::forward<ValueTypeT>(value));
	}
}


#endif // __OPTION__VALUE__H__
