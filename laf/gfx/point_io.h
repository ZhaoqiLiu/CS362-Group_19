// LAF Gfx Library
// Copyright (C) 2019  Igara Studio S.A.
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef GFX_POINT_IO_H_INCLUDED
#define GFX_POINT_IO_H_INCLUDED
#pragma once

#include "gfx/point.h"
#include <iosfwd>

namespace gfx {

  inline std::ostream& operator<<(std::ostream& os, const Point& point) {
    return os << "("
              << point.x << ", "
              << point.y << ")";
  }

  inline std::istream& operator>>(std::istream& in, Point& point) {
    while (in && in.get() != '(')
      ;

    if (!in)
      return in;

    char chr;
    in >> point.x >> chr
       >> point.y;

    return in;
  }

}

#endif
