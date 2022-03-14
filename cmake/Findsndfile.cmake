if (SNDFILE_INCLUDE_DIR)
	set(SNDFILE_FIND_QUIETLY TRUE)
endif()

find_package(PkgConfig QUIET)
pkg_check_modules(_sndfile QUIET sndfile)

find_path(SNDFILE_INCLUDE_DIR sndfile.h
	HINTS
		${SNDFILE_INCLUDEDIR}
		${SNDFILE_INCLUDE_DIRS}
		${SNDFILE_ROOT}
		"${SNDFILE_ROOT}/include"
)

find_library(SNDFILE_LIBRARY
	NAMES
		sndfile
		sndfile_static
		libsndfile
		libsndfile_static
	HINTS
		${SNDFILE_LIBDIR}
		${SNDFILE_LIB_DIRS}
		${SNDFILE_ROOT}
		"${SNDFILE_ROOT}/lib"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sndfile
	REQUIRED_VARS
		SNDFILE_LIBRARY
		SNDFILE_INCLUDE_DIR
	VERSION_VAR
		SNDFILE_VERSION
)

if(SNDFILE_FOUND)
	set(SNDFILE_LIBRARIES ${SNDFILE_LIBRARY})
	set(SNDFILE_INCLUDE_DIRS ${SNDFILE_INCLUDE_DIR})

	if (NOT TARGET SndFile::sndfile)
		add_library (SndFile::sndfile UNKNOWN IMPORTED)
		set_target_properties (SndFile::sndfile PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${SNDFILE_INCLUDE_DIRS}"
			IMPORTED_LOCATION "${SNDFILE_LIBRARIES}"
		)
	endif ()
endif()

mark_as_advanced(SNDFILE_INCLUDE_DIR SNDFILE_LIBRARY)