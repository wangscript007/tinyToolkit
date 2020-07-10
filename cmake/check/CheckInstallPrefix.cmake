#
# 检测安装路径
#
IF(NOT CMAKE_INSTALL_PREFIX)

	IF(WIN32)

		SET(CMAKE_INSTALL_PREFIX "/usr")

	ELSE()

		SET(CMAKE_INSTALL_PREFIX "C:\\")

	ENDIF()

ENDIF()


#
# 设置安装路径
#
SET(BINARY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/bin)
SET(LIBRARY_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/lib64)
SET(INCLUDE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})


#
# 打印安装路径
#
MESSAGE(STATUS "Install ${CMAKE_PROJECT_NAME} binary  prefix : " ${BINARY_INSTALL_PREFIX})
MESSAGE(STATUS "Install ${CMAKE_PROJECT_NAME} library prefix : " ${LIBRARY_INSTALL_PREFIX})
MESSAGE(STATUS "Install ${CMAKE_PROJECT_NAME} include prefix : " ${INCLUDE_INSTALL_PREFIX})