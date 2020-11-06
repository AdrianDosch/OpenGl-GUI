/****************************************************************************
 *
 * ftconfig.h
 *
 *   ANSI-specific configuration file (specification only).
 *
 * Copyright (C) 1996-2020 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


  /**************************************************************************
   *
   * This header file contains a number of macro definitions that are used by
   * the rest of the engine.  Most of the macros here are automatically
   * determined at compile time, and you should not need to change it to port
   * FreeType, except to compile the library with a non-ANSI compiler.
   *
   * Note however that if some specific modifications are needed, we advise
   * you to place a modified copy in your build directory.
   *
   * The build directory is usually `builds/<system>`, and contains
   * system-specific files that are always included first when building the
   * library.
   *
   * This ANSI version should stay in `include/config/`.
   *
   */

#ifndef FTCONFIG_H_
#define FTCONFIG_H_

#include "../../ft2build.h" // changed from <ft2build.h>
#include "ftoption.h" //changed from FT_CONFIG_OPTIONS_H
#include "../config/ftstdlib.h"  //changed from FT_CONFIG_STANDARD_LIBRARY_H

#include "../config/integer-types.h" //changd from <freetype/config/integer-types.h>
#include "../config/public-macros.h" //changd from <freetype/config/public-macros.h>
#include "../config/mac-support.h" //changd from <freetype/config/mac-support.h>

#endif /* FTCONFIG_H_ */


/* END */
