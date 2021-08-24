include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)
include(TestBigEndian)

if(VCPKG_TOOLCHAIN AND (NOT CMAKE_VERSION VERSION_LESS 3.15))
	set (CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
endif ()

if(CMAKE_FIND_PACKAGE_PREFER_CONFIG)
	find_package(sndfile CONFIG)
	find_package(portaudio CONFIG)
	find_package(spdlog CONFIG)

	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(sndfile CONFIG_MODE)
	find_package_handle_standard_args(portaudio CONFIG_MODE)
	find_package_handle_standard_args(spdlog CONFIG_MODE)
else()
	find_package(sndfile)
	find_package(portaudio)
	find_package(spdlog)
endif()

message(STATUS "INCLUDE - ${SNDFILE_INCLUDE_DIR}")
message(STATUS "INCLUDE - ${PORTAUDIO_INCLUDE_DIR}")
message(STATUS "INCLUDE - ${SPDLOG_INCLUDE_DIR}")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${SNDFILE_INCLUDE_DIR}
		${PORTAUDIO_INCLUDE_DIR}
		${SPDLOG_INCLUDE_DIR}
)