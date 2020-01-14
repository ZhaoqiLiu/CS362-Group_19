// LAF Base Library
// Copyright (C) 2019  Igara Studio S.A.
// Copyright (C) 2001-2017  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "base/log.h"

#include "base/debug.h"
#include "base/fstream_path.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

class nullbuf : public std::streambuf {
protected:
  int_type overflow(int_type ch) override {
    return traits_type::not_eof(ch);
  }
};

class nullstream : public std::ostream {
public:
  nullstream()
    : std::basic_ios<char_type, traits_type>(&m_buf)
    , std::ostream(&m_buf) { }
private:
  nullbuf m_buf;
};

// Default log level is error, which means that we'll log regular
// errors and fatal errors.
LogLevel log_level = LogLevel::ERROR;
nullstream null_stream;
std::ofstream log_stream;
std::ostream* log_ostream = &std::cerr;
std::string log_filename;

} // anonymous namespace

void base::set_log_filename(const char* filename)
{
  if (log_stream.is_open()) {
    log_stream.close();
    log_ostream = &std::cerr;
  }

  if (filename) {
    log_filename = filename;
    log_stream.open(FSTREAM_PATH(log_filename));
    log_ostream = &log_stream;
  }
  else {
    log_filename = std::string();
  }
}

void base::set_log_level(const LogLevel level)
{
  log_level = level;
}

LogLevel base::get_log_level()
{
  return log_level;
}

std::ostream& base::get_log_stream(const LogLevel level)
{
  ASSERT(level != NONE);

  if (log_level < level)
    return null_stream;
  else {
    ASSERT(log_ostream);
    return *log_ostream;
  }
}

static void LOGva(const char* format, va_list ap)
{
  va_list apTmp;
  va_copy(apTmp, ap);
  int size = std::vsnprintf(nullptr, 0, format, apTmp);
  va_end(apTmp);
  if (size < 1)
    return;                     // Nothing to log

  std::vector<char> buf(size+1);
  std::vsnprintf(&buf[0], buf.size(), format, ap);

  ASSERT(log_ostream);
  log_ostream->write(&buf[0], buf.size());
  log_ostream->flush();

#ifdef _DEBUG
  fputs(&buf[0], stderr);
  fflush(stderr);
#endif
}

std::ostream& LOG(const char* format, ...)
{
  ASSERT(format);
  if (!format || log_level < INFO)
    return null_stream;

  va_list ap;
  va_start(ap, format);
  LOGva(format, ap);
  va_end(ap);

  return log_stream;
}

std::ostream& LOG(const LogLevel level, const char* format, ...)
{
  ASSERT(format);
  if (!format || log_level < level)
    return null_stream;

  va_list ap;
  va_start(ap, format);
  LOGva(format, ap);
  va_end(ap);

  return log_stream;
}
