# LAF
# Copyright (C) 2016-2018  David Capello

cmake_minimum_required(VERSION 3.2)

project(laf C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Search in the "cmake" directory for additional CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Options
set(LAF_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "Root LAF CMakeLists.txt file location")
set(LAF_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "Root location of LAF binary files")

if(SKIA_DIR)
  set(LAF_OS_DEFAULT_BACKEND "skia")
else()
  set(LAF_OS_DEFAULT_BACKEND "none")
endif()

option(LAF_WITH_TESTS "Enable LAF tests" ON)
set(LAF_OS_BACKEND ${LAF_OS_DEFAULT_BACKEND} CACHE STRING "Select laf-os backend")
set_property(CACHE LAF_OS_BACKEND PROPERTY STRINGS "none" "skia")
if(NOT APPLE AND UNIX)
option(LAF_OS_WITH_GTK "Use GTK library for native dialogs" OFF)
endif()

# Testing
if(LAF_WITH_TESTS)
  enable_testing()
  include(LafFindTests)
endif()

add_subdirectory(third_party)
add_subdirectory(base)
add_subdirectory(gfx)
add_subdirectory(ft)
add_subdirectory(os)

# Information

if(NOT LAF_CONF_PRINTED)
  set(LAF_CONF_PRINTED TRUE CACHE INTERNAL "")
  message(
    "=== LAF CONFIGURATION ===\n"
    " Backend:  ${LAF_OS_BACKEND}\n"
    " Pixman:   ${PIXMAN_LIBRARY}\n"
    " FreeType: ${LAF_FREETYPE_LIBRARIES}\n"
    " HarfBuzz: ${LAF_HARFBUZZ_LIBRARIES}\n"
    "=========================")
  if(LAF_OS_BACKEND STREQUAL "skia")
    message(" Skia dir: ${SKIA_DIR}")
  else()
    if(NOT SKIA_DIR)
      message(WARNING "Specify SKIA_DIR if you want to compile laf-os with the Skia backend")
    endif()
  endif()
endif()
