if (PORTAUDIO_INCLUDE_DIR)
	set(PORTAUDIO_FIND_QUIETLY TRUE)
endif()

find_package(PkgConfig QUIET)
pkg_check_modules(_portaudio QUIET portaudio)

find_path(PORTAUDIO_INCLUDE_DIR portaudio.h
	HINTS
		${PORTAUDIO_INCLUDEDIR}
		${PORTAUDIO_INCLUDE_DIRS}
		${PORTAUDIO_ROOT}
		"${PORTAUDIO_ROOT}/include"
)

find_library(PORTAUDIO_LIBRARY
	NAMES
		portaudio
		portaudio_static
		libportaudio
		libportaudio_static
	HINTS
		${PORTAUDIO_LIBDIR}
		${PORTAUDIO_LIB_DIRS}
		${PORTAUDIO_ROOT}
		"${PORTAUDIO_ROOT}/lib"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(portaudio
	REQUIRED_VARS
		PORTAUDIO_LIBRARY
		PORTAUDIO_INCLUDE_DIR
	VERSION_VAR
		PORTAUDIO_VERSION
)
message(STATUS "PORTAUDIO_FOUND=${PORTAUDIO_FOUND}")
if(PORTAUDIO_FOUND)
	set(PORTAUDIO_LIBRARIES ${PORTAUDIO_LIBRARY})
	set(PORTAUDIO_INCLUDE_DIRS ${PORTAUDIO_INCLUDE_DIR})

	if (NOT TARGET PortAudio::PortAudio)
		add_library (PortAudio::PortAudio UNKNOWN IMPORTED)
		set_target_properties (PortAudio::PortAudio PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${PORTAUDIO_INCLUDE_DIRS}"
			IMPORTED_LOCATION "${PORTAUDIO_LIBRARIES}"
		)
	endif ()
endif()

mark_as_advanced(PORTAUDIO_INCLUDE_DIR PORTAUDIO_LIBRARY)