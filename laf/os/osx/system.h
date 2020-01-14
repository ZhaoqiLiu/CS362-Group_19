// LAF OS Library
// Copyright (C) 2016  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OS_OSX_SYSTEM_H
#define OS_OSX_SYSTEM_H
#pragma once

#include "os/common/system.h"

#include "os/osx/app.h"

namespace os {

Logger* get_macos_logger();

bool osx_is_key_pressed(KeyScancode scancode);
int osx_get_unicode_from_scancode(KeyScancode scancode);

class OSXSystem : public CommonSystem {
public:
  OSXSystem() : m_menus(nullptr) {
  }

  ~OSXSystem() {
    delete m_menus;
  }

  void setAppMode(AppMode appMode) override {
    OSXApp::instance()->setAppMode(appMode);
  }

  void activateApp() override {
    OSXApp::instance()->activateApp();
  }

  void finishLaunching() override {
    // Start processing NSApplicationDelegate events. (E.g. after
    // calling this we'll receive application:openFiles: and we'll
    // generate DropFiles events.)  events
    OSXApp::instance()->finishLaunching();
  }

  Logger* logger() override {
    return get_macos_logger();
  }

  Menus* menus() override {
    if (!m_menus)
      m_menus = new MenusOSX();
    return m_menus;
  }

  bool isKeyPressed(KeyScancode scancode) override {
    return osx_is_key_pressed(scancode);
  }

  int getUnicodeFromScancode(KeyScancode scancode) override {
    return osx_get_unicode_from_scancode(scancode);
  }

private:
  Menus* m_menus;
};

} // namespace os

#endif
