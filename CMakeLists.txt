# CMakeList.txt : CMake project for AudioPlusPlus
cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0074 NEW)

set(VCPKG_OVERLAY_PORTS "${CMAKE_SOURCE_DIR}/ports")

project(
	"AudioPlusPlus"
	VERSION 0.3.0
	LANGUAGES CXX
	DESCRIPTION "C++ open source audio playback & recording with file support."
	HOMEPAGE_URL https://github.com/callumc34/audioplusplus
)

#Package Settings
set(PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_FULL "${PROJECT_VERSION}${CPACK_PACKAGE_VERSION_STAGE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32 AND BUILD_SHARED_LIBS)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

#Dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#Includes
include(FeatureSummary)
include(GNUInstallDirs)
include(CMakeDependentOption)
include(FindLibCheck)

#Options
if (MSVC AND (DEFINED ENABLE_STATIC_RUNTIME))
	option (ENABLE_STATIC_RUNTIME "Enable static runtime" ${ENABLE_STATIC_RUNTIME})
elseif (MINGW)
	option (ENABLE_STATIC_RUNTIME "Enable static runtime" OFF)
endif ()
option(ENABLE_SNDFILE "Enable SndFile audio interaction" ${SNDFILE_FOUND})
option(BUILD_EXAMPLES "Build examples - requires SndFile" ${SNDFILE_FOUND})
option(ENABLE_PACKAGE_CONFIG "Generate and install package config file" ON)
option(INSTALL_PKGCONFIG_MODULE "Generate and install pkg-config module" ON)
option(BUILD_WITH_LOGGING "Build with SpdLog for extra debug logging" ${SPDLOG_FOUND})
option(BUILD_DOCUMENTATION "Build doxygen documentation - requires doxygen" ${DOXYGEN_FOUND})

add_feature_info(ENABLE_SNDFILE ENABLE_SNDFILE "Enable SndFile audio interaction")
add_feature_info(ENABLE_STATIC_RUNTIME ENABLE_STATIC_RUNTIME "Enable static runtime")
add_feature_info(BUILD_EXAMPLES BUILD_EXAMPLES "Build examples")
add_feature_info(ENABLE_PACKAGE_CONFIG ENABLE_PACKAGE_CONFIG "Generate and install package config files")
add_feature_info(INSTALL_PKGCONFIG_MODULE INSTALL_PKGCONFIG_MODULE "Generate and install pkg-config module")
add_feature_info(BUILD_WITH_LOGGING BUILD_WITH_LOGGING "Build with SpdLog for extra debug logging")
add_feature_info(BUILD_DOCUMENTATION BUILD_DOCUMENTATION "Build doxygen documentation - requires doxygen")

set_package_properties(PortAudio PROPERTIES
	TYPE REQUIRED
	URL "http://www.portaudio.com/"
	DESCRIPTION "PortAudio is a cross-platform, open-source C language library for real-time audio input and output"
	PURPOSE "Audio Playback"
)

set_package_properties(taglib PROPERTIES
	TYPE REQUIRED
	URL "https://taglib.org/"
	DESCRIPTION "Audio meta-data library"
	PURPOSE "ID3 Tag reading"
)

set_package_properties(sndfile PROPERTIES
	TYPE RECOMMENDED
	URL "http://libsndfile.github.io/libsndfile/"
	DESCRIPTION "A C library for reading and writing sound files containing sampled audio data"
	PURPOSE "Audio file IO"
)

set_package_properties(Ogg PROPERTIES
	TYPE RECOMMENDED
	URL "https://www.xiph.org/ogg/"
	DESCRIPTION "library for manipulating ogg bitstreams"
	PURPOSE "Required to enable Vorbis, Speex, and Opus support"
)

set_package_properties(Vorbis PROPERTIES
	TYPE RECOMMENDED
	URL "https://xiph.org/vorbis/"
	DESCRIPTION "open source lossy audio codec"
	PURPOSE "Enables Vorbis support"
)

set_package_properties(FLAC PROPERTIES
	TYPE RECOMMENDED
	URL "https://www.xiph.org/flac/"
	DESCRIPTION "Free Lossless Audio Codec Library"
	PURPOSE "Enables FLAC support"
)

set_package_properties(Opus PROPERTIES
	TYPE RECOMMENDED
	URL	"https://www.opus-codec.org"
	DESCRIPTION "Standardized open source low-latency fullband codec"
	PURPOSE	"Enables experimental Opus support"
)

set_package_properties(Mpg123 PROPERTIES
	TYPE RECOMMENDED
	URL "https://www.mpg123.org/"
	DESCRIPTION "MPEG Audio Decoder"
	PURPOSE "MPEG Support for sndfile"
)

set_package_properties(Lame PROPERTIES
	TYPE RECOMMENDED
	URL "https://lame.sourceforge.io/index.php"
	DESCRIPTION "MPEG Audio Encoder"
	PURPOSE "MPEG Support for sndfile"
)

set_package_properties(spdlog PROPERTIES
	TYPE RECOMMENDED
	URL "https://github.com/gabime/spdlog"
	DESCRIPTION "Fast C++ logging library"
	PURPOSE "Logging"
)

include_directories("include")
add_subdirectory("src")

feature_summary(WHAT ALL)

#Config files
if(BUILD_WITH_LOGGING)
	set(AudioPlusPlus_WITH_LOGGING ${BUILD_WITH_LOGGING})
	add_compile_definitions(ENABLE_LOGGING=True)
endif()

if(INSTALL_PKGCONFIG_MODULE)
	set(prefix ${CMAKE_INSTALL_PREFIX})
	set(exec_prefix "\$\{prefix\}")
	set(libdir "\$\{prefix\}/${CMAKE_INSTALL_LIBDIR}")
	set(includedir "\$\{prefix\}/${CMAKE_INSTALL_INCLUDEDIR}")
	set(VERSION ${PROJECT_VERSION})
	set(REQUIRES_PUBLIC "")
	set(REQUIRES_PRIVATE "taglib portaudio")
	set(PUBLIC_LIBS "")
	set(PRIVATE_LIBS "-lportaudio -ltaglib")
	if(ENABLE_SNDFILE)
		set(REQUIRES_PRIVATE "${REQUIRES_PRIVATE} sndfile flac ogg vorbis vorbisenc opus libmpg123")
		set(PRIVATE_LIBS "${PRIVATE_LIBS} -lsndfile")
	endif()
	if(BUILD_WITH_LOGGING)
		set(REQUIRES_PRIVATE "${REQUIRES_PRIVATE} spdlog")
		set(PRIVATE_LIBS "${PRIVATE_LIBS} -lspdlog")
	endif()
	
	configure_file(AudioPlusPlus.pc.in AudioPlusPlus.pc @ONLY)
endif()

if(BUILD_EXAMPLES)
	add_subdirectory("examples")
endif()

if(BUILD_DOCUMENTATION AND DOXYGEN_FOUND)
	set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/doxy.config.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc/doxy.config)
	
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

	add_custom_target(Doxygen-Documentation ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/
		COMMENT "Building doxygen documentation."
		VERBATIM
	)

	install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/html/"
		DESTINATION "${CMAKE_INSTALL_DOCDIR}"
	)
