find_package(PkgConfig QUIET)
pkg_check_modules(_spdlog QUIET spdlog)

find_path(SPDLOG_INCLUDE_DIR spdlog/spdlog.h
	HINTS
		${SPDLOG_INCLUDEDIR}
		${SPDLOG_INCLUDE_DIRS}
		${SPDLOG_ROOT}
)

find_library(SPDLOG_LIBRARY
	NAMES
		spdlog
		spdlog_static
		libspdlog
		libspdlog_static
	HINTS
		${SPDLOG_LIBDIR}
		${SPDLOG_LIB_DIRS}
		${SPDLOG_ROOT}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(spdlog
	REQUIRED_VARS
		SPDLOG_LIBRARY
		SPDLOG_INCLUDE_DIR
	VERSION_VAR
		SPDLOG_VERSION
)

if(SPDLOG_FOUND)
	set(SPDLOG_LIBRARIES ${SPDLOG_LIBRARIES})
	set(SPDLOG_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIR})

	if (NOT TARGET spdlog::spdlog)
		add_library (spdlog::spdlog UNKNOWN IMPORTED)
		set_target_properties (spdlog::spdlog PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_INCLUDE_DIRS}"
			IMPORTED_LOCATION "${SPDLOG_LIBRARIES}"
		)
	endif ()
endif()

mark_as_advanced(SPDLOG_INCLUDE_DIR SPDLOG_LIBARY)