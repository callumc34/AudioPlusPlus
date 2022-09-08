if(BUILD_EXAMPLES)
	add_executable(${PROJECT_NAME}-playback-example
		playback.cpp
	)

	target_link_libraries(${PROJECT_NAME}-playback-example
		PUBLIC
			${PROJECT_NAME}
			$<$<BOOL:${PORTAUDIO_FOUND}>:PortAudio::PortAudio>
			$<$<BOOL:${TAGLIB_FOUND}>:taglib::taglib>

		PRIVATE			
			$<$<BOOL:${SNDFILE_FOUND}>:SndFile::sndfile>
			$<$<BOOL:${OGG_FOUND}>:Ogg::ogg>
			$<$<BOOL:${FLAC_FOUND}>:FLAC::FLAC>
			$<$<BOOL:${OPUS_FOUND}>:Opus::opus>
			$<$<BOOL:${Vorbis_Vorbis_FOUND}>:Vorbis::vorbis>
			$<$<BOOL:${Vorbis_Enc_FOUND}>:Vorbis::vorbisenc>
			$<$<BOOL:${Vorbis_File_FOUND}>:Vorbis::vorbisfile>
			$<$<BOOL:${LAME_FOUND}>:Lame::Lame>
			$<$<BOOL:${MPG123_FOUND}>:MPG123::libmpg123>
			$<$<BOOL:${BUILD_WITH_LOGGING}>:spdlog::spdlog>
			$<$<BOOL:${WIN32}>:shlwapi>
	)

	target_include_directories(${PROJECT_NAME}-playback-example
		PUBLIC
			${SNDFILE_INCLUDE_DIR}
			${PORTAUDIO_INCLUDE_DIR}
			${TAGLIB_INCLUDE_DIR}
			${SPDLOG_INCLUDE_DIR}
	)

	add_executable(${PROJECT_NAME}-recording-example
		recording.cpp
	)

	target_link_libraries(${PROJECT_NAME}-recording-example		
		PUBLIC
			${PROJECT_NAME}
			$<$<BOOL:${PORTAUDIO_FOUND}>:PortAudio::PortAudio>
			$<$<BOOL:${TAGLIB_FOUND}>:taglib::taglib>

		PRIVATE			
			$<$<BOOL:${SNDFILE_FOUND}>:SndFile::sndfile>
			$<$<BOOL:${OGG_FOUND}>:Ogg::ogg>
			$<$<BOOL:${FLAC_FOUND}>:FLAC::FLAC>
			$<$<BOOL:${OPUS_FOUND}>:Opus::opus>
			$<$<BOOL:${Vorbis_Vorbis_FOUND}>:Vorbis::vorbis>
			$<$<BOOL:${Vorbis_Enc_FOUND}>:Vorbis::vorbisenc>
			$<$<BOOL:${Vorbis_File_FOUND}>:Vorbis::vorbisfile>
			$<$<BOOL:${LAME_FOUND}>:Lame::Lame>
			$<$<BOOL:${MPG123_FOUND}>:MPG123::libmpg123>
			$<$<BOOL:${BUILD_WITH_LOGGING}>:spdlog::spdlog>
			$<$<BOOL:${WIN32}>:shlwapi>
	)

	target_include_directories(${PROJECT_NAME}-recording-example
		PUBLIC
			${SNDFILE_INCLUDE_DIR}
			${PORTAUDIO_INCLUDE_DIR}
			${TAGLIB_INCLUDE_DIR}
			${SPDLOG_INCLUDE_DIR}
	)
endif()