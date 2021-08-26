if(BUILD_EXAMPLES)
	add_executable(${PROJECT_NAME}-example1
		Example1/main.cpp
	)

	target_link_libraries(${PROJECT_NAME}-example1
		PUBLIC
			${PROJECT_NAME}
			${PORTAUDIO_LIBRARY}
		PRIVATE
			${SNDFILE_LIBRARY}
			${SPDLOG_LIBRARY}
			$<$<BOOL:${WIN32}>:shlwapi>
	)

	target_include_directories(${PROJECT_NAME}-example1
		PUBLIC
			${SNDFILE_INCLUDE_DIR}
			${PORTAUDIO_INCLUDE_DIR}
			${SPDLOG_INCLUDE_DIR}
	)
endif()