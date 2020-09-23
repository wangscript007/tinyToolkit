#
# 平台判断
#
IF(NOT MINGW AND NOT WIN32 AND NOT ANDROID)

	#
	# 显示信息
	#
	MESSAGE(STATUS "Found fmtlib library")

	#
	# 判断路径
	#
	IF(WITH_FMT)

		#
		# 查找文件
		#
		FIND_FILE(HAVE_FMT format.h ${WITH_FMT}/include/fmt NO_DEFAULT_PATH)

	ELSE()

		#
		# 查找文件
		#
		FIND_FILE(HAVE_FMT format.h)

	ENDIF()

	#
	# 判断结果
	#
	IF(NOT HAVE_FMT)

		#
		# 显示信息
		#
		MESSAGE(FATAL_ERROR "Cannot find fmtlib library\r\nUse -DWITH_FMT specifies the library file directory\r\n")

	ENDIF()

ENDIF()
