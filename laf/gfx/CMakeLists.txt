# LAF GFX Library
# Copyright (c) 2018  Igara Studio S.A.
# Copyright (C) 2001-2017  David Capello

if(NOT PIXMAN_LIBRARY)
  find_library(PIXMAN_LIBRARY NAMES pixman pixman-1)
  find_path(PIXMAN_INCLUDE_DIR NAMES pixman.h PATH_SUFFIXES pixman-1)
endif()

set(LAF_GFX_EXTRA_SOURCES)
if(PIXMAN_LIBRARY)
  set(LAF_GFX_EXTRA_SOURCES
    packing_rects.cpp
    region.cpp)
endif()

add_library(laf-gfx
  color_space.cpp
  hsl.cpp
  hsv.cpp
  rgb.cpp
  ${LAF_GFX_EXTRA_SOURCES})

target_link_libraries(laf-gfx laf-base)
if(PIXMAN_LIBRARY)
  target_link_libraries(laf-gfx ${PIXMAN_LIBRARY})
  target_include_directories(laf-gfx PRIVATE ${PIXMAN_INCLUDE_DIR})
endif()

if(LAF_WITH_TESTS)
  laf_find_tests(. laf-gfx)
  if(PIXMAN_LIBRARY)
    target_compile_definitions(packing_rects_tests PRIVATE HAVE_PIXMAN)
    target_compile_definitions(region_tests PRIVATE HAVE_PIXMAN)
  endif()
endif()
