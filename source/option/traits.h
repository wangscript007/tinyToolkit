#ifndef __OPTION__TRAITS__H__
#define __OPTION__TRAITS__H__


/**
 *
 *  作者: hm
 *
 *  说明: 萃取
 *
 */


#include "type.h"

#include <string>


namespace option
{
	template<typename TypeT>
	struct API_TYPE Traits
	{
		static const OPTION_TYPE type = OPTION_TYPE::UNKNOWN;
	};

	template<>
	struct API_TYPE Traits<bool>
	{
		static const OPTION_TYPE type = OPTION_TYPE::BOOL;
	};

	template<>
	struct API_TYPE Traits<float>
	{
		static const OPTION_TYPE type = OPTION_TYPE::FLOAT;
	};

	template<>
	struct API_TYPE Traits<double>
	{
		static const OPTION_TYPE type = OPTION_TYPE::DOUBLE;
	};

	template<>
	struct API_TYPE Traits<long double>
	{
		static const OPTION_TYPE type = OPTION_TYPE::LONG_DOUBLE;
	};

	template<>
	struct API_TYPE Traits<int8_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::INT8;
	};

	template<>
	struct API_TYPE Traits<uint8_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::UINT8;
	};

	template<>
	struct API_TYPE Traits<int16_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::INT16;
	};

	template<>
	struct API_TYPE Traits<uint16_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::UINT16;
	};

	template<>
	struct API_TYPE Traits<int32_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::INT32;
	};

	template<>
	struct API_TYPE Traits<uint32_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::UINT32;
	};

	template<>
	struct API_TYPE Traits<int64_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::INT64;
	};

	template<>
	struct API_TYPE Traits<uint64_t>
	{
		static const OPTION_TYPE type = OPTION_TYPE::UINT64;
	};

	template<>
	struct API_TYPE Traits<std::string>
	{
		static const OPTION_TYPE type = OPTION_TYPE::STRING;
	};
}


#endif // __OPTION__TRAITS__H__
