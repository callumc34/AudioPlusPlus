vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO taglib/taglib
    REF 10721b4b410a688f036540d12b682f0ef6a8ca71
    SHA512 a23560845e507d8fe976d2e85d912d0f942238a40cb28755c7d8c4eeefe4e6dac590e74369d0b32feff9473c7966382acab3abaed4a834a9b0e754379bb327c7
    HEAD_REF master
)

if(VCPKG_CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
    set(WINRT_OPTIONS -DHAVE_VSNPRINTF=1 -DPLATFORM_WINRT=1)
endif()


string(COMPARE EQUAL ${VCPKG_LIBRARY_LINKAGE} dynamic BUILD_SHARED_LIBS)
string(COMPARE EQUAL ${VCPKG_LIBRARY_LINKAGE} static ENABLE_STATIC_RUNTIME)

vcpkg_configure_cmake(
    SOURCE_PATH "${SOURCE_PATH}"
    PREFER_NINJA
    OPTIONS
        -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        -DENABLE_STATIC_RUNTIME=${ENABLE_STATIC_RUNTIME}
        -DWITH_ZLIB=OFF
        ${WINRT_OPTIONS}
)
vcpkg_install_cmake()
vcpkg_fixup_pkgconfig()

set(pcfile "${CURRENT_PACKAGES_DIR}/lib/pkgconfig/taglib.pc")
set(pcfile "${CURRENT_PACKAGES_DIR}/debug/lib/pkgconfig/taglib.pc")

# remove the debug/include files
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

# copyright file
file(COPY "${SOURCE_PATH}/COPYING.LGPL" DESTINATION "${CURRENT_PACKAGES_DIR}/share/taglib")
file(COPY "${SOURCE_PATH}/COPYING.MPL" DESTINATION "${CURRENT_PACKAGES_DIR}/share/taglib")
file(RENAME "${CURRENT_PACKAGES_DIR}/share/taglib/COPYING.LGPL" "${CURRENT_PACKAGES_DIR}/share/taglib/copyright")

file(REMOVE "${CURRENT_PACKAGES_DIR}/bin/taglib-config.cmd" "${CURRENT_PACKAGES_DIR}/debug/bin/taglib-config.cmd") # Contains absolute paths

# remove bin directory for static builds (taglib creates a cmake batch file there)
if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    vcpkg_replace_string("${CURRENT_PACKAGES_DIR}/include/taglib/taglib_export.h" "defined(TAGLIB_STATIC)" "1")
    file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/bin" "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()

vcpkg_copy_pdbs()