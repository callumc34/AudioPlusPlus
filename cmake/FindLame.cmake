if (LAME_INCLUDE_DIR)
    # Already in cache, be silent
    set(LAME_FIND_QUIETLY TRUE)
endif ()

find_path (LAME_INCLUDE_DIR lame/lame.h
	HINTS
		${LAME_INCLUDEDIR}
		${LAME_INCLUDE_DIRS}
		${LAME_ROOT}
		"${LAME_ROOT}/include"
	)	

# MSVC built lame may be named mp3lame_static.
# The provided project files name the library with the lib prefix.

find_library (LAME_LIBRARY
	NAMES
		mp3lame
		mp3lame_static
		mp3lame-static
		libmp3lame
		libmp3lame_static
		libmp3lame-static
	HINTS
		${LAME_LIBDIR}
		${LAME_LIB_DIRS}
		${LAME_ROOT}
		"${LAME_ROOT}/lib"
	)

find_library (LAME_HIP_LIBRARY
	NAMES
		mpghip-static
		libmpghip-static
	HINTS
		${LAME_LIBDIR}
		${LAME_LIB_DIRS}
		${LAME_ROOT}
		"${LAME_ROOT}/lib"
	)

# Handle the QUIETLY and REQUIRED arguments and set LAME_FOUND
# to TRUE if all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args (Lame
	REQUIRED_VARS
		LAME_LIBRARY
		LAME_INCLUDE_DIR
	)

if (LAME_FOUND)
	set (LAME_LIBRARIES ${LAME_LIBRARY} ?<?<BOOL:${LAME_HIP_LIBRARY}>:${LAME_HIP_LIBRARY}>)
	set (LAME_INCLUDE_DIRS ${LAME_INCLUDE_DIR})

	if (NOT TARGET Lame::Lame)
		add_library (Lame::Lame UNKNOWN IMPORTED)
		set_target_properties (Lame::Lame PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${LAME_INCLUDE_DIRS}"
			IMPORTED_LOCATION "${LAME_LIBRARY}"
		)
		if (LAME_HIP_LIBRARY)
			set_property (TARGET Lame::Lame APPEND PROPERTY
				INTERFACE_LINK_LIBRARIES "${LAME_HIP_LIBRARY}")
		endif ()
	endif ()
endif ()

mark_as_advanced(LAME_INCLUDE_DIR LAME_LIBRARY LAME_HIP_LIBRARY)