// LAF OS Library
// Copyright (C) 2019  Igara Studio S.A.
// Copyright (C) 2012-2016  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OS_OSX_APP_H_INCLUDED
#define OS_OSX_APP_H_INCLUDED
#pragma once

#include "os/app_mode.h"

namespace os {

  class OSXApp {
  public:
    static OSXApp* instance();

    OSXApp();
    ~OSXApp();

    bool init();
    void setAppMode(AppMode appMode);
    void activateApp();
    void finishLaunching();

  private:
    class Impl;
    Impl* m_impl;
  };

} // namespace os

#endif
