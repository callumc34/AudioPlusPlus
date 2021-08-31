# CMakeList.txt : CMake project for AudioPlusPlus
cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0074 NEW)

project(
	"AudioPlusPlus"
	VERSION 0.0.1
	LANGUAGES CXX
	DESCRIPTION "Open source audio playback"
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

#Includes
include(FeatureSummary)
include(GNUInstallDirs)
include(CMakeDependentOption)

#Options
if (MSVC AND (DEFINED ENABLE_STATIC_RUNTIME))
	option (ENABLE_STATIC_RUNTIME "Enable static runtime" ${ENABLE_STATIC_RUNTIME})
elseif (MINGW)
	option (ENABLE_STATIC_RUNTIME "Enable static runtime" OFF)
endif ()
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_PACKAGE_CONFIG "Generate and install package config file" ON)
option(INSTALL_PKGCONFIG_MODULE "Generate and isntall pkg-config module" ON)
option(BUILD_WITH_LOGGING "Build with SpdLog for extra debug logging" ON)

add_feature_info(ENABLE_STATIC_RUNTIME ENABLE_STATIC_RUNTIME "Enable static runtime")
add_feature_info(BUILD_EXAMPLES BUILD_EXAMPLES "Build examples")
add_feature_info(ENABLE_PACKAGE_CONFIG ENABLE_PACKAGE_CONFIG "Generate and install package config files")
add_feature_info(INSTALL_PKGCONFIG_MODULE INSTALL_PKGCONFIG_MODULE "Generate and install pkg-config module")
add_feature_info(BUILD_WITH_LOGGING BUILD_WITH_LOGGING "Build with SpdLog for extra debug logging")

#Dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set_package_properties(sndfile PROPERTIES
	TYPE REQUIRED
	URL "https://www.github.com/libsndfile/libsndfile"
	DESCRIPTION "A C library for reading and writing sound files containing sampled audio data"
	PURPOSE "Audio decoding"
)

set_package_properties(Ogg PROPERTIES
	TYPE RECOMMENDED
	URL "https://www.xiph.org/ogg/"
	DESCRIPTION "library for manipulating ogg bitstreams"
	PURPOSE "Required to enable Vorbis, Speex, and Opus support"
)

set_package_properties(Vorbis PROPERTIES
	TYPE RECOMMENDED
	URL "https://www.vorbis.com/"
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
	URL	"https://www.opus-codec.org/"
	DESCRIPTION "Standardized open source low-latency fullband codec"
	PURPOSE	"Enables experimental Opus support"
)

set_package_properties(Mpg123 PROPERTIES
	TYPE RECOMMENDED
	URL "https://www.mpg123.de/"
	DESCRIPTION "MPEG Audio Decoder"
	PURPOSE "MPEG Support for sndfile"
)

set_package_properties(Lame PROPERTIES
	TYPE RECOMMENDED
	URL "https://lame.sourceforge.io/index.php"
	DESCRIPTION "MPEG Audio Encoder"
	PURPOSE "MPEG Support for sndfile"
)

set_package_properties(portaudio PROPERTIES
	TYPE REQUIRED
	URL "https://github.com/portaudio/portaudio"
	DESCRIPTION "PortAudio is a cross-platform, open-source C language library for real-time audio input and output"
	PURPOSE "Audio Playback"
)

set_package_properties(spdlog PROPERTIES
	TYPE RECOMMENDED
	URL "https://github.com/gabime/spdlog"
	DESCRIPTION "Fast C++ logging library"
	PURPOSE "Logging"
)

set_package_properties(taglib PROPERTIES
	TYPE REQUIRED
	URL "https://taglib.org/"
	DESCRIPTION "Audio meta-data library"
	PURPOSE "ID3 Tag reading"
)

include(FindLibCheck)

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
	set(PUBLIC_LIBS "-lportaudio -ltaglib")
	if(BUILD_WITH_LOGGING)
		set(PRIVATE_LIBS "-lsndfile -lspdlog")
	else()
		set(PRIVATE_LIBS "-lsndfile")
	endif()
	
	configure_file(AudioPlusPlus.pc.in AudioPlusPlus.pc @ONLY)
endif()

if(BUILD_EXAMPLES)
	add_subdirectory("examples")
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
		PUBLIC_HEADER DESTINATION	${CMAKE_INSTALL_INCLUDEDIR})
endif()

if(INSTALL_PKGCONFIG_MODULE)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AudioPlusPlus.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()