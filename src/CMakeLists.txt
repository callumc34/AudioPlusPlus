add_library(${PROJECT_NAME}
	"Device/Device.cpp"
	"Device/DeviceManager.cpp"
	"File/File.cpp"
	"File/WriteFile.cpp"
	"File/ReadFile.cpp"
	"Log/Log.cpp"
	"Player/Player.cpp"
	"Recorder/Recorder.cpp"
	"Stream/Stream.cpp"
	"Stream/StreamManager.cpp"
	"TagHandle/TagHandle.cpp"
	"AudioPlusPlus.cpp"
)

if(BUILD_WITH_LOGGING)
	add_compile_definitions(ENABLE_LOGGING=True)
endif()

#public AudioPlusPlus headers
set(audioplusplus_HDRS
	"include/AudioPlusPlus/Device/Device.h"
	"include/AudioPlusPlus/Device/DeviceManager.h"
	"include/AudioPlusPlus/Device/DeviceManager.h"
	"include/AudioPlusPlus/File/File.h"
	"include/AudioPlusPlus/File/WriteFile.h"
	"include/AudioPlusPlus/File/ReadFile.h"
	"include/AudioPlusPlus/Log/Log.h"
	"include/AudioPlusPlus/Player/Player.h"
	"include/AudioPlusPlus/Recorder/Recorder.h"
	"include/AudioPlusPlus/Stream/Stream.h"
	"include/AudioPlusPlus/Stream/StreamManager.h"
	"include/AudioPlusPlus/TagHandle/TagHandle.h"
	"include/AudioPlusPlus/AudioPlusPlus.h"
)

add_library(AudioPlusPlus::audioplusplus ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	PRIVATE
		${SNDFILE_INCLUDE_DIR}
		${PORTAUDIO_INCLUDE_DIR}
		${TAGLIB_INCLUDE_DIR}
		$<$<BOOL:${BUILD_WITH_LOGGING}>:${SPDLOG_INCLUDE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		$<$<BOOL:${PORTAUDIO_FOUND}>:PortAudio::PortAudio>
		$<$<BOOL:${TAGLIB_FOUND}>:taglib::taglib>
		$<$<BOOL:${SNDFILE_FOUND}>:SndFile::sndfile>
		$<$<BOOL:${BUILD_WITH_LOGGING}>:spdlog::spdlog>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER "${audioplusplus_HDRS}"
)