/**
 *
 *  作者: hm
 *
 *  说明: 分布式唯一标识码
 *
 */


#include "snowflake.h"

#include <chrono>
#include <string>
#include <stdexcept>


namespace id
{
	/**
	 *
	 * 下个时间戳
	 *
	 * @param lastTimestamp 上次时间截
	 *
	 * @return 当前时间戳
	 *
	 */
	int64_t NextMilliseconds(int64_t lastTimestamp)
	{
		/// 这里需要用稳定时间, 防止系统时间变化
		int64_t timeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		while (timeStamp <= lastTimestamp)
		{
			/// 这里需要用稳定时间, 防止系统时间变化
			timeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		}

		return timeStamp;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////


	const int32_t Snowflake::USER_ID_BITS;
	const int32_t Snowflake::DEVICE_ID_BITS;
	const int32_t Snowflake::SEQUENCE_ID_BITS;

	const int32_t Snowflake::USER_ID_MAX;
	const int32_t Snowflake::DEVICE_ID_MAX;
	const int32_t Snowflake::SEQUENCE_ID_MAX;

	const int32_t Snowflake::USER_ID_SHIFT;
	const int32_t Snowflake::DEVICE_ID_SHIFT;
	const int32_t Snowflake::TIMESTAMP_ID_SHIFT;


	/**
	 *
	 * 构造函数
	 *
	 * @param userID 用户序号
	 * @param deviceID 设备序号
	 *
	 */
	Snowflake::Snowflake(int32_t userID, int32_t deviceID) : _userID(userID),
	                                                         _deviceID(deviceID)
	{
		/// 这里需要用稳定时间, 防止系统时间变化
		_baseTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		_lastTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		if (_userID < 0 || _userID > USER_ID_MAX)
		{
			throw std::runtime_error("userID can't be greater than " + std::to_string(USER_ID_MAX) + " or less than 0");
		}

		if (_deviceID < 0 || _deviceID > DEVICE_ID_MAX)
		{
			throw std::runtime_error("deviceID can't be greater than " + std::to_string(DEVICE_ID_MAX) + " or less than 0");
		}
	}

	/**
	 *
	 * 生成
	 *
	 * @return 唯一标识码
	 *
	 */
	uint64_t Snowflake::Generate()
	{
		int64_t timeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		if (timeStamp < _lastTimeStamp)
		{
			throw std::runtime_error("Clock moved backwards, Refusing to generate id");
		}

		if (_lastTimeStamp == timeStamp)
		{
			_sequence = (_sequence + 1) & SEQUENCE_ID_MAX;

			if (_sequence == 0)  /// 毫秒内序列溢出
			{
				timeStamp = NextMilliseconds(_lastTimeStamp);
			}
		}
		else
		{
			_sequence = 0;
		}

		_lastTimeStamp = timeStamp;

		return static_cast<uint64_t>
		(
			((_lastTimeStamp - _baseTimeStamp) << TIMESTAMP_ID_SHIFT) |
			(_userID << USER_ID_SHIFT) |
			(_deviceID << DEVICE_ID_SHIFT) |
			_sequence
		);
	}
}
