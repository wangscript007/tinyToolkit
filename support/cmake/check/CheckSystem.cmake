#
# 检测系统
#
IF(MINGW)

	MESSAGE(STATUS "Detected Mingw System")

ELSEIF(WIN32)

	MESSAGE(STATUS "Detected Windows System")

ELSEIF(APPLE)

	MESSAGE(STATUS "Detected Apple System")

ELSEIF(ANDROID)

	MESSAGE(STATUS "Detected Android System")

ELSEIF(UNIX)

	MESSAGE(STATUS "Detected Unix System")

ENDIF()