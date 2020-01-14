# LAF: The Lost Application Framework

[![Build Status](https://travis-ci.org/aseprite/laf.svg)](https://travis-ci.org/aseprite/laf)
[![Build status](https://ci.appveyor.com/api/projects/status/3hqecxtkobx2gofo?svg=true)](https://ci.appveyor.com/project/dacap/laf)
[![MIT Licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.txt)

A library to create Windows, macOS, and Linux desktop applications.

This library is under active development so we don't provide API or
ABI compatibility at this moment.

## Modules

* [base](base): Base functions for any kind of application.
* [gfx](gfx): Generic graphics classes (rectangle, point, region, etc.)
* [ft](ft): FreeType wrapper used by the `os` module.
* [os](os): Functions to create windows in your Operating System desktop.

## License

LAF is distributed under the terms of [the MIT license](LICENSE.txt).

Some functions in LAF depends on third party libraries:

* [base::encode/decode_base64](base/base64.cpp) functions use
  [stringencoders](https://github.com/client9/stringencoders) by
  [Nick Galbreath](https://github.com/client9)
  ([MIT license](https://github.com/aseprite/stringencoders/blob/master/LICENSE)).
* Tests use the [Google Test](https://github.com/aseprite/googletest/tree/master/googletest)
  framework by Google Inc. licensed under
  [a BSD-like license](https://github.com/aseprite/googletest/blob/master/googletest/LICENSE).
* Color spaces and the laf::os library use code from the [Skia library](https://skia.org)
  by Google Inc. licensed under [a BSD-like license](https://github.com/aseprite/skia/blob/master/LICENSE).
