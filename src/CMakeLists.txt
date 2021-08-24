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