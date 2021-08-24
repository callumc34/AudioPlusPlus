# CMakeList.txt : CMake project for AudioPlusPlus

cmake_minimum_required(VERSION 3.8)

project(
	"libaudio++"
	VERSION 0.0.1
	LANGUAGES CXX
	DESCRIPTION "Open source audio playback"
)

set(PACKAGE_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FeatureSummary)

include_directories("include")
add_subdirectory("src")

if(BUILD_EXAMPLES)
	#add_subdirectory("examples")
endif()

set_package_properties(sndfile PROPERTIES
	TYPE REQUIRED
	URL "https://www.github.com/libsndfile/libsndfile"
	DESCRIPTION "A C library for reading and writing sound files containing sampled audio data"
	PURPOSE "Audio decoding"
)

set_package_properties(portaudio PROPERTIES
	TYPE REQUIRED
	URL "https://github.com/portaudio/portaudio"
	DESCRIPTION "PortAudio is a cross-platform, open-source C language library for real-time audio input and output"
	PURPOSE "Audio Playback"
)

set_package_properties(spdlog PROPERTIES
	TYPE REQUIRED
	URL "https://github.com/gabime/spdlog"
	DESCRIPTION "Fast C++ logging library"
	PURPOSE "Logging"
)

include(FindLibCheck)

feature_summary(WHAT ALL)