#ifndef __NET__EVENT_POLL__H__
#define __NET__EVENT_POLL__H__


/**
 *
 *  作者: hm
 *
 *  说明: 事件轮询器
 *
 */


#include "channel.h"


namespace net
{
	class API_TYPE EventPoll
	{
	public:
		/**
		 *
		 * 构造函数
		 *
		 */
		EventPoll();

		/**
		 *
		 * 析构函数
		 *
		 */
		~EventPoll();

		/**
		 *
		 * 是否有效
		 *
		 * @return 是否有效
		 *
		 */
		bool IsValid() const;

		/**
		 *
		 * 执行事件
		 *
		 * @param timeout 超时时间
		 *
		 * @return 是否执行成功
		 *
		 */
		bool DoEvent(int32_t timeout = 3);

		/**
		 *
		 * 添加管道监控
		 *
		 * @param channel 通道
		 *
		 * @return 是否添加成功
		 *
		 */
		bool AppendChannel(Channel * channel) const;

		/**
		 *
		 * 更新管道监控
		 *
		 * @param channel 通道
		 *
		 * @return 是否更新成功
		 *
		 */
		bool UpdateChannel(Channel * channel) const;

		/**
		 *
		 * 移除管道监控
		 *
		 * @param channel 通道
		 *
		 * @return 是否移除成功
		 *
		 */
		bool RemoveChannel(Channel * channel) const;

	private:
		POLL_HANDLE_TYPE _handle{ POLL_HANDLE_INVALID };
	};
}


#endif // __NET__EVENT_POLL__H__
