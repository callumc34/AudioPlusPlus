#Modified from: https://github.com/libsndfile/libsndfile/blob/master/vcpkg.json

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO PortAudio/portaudio
    REF af42647e3804f6a2472a00d943aaeedd641f7966
    SHA512 27bd4855f374b0d0a6c024194f404b6ceacfcd83529d746eb36369f627fb5d29457b2026d9b26818f7c8ca15ef29a3baeabcf3dba55ce732a42e331594bb5ea4
)

string(COMPARE EQUAL ${VCPKG_LIBRARY_LINKAGE} dynamic PA_BUILD_SHARED)

# NOTE: the ASIO backend will be built automatically if the ASIO-SDK is provided
# in a sibling folder of the portaudio source in vcpkg/buildtrees/portaudio/src
vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS
        -DPA_USE_DS=ON
        -DPA_USE_WASAPI=ON
        -DPA_USE_WDMKS=ON
        -DPA_USE_WMME=ON
        -DPA_USE_JACK=OFF
        -DBUILD_SHARED_LIBS=${PA_BUILD_SHARED}
    OPTIONS_DEBUG
        -DPA_ENABLE_DEBUG_OUTPUT:BOOL=ON
)

vcpkg_install_cmake()
vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/${PORT})

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)

if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/bin ${CURRENT_PACKAGES_DIR}/debug/bin)
endif()

# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)

vcpkg_fixup_pkgconfig()