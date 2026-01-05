cmake_minimum_required(VERSION 3.25)
project(Wii-Tac-Toe)

find_library(AESND aesnd
  PATHS "${OGC_ROOT}/lib/${OGC_SUBDIR}"
  REQUIRED
)
find_library(FAT fat
  PATHS "${OGC_ROOT}/lib/${OGC_SUBDIR}"
  REQUIRED
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(PNG REQUIRED libpng)
pkg_check_modules(FREETYPE REQUIRED freetype2)
pkg_check_modules(MXML REQUIRED mxml)

include(FetchContent)
FetchContent_Declare(grrlib
  GIT_REPOSITORY https://github.com/GRRLIB/GRRLIB.git
  GIT_TAG        8feae891610ccd08ea2d2cb5d987fc74c47ad57c
)
FetchContent_Declare(grrmod
  URL https://codeload.github.com/GRRLIB/GRRMOD/tar.gz/eaebb7a92dcacd4e74ec600b2d0056a5fac408c7
)
set(GRRLIB_INSTALL OFF CACHE BOOL "Don't install" FORCE)
set(GRRMOD_INSTALL OFF CACHE BOOL "Don't install" FORCE)
set(GRRMOD_USE_MP3 OFF CACHE BOOL "Don't use MP3" FORCE)
FetchContent_MakeAvailable(grrlib grrmod)

file(GLOB_RECURSE SRC_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/fonts/*.cpp"
)

file(GLOB_RECURSE BIN_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/gfx/*.png"
)

add_executable(Wii-Tac-Toe)

target_compile_features(Wii-Tac-Toe PRIVATE cxx_std_26)

target_compile_options(Wii-Tac-Toe PRIVATE
  -Werror
  -Wall
  -Wextra
  -Wunused
  -Wmisleading-indentation
  -Wduplicated-cond
  -Wduplicated-branches
  -Wsuggest-override
)

target_sources(Wii-Tac-Toe PRIVATE
  ${SRC_FILES}
)

target_include_directories(Wii-Tac-Toe PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/source"
  ${MXML_INCLUDE_DIRS}
)

dkp_add_embedded_binary_library(data
  ${BIN_FILES}
)

target_link_libraries(Wii-Tac-Toe PRIVATE
  data
  grrlib
  grrmod
  ${PNG_LIBRARIES}
  ${FREETYPE_LIBRARIES}
  ${MXML_LIBRARIES}
  ${FAT}
  ${AESND}
)

ogc_create_dol(Wii-Tac-Toe)

get_target_property(DOL_FILE Wii-Tac-Toe DKP_FILE)
install(FILES "${DOL_FILE}" DESTINATION "Wii-Tac-Toe" RENAME "boot.dol")
install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/Wii-Tac-Toe/icon.png"
  "${CMAKE_CURRENT_SOURCE_DIR}/Wii-Tac-Toe/meta.xml"
  DESTINATION "Wii-Tac-Toe"
)

set(CPACK_PACKAGE_NAME "wii-tac-toe")
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
include(CPack)
