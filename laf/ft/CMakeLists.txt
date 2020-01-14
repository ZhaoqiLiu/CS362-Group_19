# LAF FreeType Wrapper
# Copyright (C) 2017 David Capello

if(NOT FREETYPE_LIBRARIES)
  find_package(Freetype REQUIRED)
endif()
if(NOT HARFBUZZ_LIBRARIES)
  find_package(HarfBuzz REQUIRED)
endif()

add_library(laf-ft
  lib.cpp
  stream.cpp)

target_link_libraries(laf-ft
  laf-base
  ${FREETYPE_LIBRARIES}
  ${HARFBUZZ_LIBRARIES})

target_include_directories(laf-ft
  PUBLIC
  ${FREETYPE_INCLUDE_DIRS}
  ${HARFBUZZ_INCLUDE_DIRS})

set(LAF_FREETYPE_LIBRARIES ${FREETYPE_LIBRARIES} PARENT_SCOPE)
set(LAF_HARFBUZZ_LIBRARIES ${HARFBUZZ_LIBRARIES} PARENT_SCOPE)
