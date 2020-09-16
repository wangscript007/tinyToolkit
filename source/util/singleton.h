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

#include <mutex>
#include <memory>


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
			std::call_once(_onceFlag, [](Args &&... args_)
			{
				_instance = std::unique_ptr<TypeT>(new TypeT(std::forward<Args>(args_)...));
			},
			std::forward<Args>(args)...);

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

	private:
		static std::once_flag _onceFlag;

		static std::unique_ptr<TypeT> _instance;
	};

	template <typename TypeT>
	std::once_flag Singleton<TypeT>::_onceFlag;

	template <typename TypeT>
	std::unique_ptr<TypeT> Singleton<TypeT>::_instance = nullptr;
}


#endif // __UTIL__SINGLETON__H__
