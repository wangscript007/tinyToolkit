#
# 添加cmake自带的模块
#
INCLUDE(CheckCCompilerFlag)
INCLUDE(CheckCXXCompilerFlag)


#
# 检测C编译器支持的特性
#
CHECK_C_COMPILER_FLAG("-std=c89" C_COMPILER_SUPPORTS_C89)
CHECK_C_COMPILER_FLAG("-std=c99" C_COMPILER_SUPPORTS_C99)
CHECK_C_COMPILER_FLAG("-std=c11" C_COMPILER_SUPPORTS_C11)

IF(C_COMPILER_SUPPORTS_C11)

	TRAVERSE_SET(CMAKE_C_FLAGS "-std=c11")

ELSEIF(C_COMPILER_SUPPORTS_C99)

	TRAVERSE_SET(CMAKE_C_FLAGS "-std=c99")

ELSEIF(C_COMPILER_SUPPORTS_C89)

	TRAVERSE_SET(CMAKE_C_FLAGS "-std=c89")

ELSE()

	MESSAGE(STATUS "The C compiler ${CMAKE_C_COMPILER} does not support more than C89 features.")

ENDIF()


#
# 检测C++编译器支持的特性
#
CHECK_CXX_COMPILER_FLAG("-std=c++0x" CXX_COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=c++11" CXX_COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++14" CXX_COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++17" CXX_COMPILER_SUPPORTS_CXX17)

IF(CXX_COMPILER_SUPPORTS_CXX17)

	TRAVERSE_SET(CMAKE_CXX_FLAGS "-std=c++17")

ELSEIF(CXX_COMPILER_SUPPORTS_CXX14)

	TRAVERSE_SET(CMAKE_CXX_FLAGS "-std=c++14")

ELSEIF(CXX_COMPILER_SUPPORTS_CXX11)

	TRAVERSE_SET(CMAKE_CXX_FLAGS "-std=c++11")

ELSE()

	MESSAGE(STATUS "The CXX compiler ${CMAKE_CXX_COMPILER} does not support more than C++11 features.")

ENDIF()


#
# 设置C/C++编译选项
#
IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

	TRAVERSE_SET(CMAKE_CXX_FLAGS	-g								# 将编译时的调试信息保存到本地文件中
									-O2								# 优选代码空间
									-ldl							# 支持显示加载动态库
									-fPIC							# 告诉编译器产生与位置无关代码, 则产生的代码中, 没有绝对地址, 全部使用相对地址
									-latomic                        # 链接原子操作库
									-pthread						# 链接线程库
									-rdynamic						# 通知链接器将所有符号添加到动态符号表中
#									-fmem-report					# 显示所有的静态内存分配
#									-ftime-report					# 统计编译消耗的时间并显示报告
									-fsigned-char					# 将char类型设置成signed char
									-finline-functions				# 把所有简单的函数内联进调用者. 编译器会探索式地决定哪些函数足够简单, 值得做这种内联
									-Wall							# 会打开一些很有用的警告选项
#									-Werror							# 把警告当作错误
									-Wextra							# 打印一些额外的警告信息
									-Wshadow						# 当一个局部变量遮盖住了另一个局部变量, 或者全局变量, 给出警告
									-Woverflow						# 范围溢出, 给出警告
									-Wconversion					# 对一些可能改变值的隐式转换, 给出警告
									-Wcast-align					# 某个指针类型强制转换导致目标所需的地址对齐增加, 给出警告
									-Wfatal-errors					# 出现错误的时候停止编译
									-Wwrite-strings					# 把字符串常量赋值给non-const char *指针, 给出警告
									-Wpointer-arith					# 对函数指针或者void *类型的指针进行算术操作, 给出警告
									-Wold-style-cast				# 如果存在c风格类型转换，给出警告
									-Wredundant-decls				# 如果在同一个可见域内某定义多次声明, 给出警告
									-Wno-unused-result				# 如果存在未使用的返回值, 忽略警告
									-Wunreachable-code				# 如果编译器探测到永远不会执行到的代码, 给出警告
									-Wreturn-local-addr				# 如果返回临时引用, 给出警告
									-Woverloaded-virtual			# 如果函数的声明隐藏住了基类的虚函数, 给出警告
									-fno-omit-frame-pointer			# 产生stack frame
									-Wunused-but-set-variable		# 设置了但未使用的变量, 给出警告
									-Wsizeof-pointer-memaccess)		# 无法保证完整初始化类, 给出警告

	IF(${CMAKE_BUILD_TYPE} MATCHES Debug)

		IF(CXX_COMPILER_SUPPORTS_CXX11)

			TRAVERSE_SET(CMAKE_CXX_FLAGS	-static-libasan
											-fsanitize=address)

		ENDIF()

		IF(CXX_COMPILER_SUPPORTS_CXX17)

			TRAVERSE_SET(CMAKE_CXX_FLAGS	-static-libubsan
											-fsanitize=leak
											-fsanitize=vptr
											-fsanitize=null
											-fsanitize=shift
											-fsanitize=bounds
											-fsanitize=return
											-fsanitize=alignment
											-fsanitize=undefined
											-fsanitize=vla-bound
											-fsanitize=object-size
											-fsanitize=unreachable
											-fsanitize=bounds-strict
											-fsanitize=float-cast-overflow
											-fsanitize=float-divide-by-zero
											-fsanitize=integer-divide-by-zero
											-fsanitize=signed-integer-overflow)

		ENDIF()

	ENDIF()

ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

	TRAVERSE_SET(CMAKE_CXX_FLAGS	-g								# 将编译时的调试信息保存到本地文件中
									-O2								# 优选代码空间
									-fPIC							# 告诉编译器产生与位置无关代码, 则产生的代码中, 没有绝对地址, 全部使用相对地址
									-latomic                        # 链接原子操作库
									-pthread						# 链接线程库
#									-fmem-report					# 显示所有的静态内存分配
#									-ftime-report					# 统计编译消耗的时间并显示报告
									-fsigned-char					# 将char类型设置成signed char
									-finline-functions				# 把所有简单的函数内联进调用者. 编译器会探索式地决定哪些函数足够简单, 值得做这种内联
									-Wall							# 会打开一些很有用的警告选项
#									-Werror							# 把警告当作错误
									-Wextra							# 打印一些额外的警告信息
									-Wshadow						# 当一个局部变量遮盖住了另一个局部变量, 或者全局变量, 给出警告
									-Woverflow						# 范围溢出, 给出警告
									-Wconversion					# 对一些可能改变值的隐式转换, 给出警告
									-Wcast-align					# 某个指针类型强制转换导致目标所需的地址对齐增加, 给出警告
									-Wfatal-errors					# 出现错误的时候停止编译
									-Wwrite-strings					# 把字符串常量赋值给non-const char *指针, 给出警告
									-Wpointer-arith					# 对函数指针或者void *类型的指针进行算术操作, 给出警告
									-Wold-style-cast				# 如果存在c风格类型转换，给出警告
									-Wredundant-decls				# 如果在同一个可见域内某定义多次声明, 给出警告
									-Wunreachable-code				# 如果编译器探测到永远不会执行到的代码, 给出警告
									-Woverloaded-virtual			# 如果函数的声明隐藏住了基类的虚函数, 给出警告
									-Wreturn-stack-address			# 如果返回临时引用, 给出警告
									-fno-omit-frame-pointer			# 产生stack frame
									-Wunused-const-variable			# 设置了但未使用的const变量, 给出警告
									-Wsizeof-pointer-memaccess)		# 无法保证完整初始化类, 给出警告

	IF(${CMAKE_BUILD_TYPE} MATCHES Debug)

		TRAVERSE_SET(CMAKE_CXX_FLAGS	-fsanitize=address)

	ENDIF()

ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

	TRAVERSE_SET(CMAKE_CXX_FLAGS	/MP								# 启用多处理器编译
									/WX								# 将警告视为错误
									/MT
									/MTd
									/EHa							# 启用c++异常
									/sdl							# DSL检查
									/utf-8)							# utf-8支持

ENDIF()
