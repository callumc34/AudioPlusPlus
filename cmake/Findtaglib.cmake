if (TAGLIB_INCLUDE_DIR)
	set(TAGLIB_FIND_QUIETLY TRUE)
endif()

find_package(PkgConfig QUIET)
pkg_check_modules(_taglib QUIET taglib)

find_path(TAGLIB_INCLUDE_DIR taglib/taglib.h
	HINTS
		${TAGLIB_INCLUDEDIR}
		${TAGLIB_INCLUDE_DIRS}
		${TAGLIB_ROOT}
		"${TAGLIB_ROOT}/include"
)

find_library(TAGLIB_LIBRARY
	NAMES
		tag
		tag_static
		libtag
		libtag_static
	HINTS
		${TAGLIB_LIBDIR}
		${TAGLIB_LIB_DIRS}
		${TAGLIB_ROOT}
		"${TAGLIB_ROOT}/lib"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(taglib
	REQUIRED_VARS
		TAGLIB_LIBRARY
		TAGLIB_INCLUDE_DIR
	VERSION_VAR
		TAGLIB_VERSION
)

if(TAGLIB_FOUND)
	set(TAGLIB_LIBRARIES ${TAGLIB_LIBRARY})
	set(TAGLIB_INCLUDE_DIRS ${TAGLIB_INCLUDE_DIR})

	if (NOT TARGET taglib::taglib)
		add_library (taglib::taglib UNKNOWN IMPORTED)
		set_target_properties (taglib::taglib PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${TAGLIB_INCLUDE_DIRS}"
			IMPORTED_LOCATION "${TAGLIB_LIBRARIES}"
		)
	endif ()
endif()

mark_as_advanced(TAGLIB_INCLUDE_DIR TAGLIB_LIBRARY)