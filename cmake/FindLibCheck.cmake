include(CheckLibraryExists)

if(VCPKG_TOOLCHAIN AND (NOT CMAKE_VERSION VERSION_LESS 3.15))
	set (CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
endif ()

#Set root values
set(OGG_ROOT "${DEPENDENCIES_ROOT}/Ogg")
set(FLAC_ROOT "${DEPENDENCIES_ROOT}/FLAC")
set(OPUS_ROOT "${DEPENDENCIES_ROOT}/Opus")
set(Vorbis_ROOT "${DEPENDENCIES_ROOT}/Vorbis")
set(MPG123_ROOT "${DEPENDENCIES_ROOT}/Mpg123")
set(LAME_ROOT "${DEPENDENCIES_ROOT}/lame")
set(SNDFILE_ROOT "${DEPENDENCIES_ROOT}/libsndfile")
set(PORTAUDIO_ROOT "${DEPENDENCIES_ROOT}/portaudio")
set(SPDLOG_ROOT "${DEPENDENCIES_ROOT}/spdlog")

if(CMAKE_FIND_PACKAGE_PREFER_CONFIG)
	find_package(portaudio 19.7.0 CONFIG)
	if(BUILD_WITH_LOGGING)
		find_package(spdlog CONFIG)
	endif()
	#Sndfile dependencies
	find_package(sndfile 1.1.0 CONFIG)
	find_package(Lame CONFIG)
	find_package(Mpg123 1.25.10 CONFIG)

	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(sndfile CONFIG_MODE)
	find_package_handle_standard_args(portaudio CONFIG_MODE)
	find_package_handle_standard_args(spdlog CONFIG_MODE)
else()
	find_package(portaudio 19.8.0)
	if(BUILD_WITH_LOGGING)
		find_package(spdlog)
	endif()
	#If sndfile not found with config all dependencies must be found
	find_package(sndfile 1.1.0)
	find_package(Ogg 1.3)
	find_package(FLAC COMPONENTS Enc)
	find_package(Opus)
	find_package(Vorbis)
	find_package(Lame)
	find_package(Mpg123 1.25.10)
endif()

if (DEFINED ENABLE_STATIC_RUNTIME)
	if (MSVC)
		if (ENABLE_STATIC_RUNTIME)
			foreach (flag_var
				CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
				CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
				CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
				)
				if (${flag_var} MATCHES "/MD")
					string (REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
				endif ()
			endforeach (flag_var)
		else ()
			foreach (flag_var
				CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
				CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
				CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
				)
				if (${flag_var} MATCHES "/MT")
					string (REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
				endif (${flag_var} MATCHES "/MT")
			endforeach (flag_var)
		endif ( )
	elseif (MINGW)
		if (ENABLE_STATIC_RUNTIME)
			if (CMAKE_C_COMPILER_ID STREQUAL GNU)
				set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
				set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
			endif ()
			if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
				set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
				set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
			endif ()
			if (CMAKE_C_COMPILER_ID STREQUAL Clang)
				set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
				set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static")
			endif ()
			if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
				set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
				set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static")
			endif ()
		endif ()
	else ()
		message (AUTHOR_WARNING "ENABLE_STATIC_RUNTIME option is for MSVC or MinGW only.")
	endif ()
endif ()