elseif(BUILD_DOCUMENTATION AND NOT DOXYGEN_FOUND)
	message(WARNING "Documentation was set on but doxygen was not found. Cannot build documentation.")
endif()

#Installation
if(ENABLE_PACKAGE_CONFIG)
	if(WIN32 AND (NOT MINGW) AND (NOT CYGWIN))
		set(CMAKE_INSTALL_PACKAGEDIR cmake) 
	 else()
	 	set(CMAKE_INSTALL_PACKAGEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/AudioPlusPlus)
	 endif()

	 install(TARGETS ${AUDIOPLUSPLUS_PROGRAM_TARGETS}
		RUNTIME DESTINATION			${CMAKE_INSTALL_BINDIR}
 	)

	install(TARGETS ${PROJECT_NAME}
		EXPORT AudioPlusPlusTargets
		RUNTIME DESTINATION			${CMAKE_INSTALL_BINDIR}
		ARCHIVE DESTINATION			${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION			${CMAKE_INSTALL_LIBDIR}
	)

	#Install include files keeping hierachy
	install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		FILES_MATCHING
		PATTERN "*.h"
	)

	include(CMakePackageConfigHelpers)

	if(ENABLE_EXTERNAL_LIBS)
		set(AudioPlusPlus_WITH_EXTERNAL_LIBS 1)
	else()
		set(AudioPlusPlus_WITH_EXTERNAL_LIBS 0)
	endif()
	
	set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})
	configure_package_config_file(cmake/AudioPlusPlusConfig.cmake.in AudioPlusPlusConfig.cmake
		INSTALL_DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
		PATH_VARS INCLUDE_INSTALL_DIR
	)
	write_basic_package_version_file(AudioPlusPlusConfigVersion.cmake COMPATIBILITY SameMajorVersion)

	install(EXPORT AudioPlusPlusTargets
		NAMESPACE AudioPlusPlus::
		DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
	)
	install(
		FILES
			${CMAKE_CURRENT_BINARY_DIR}/AudioPlusPlusConfig.cmake
			${CMAKE_CURRENT_BINARY_DIR}/AudioPlusPlusConfigVersion.cmake
		DESTINATION	${CMAKE_INSTALL_PACKAGEDIR}
	)
else()
	install(TARGETS ${PROJECT_NAME} ${audioplusplus_PROGRAMS}
		RUNTIME DESTINATION			${CMAKE_INSTALL_BINDIR}
		ARCHIVE DESTINATION			${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION			${CMAKE_INSTALL_LIBDIR}
	)

	#Install include files keeping hierachy
	install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		FILES_MATCHING
		PATTERN "*.h"
	)
endif()

if(INSTALL_PKGCONFIG_MODULE)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AudioPlusPlus.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()