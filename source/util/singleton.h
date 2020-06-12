#ifndef __UTIL__SINGLETON__H__
#define __UTIL__SINGLETON__H__


/**
 *
 *  作者: hm
 *
 *  说明: 单例处理
 *
 */


#include "../common/macro.h"
#include "../common/symbol.h"


#if PLATFORM_TYPE == PLATFORM_WINDOWS
#
#  include <mutex>
#
#elif PLATFORM_TYPE == PLATFORM_APPLE
#
#  include <mutex>
#
#elif PLATFORM_TYPE == PLATFORM_LINUX
#
#  include <mutex>
#  include <memory>
#
#endif


namespace util
{
	template <typename TypeT>
	class API_TYPE Singleton
	{
	public:
		/**
		 *
		 * 获取单例
		 *
		 * @param args 参数
		 *
		 * @return 单例对象
		 *
		 */
		template <typename ... Args>
		static TypeT & Instance(Args &&... args)
		{
			std::call_once(_onceFlag, [&]()
			{
				_instance.reset(new TypeT(std::forward<Args>(args)...));
			});

			return *_instance;
		}

	private:
		/**
		 *
		 * 构造函数
		 *
		 */
		Singleton() = default;

		/**
		 *
		 * 析构函数
		 *
		 */
		~Singleton() = default;

	protected:
		static std::once_flag _onceFlag;

		static std::unique_ptr<TypeT> _instance;
	};

	template <typename TypeT>
	std::once_flag Singleton<TypeT>::_onceFlag;

	template <typename TypeT>
	std::unique_ptr<TypeT> Singleton<TypeT>::_instance;
}


#endif // __UTIL__SINGLETON__H__
