add_library(${PROJECT_NAME}
	AudioPlusPlus.cpp
	Config/Config.cpp
	Device/Device.cpp
	Device/DeviceManager.cpp
	File/File.cpp
	Log/Log.cpp
	Player/Player.cpp
	Player/Stream.cpp
)

if(BUILD_WITH_LOGGING)
	add_compile_definitions(ENABLE_LOGGING=True)
endif()

set(audioplusplus_HDRS
	include/AudioPlusPlus/AudioPlusPlus.h
	include/AudioPlusPlus/Config/Config.h
	include/AudioPlusPlus/Device/Device.h
	include/AudioPlusPlus/Device/DeviceManager.h
	include/AudioPlusPlus/File/File.h
	include/AudioPlusPlus/Log/Log.h
	include/AudioPlusPlus/Player/Player.h
	include/AudioPlusPlus/Player/Stream.h
)

add_library(AudioPlusPlus::audioplusplus ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${PORTAUDIO_LIBRARY}
	PRIVATE
		${SNDFILE_LIBRARY}
		$<$<BOOL:BUILD_WITH_LOGGING>:${SPDLOG_LIBRARY}>
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${SNDFILE_INCLUDE_DIR}
		${PORTAUDIO_INCLUDE_DIR}
		$<$<BOOL:BUILD_WITH_LOGGING>:${SPDLOG_INCLUDE_DIR}>
)