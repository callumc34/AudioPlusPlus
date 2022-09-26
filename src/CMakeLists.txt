if(BUILD_WITH_LOGGING)
	add_compile_definitions(ENABLE_LOGGING=True)
endif()

if(ENABLE_SNDFILE)
	set(SNDFILE_READ "File/SndReadFile.cpp")
	set(SNDFILE_WRITE "File/SndWriteFile.cpp")
endif()

add_library(${PROJECT_NAME}
	"Device/Device.cpp"
	"Device/DeviceManager.cpp"
	"Exceptions/Exception.cpp"
	"File/File.cpp"
	"File/ReadFile.cpp"
	"File/WriteFile.cpp"
	${SNDFILE_READ}
	${SNDFILE_WRITE}
	"Log/Log.cpp"
	"Player/Player.cpp"
	"Recorder/Recorder.cpp"
	"Stream/Stream.cpp"
	"Stream/StreamManager.cpp"
	"TagHandle/TagHandle.cpp"
	"AudioPlusPlus.cpp"
)

#public AudioPlusPlus headers
set(audioplusplus_HDRS
	"include/AudioPlusPlus/Device/Device.h"
	"include/AudioPlusPlus/Device/DeviceManager.h"
	"include/AudioPlusPlus/Device/DeviceManager.h"
	"include/AudioPlusPlus/Exceptions/Exception.h"
	"include/AudioPlusPlus/File/File.h"
	"include/AudioPlusPlus/File/ReadFile.h"
	"include/AudioPlusPlus/File/WriteFile.h"
	$<$<BOOL:${ENABLE_SNDFILE}>:"include/AudioPlusPlus/File/SndReadFile.h">
	$<$<BOOL:${ENABLE_SNDFILE}>:"include/AudioPlusPlus/File/SndWriteFile.h">
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
		$<$<BOOL:${ENABLE_SNDFILE}>:${SNDFILE_INCLUDE_DIR}>
		${PORTAUDIO_INCLUDE_DIR}
		${TAGLIB_INCLUDE_DIR}
		$<$<BOOL:${BUILD_WITH_LOGGING}>:${SPDLOG_INCLUDE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		$<$<BOOL:${PORTAUDIO_FOUND}>:PortAudio::PortAudio>
		$<$<BOOL:${TAGLIB_FOUND}>:taglib::taglib>
		$<$<BOOL:${ENABLE_SNDFILE}>:SndFile::sndfile>
		$<$<BOOL:${BUILD_WITH_LOGGING}>:spdlog::spdlog>
)