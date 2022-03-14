vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO libsndfile/libsndfile
    REF 77acc6d3623b06c75461a8bfdeff0066278c2eea
    SHA512 04d6f5ae7ba6626e41cc807b66932edf169674dd00c98d73582b431f3e6360d6085382f15a270bd0fb5a0b9231f78b256411e1fd2c2282e1c086fecb6e60b8ca
    HEAD_REF master
)

if(VCPKG_LIBRARY_LINKAGE STREQUAL dynamic)
    vcpkg_find_acquire_program(PYTHON3)
endif()

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        external-libs ENABLE_EXTERNAL_LIBS
        mpeg ENABLE_MPEG
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DBUILD_EXAMPLES=OFF
        -DBUILD_REGTEST=OFF
        -DBUILD_TESTING=OFF
        -DENABLE_BOW_DOCS=OFF
        -DBUILD_PROGRAMS=OFF
        -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=ON
    MAYBE_UNUSED_VARIABLES
        -DPYTHON_EXECUTABLE=${PYTHON3}
        ${FEATURE_OPTIONS}
)

vcpkg_install_cmake()

if(WIN32 AND (NOT MINGW) AND (NOT CYGWIN))
    set(CONFIG_PATH cmake)
else()
    set(CONFIG_PATH lib/cmake/SndFile)
endif()

vcpkg_fixup_cmake_targets(CONFIG_PATH ${CONFIG_PATH} TARGET_PATH share/SndFile)
vcpkg_fixup_pkgconfig(SYSTEM_LIBRARIES m)

vcpkg_copy_pdbs()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)

# Handle copyright
file(INSTALL ${SOURCE_PATH}/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)