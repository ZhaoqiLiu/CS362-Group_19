// LAF Gfx Library
// Copyright (C) 2019  Igara Studio S.A.
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef GFX_SIZE_IO_H_INCLUDED
#define GFX_SIZE_IO_H_INCLUDED
#pragma once

#include "gfx/size.h"
#include <iosfwd>

namespace gfx {

  inline std::ostream& operator<<(std::ostream& os, const Size& size) {
    return os << "("
              << size.w << ", "
              << size.h << ")";
  }

  inline std::istream& operator>>(std::istream& in, Size& size) {
    while (in && in.get() != '(')
      ;

    if (!in)
      return in;

    char chr;
    in >> size.w >> chr
       >> size.h;

    return in;
  }

}

#endif
