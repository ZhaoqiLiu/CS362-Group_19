// LAF Base Library
// Copyright (c) 2001-2017 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

// Always undefine ERROR macro just in case (so we can include
// base/log.h as the last header file)
#ifdef ERROR
#undef ERROR
#endif

#ifndef BASE_LOG_H_INCLUDED
#define BASE_LOG_H_INCLUDED

// Don't use pragma once because we want to undef ERROR each time this
// file is included.
//#pragma once

enum LogLevel {
  NONE    = 0, // Default log level: do not log
  FATAL   = 1, // Something failed and we CANNOT continue the execution
  ERROR   = 2, // Something failed, the UI should show this, and we can continue
  WARNING = 3, // Something failed, the UI don't need to show this, and we can continue
  INFO    = 4, // Information about some important event
  VERBOSE = 5, // Information step by step
};

#ifdef __cplusplus
#include <iosfwd>

namespace base {

  void set_log_filename(const char* filename);
  void set_log_level(const LogLevel level);
  LogLevel get_log_level();

  std::ostream& get_log_stream(const LogLevel level);

} // namespace base

// E.g. LOG("text in information log level\n");
std::ostream& LOG(const char* format, ...);
std::ostream& LOG(const LogLevel level, const char* format, ...);

// E.g. LOG(INFO) << "some information\n";
inline std::ostream& LOG(const LogLevel level) {
  return base::get_log_stream(level);
}

inline void LOG(int) {
  // This is in case LOG() is used with an integer value instead of
  // LogLevel, an error must be triggered (e.g. on wingdi.h ERROR is
  // defined as 0, and with this definition we avoid calling LOG(const
  // char* format=0=nullptr) and we detect the problem at compile
  // time.
}

#endif

#endif
