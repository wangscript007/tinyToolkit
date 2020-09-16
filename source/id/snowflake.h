#ifndef __ID__SNOWFLAKE__H__
#define __ID__SNOWFLAKE__H__


/**
 *
 *  作者: hm
 *
 *  说明: 分布式唯一标识码
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"

#include <ctime>
#include <cstdint>


namespace id
{
	/**
	 *
	 * 无效位                    时间戳                       用户序号      设备序号         序列号
	 *   0 - 000 0000 0000 0000 0000 0000 0000 0000 0000 - 0000 0000 - 0000 0000 - 0000 0000 0000
	 *
	 */
	class API_TYPE Snowflake
	{
		static const int32_t USER_ID_BITS = 8;
		static const int32_t DEVICE_ID_BITS = 8;
		static const int32_t SEQUENCE_ID_BITS = 12;

		static const int32_t USER_ID_MAX = ~(-1 * (1 << USER_ID_BITS));
		static const int32_t DEVICE_ID_MAX = ~(-1 * (1 << DEVICE_ID_BITS));
		static const int32_t SEQUENCE_ID_MAX = ~(-1 * (1 << SEQUENCE_ID_BITS));

		static const int32_t USER_ID_SHIFT = SEQUENCE_ID_BITS + DEVICE_ID_BITS;
		static const int32_t DEVICE_ID_SHIFT = SEQUENCE_ID_BITS;
		static const int32_t TIMESTAMP_ID_SHIFT = SEQUENCE_ID_BITS + DEVICE_ID_BITS + USER_ID_BITS;

	public:
		/**
		 *
		 * 构造函数
		 *
		 * @param userID 用户序号
		 * @param deviceID 设备序号
		 *
		 */
		Snowflake(int32_t userID, int32_t deviceID);

		/**
		 *
		 * 生成
		 *
		 * @return 唯一标识码
		 *
		 */
		uint64_t Generate();

	private:
		int32_t _userID{ 0 };
		int32_t _deviceID{ 0 };
		int32_t _sequence{ 0 };

		int64_t _baseTimeStamp{ 0 };
		int64_t _lastTimeStamp{ 0 };
	};
}


#endif // __ID__SNOWFLAKE__H__
