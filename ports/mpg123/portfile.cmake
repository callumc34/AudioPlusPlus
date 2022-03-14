vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO madebr/mpg123
    REF d1bd549d68cba8090f01cf1c213752aae03da53e
    SHA512 17e336097d8db7222160a6a870488fbb49acd168526730d6714cb0f529f613255c5999c451263938710ab349e4672a6ef678e0ea0abb1e09f72ab77223d9aa15
    HEAD_REF master
)

include("${CURRENT_INSTALLED_DIR}/share/yasm-tool-helper/yasm-tool-helper.cmake")
yasm_tool_helper(APPEND_TO_PATH)

vcpkg_configure_cmake(
    SOURCE_PATH "${SOURCE_PATH}/ports/cmake"
)

vcpkg_install_cmake()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/${PORT})

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")

file(INSTALL "${SOURCE_PATH}/COPYING"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME COPYRIGHT
)