#ifndef __NET__CHANNEL__H__
#define __NET__CHANNEL__H__


/**
 *
 *  作者: hm
 *
 *  说明: 通道
 *
 */


#include "context.h"

#include <functional>


namespace tinyToolkit
{
	namespace net
	{
		class API_TYPE EventLoop;

		class API_TYPE Channel
		{
			friend class API_TYPE EventPoll;

		public:
			/**
			 *
			 * 构造函数
			 *
			 * @param eventLoop 事件循环器
			 * @param handle 句柄
			 * @param option 操作
			 *
			 */
			Channel(EventLoop * eventLoop, SOCKET_HANDLE_TYPE handle, NET_OPTION_TYPE option = NET_OPTION_TYPE::IO);

			/**
			 *
			 * 设置读事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetReadCallback(std::function<void()> function);

			/**
			 *
			 * 设置写事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetWriteCallback(std::function<void()> function);

			/**
			 *
			 * 设置错误事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetErrorCallback(std::function<void()> function);

			/**
			 *
			 * 设置关闭事件回调函数
			 *
			 * @param function 函数
			 *
			 */
			void SetCloseCallback(std::function<void()> function);

			/**
			 *
			 * 移除
			 *
			 * @return 是否移除成功
			 *
			 */
			bool Remove();

			/**
			 *
			 * 是否正在监听读操作
			 *
			 * @return 是否正在监听读操作
			 *
			 */
			bool IsListenReading() const;

			/**
			 *
			 * 是否正在监听写操作
			 *
			 * @return 是否正在监听写操作
			 *
			 */
			bool IsListenWriting() const;

			/**
			 *
			 * 设置监听读操作状态
			 *
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			bool SetListenReadingStatus(bool on);

			/**
			 *
			 * 设置监听写操作状态
			 *
			 * @param on 状态
			 *
			 * @return 是否设置成功
			 *
			 */
			bool SetListenWritingStatus(bool on);

			/**
			 *
			 * 上下文
			 *
			 * @return 上下文
			 *
			 */
			Context * OwnerContext();

			/**
			 *
			 * 句柄
			 *
			 * @return 句柄
			 *
			 */
			SOCKET_HANDLE_TYPE Handle() const;

		protected:
			/**
			 *
			 * 执行事件
			 *
			 * @param netContext 网络上下文
			 * @param sysContext 系统上下文
			 *
			 */
			void DoEvent(Context * netContext, void * sysContext);

			/**
			 *
			 * 交互处理
			 *
			 * @param netContext 网络上下文
			 * @param sysContext 系统上下文
			 *
			 */
			void DoIO(Context * netContext, void * sysContext);

			/**
			 *
			 * 发送处理
			 *
			 * @param netContext 网络上下文
			 * @param sysContext 系统上下文
			 *
			 */
			void DoSend(Context * netContext, void * sysContext);

			/**
			 *
			 * 接收处理
			 *
			 * @param netContext 网络上下文
			 * @param sysContext 系统上下文
			 *
			 */
			void DoReceive(Context * netContext, void * sysContext);

		private:
			bool _isListenReading{ false };
			bool _isListenWriting{ false };

			Context _context{ };

			EventLoop * _eventLoop{ };

			std::function<void()> _readCallback{ };
			std::function<void()> _writeCallback{ };
			std::function<void()> _errorCallback{ };
			std::function<void()> _closeCallback{ };

			SOCKET_HANDLE_TYPE _handle{ SOCKET_HANDLE_INVALID };
		};
	}
}


#endif // __NET__CHANNEL__H__
