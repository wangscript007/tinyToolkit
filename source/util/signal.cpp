/**
 *
 *  作者: hm
 *
 *  说明: 信号处理
 *
 */


#include "signal.h"

#include <csignal>


namespace tinyToolkit
{
	namespace util
	{
		/**
		 *
		 * 注册信号动作
		 *
		 * @param signalNo 信号量
		 * @param callback 回调函数
		 *
		 */
		void Signal::RegisterAction(int32_t signalNo, void(* callback)(int32_t))
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			std::signal(signalNo, callback);

		#else

			struct sigaction action{ };

			action.sa_flags = SA_SIGINFO;
			action.sa_handler = callback;

			sigemptyset(&action.sa_mask);  /// 用来将参数信号集初始化并清空

			#ifdef SA_RESTART

			action.sa_flags |= SA_RESTART;

			#endif

			/**
			 *
			 * int sigaction(int signo, const struct sigaction * restrict, struct sigaction * restrict oact)
			 *
			 * signo 为信号编号
			 *
			 * restrict 为sigaction结构体
			 *
			 * oact 一般为nullptr
			 *
			 */
			::sigaction(signalNo, &action, nullptr);

		#endif
		}

		/**
		 *
		 * 注册忽略信号
		 *
		 */
		void Signal::RegisterIgnore()
		{
		#if PLATFORM_TYPE == PLATFORM_MIPS || PLATFORM_TYPE == PLATFORM_APPLE || PLATFORM_TYPE == PLATFORM_LINUX

			/**
			 *
			 * SIGHUP 终端关闭时.
			 * 		  系统对SIGHUP信号的默认处理是终止收到该信号的进程.
			 * 		  所以若程序中没有捕捉该信号, 当收到该信号时, 进程就会退出.
			 *
			 * SIGPIPE 产生信号时就不会中止程序, 直接把这个信号忽略掉
			 *
			 * SIGCHLD 产生信号时就不会僵尸进程, 直接把这个信号忽略掉
			 *
			 */
			RegisterAction(SIGHUP, SIG_IGN);
			RegisterAction(SIGPIPE, SIG_IGN);
			RegisterAction(SIGCHLD, SIG_IGN);

		#endif
		}

		/**
		 *
		 * 注册结束信号
		 *
		 * @param callback 回调函数
		 *
		 */
		void Signal::RegisterTerminate(void(* callback)(int32_t))
		{
		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			/**
			 *
			 * SIGINT    程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出, 用于通知前台进程组终止进程
			 *
			 * SIGTERM   程序结束(terminate)信号, 与SIGKILL不同的是该信号可以被阻塞和处理.
			 * 			 通常用来要求程序自己正常退出, shell命令kill缺省产生这个信号.
			 * 			 如果进程终止不了, 我们才会尝试SIGKILL
			 *
			 * SIGBREAK  停止进程的运行, 但该信号可以被处理和忽略.
			 * 			 用户键入SUSP字符时(通常是Ctrl-Break)发出这个信号
			 *
			 */
			RegisterAction(SIGINT,  callback);  /// 信号处理线程和程序的主线程不是是同一个线程, 优先级更高
			RegisterAction(SIGTERM, callback);
			RegisterAction(SIGBREAK, callback);  /// 信号处理线程和程序的主线程不是是同一个线程, 优先级更高

		#else

			/**
			 *
			 * SIGINT   程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出, 用于通知前台进程组终止进程
			 *
			 * SIGQUIT  和SIGINT类似, 但由QUIT字符(通常是Ctrl-\)来控制.
			 * 			进程在因收到SIGQUIT退出时会产生core文件, 在这个意义上类似于一个程序错误信号
			 *
			 * SIGTERM  程序结束(terminate)信号, 与SIGKILL不同的是该信号可以被阻塞和处理.
			 * 			通常用来要求程序自己正常退出, shell命令kill缺省产生这个信号.
			 * 			如果进程终止不了, 我们才会尝试SIGKILL
			 *
			 * SIGTSTP  停止进程的运行, 但该信号可以被处理和忽略.
			 * 			用户键入SUSP字符时(通常是Ctrl-Z)发出这个信号
			 *
			 */
			RegisterAction(SIGINT,  callback);
			RegisterAction(SIGQUIT, callback);
			RegisterAction(SIGTERM, callback);
			RegisterAction(SIGTSTP, callback);

		#endif
		}

		/**
		 *
		 * 注册异常信号
		 *
		 * @param callback 回调函数
		 *
		 */
		void Signal::RegisterException(void(* callback)(int32_t))
		{
			/**
			 *
			 * SIGILL  非法指令
			 *
			 * SIGFPE  浮点异常
			 *
			 * SIGABRT 调用abort函数生成的信号
			 *
			 * SIGSEGV 进程执行了一个无效的内存引用, 或发生段错误时发送给它的信号
			 *
			 */
			RegisterAction(SIGILL, callback);
			RegisterAction(SIGFPE, callback);
			RegisterAction(SIGABRT, callback);
			RegisterAction(SIGSEGV, callback);
		}

		/**
		 *
		 * 向自身发送信号
		 *
		 * @param signalNo 信号量
		 *
		 * @return 是否发送成功
		 *
		 */
		bool Signal::Raise(int32_t signalNo)
		{
			return std::raise(signalNo);
		}
	}
}
