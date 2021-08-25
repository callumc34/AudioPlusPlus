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

set(audioplusplus_HDRS
	include/AudioPlusPlus.h
	include/Config/Config.h
	include/Device/Device.h
	include/Device/DeviceManager.h
	include/File/File.h
	include/Log/Log.h
	include/Player/Player.h
	include/Player/Stream.h
)

add_library(AudioPlusPlus::audioplusplus ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		portaudio
		sndfile
		spdlog
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${SNDFILE_INCLUDE_DIR}
		${PORTAUDIO_INCLUDE_DIR}
		${SPDLOG_INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER "${audioplusplus_HDRS}"
)