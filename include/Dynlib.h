// -*- c++ -*-
#ifndef _DYNLIB_H_
# define _DYNLIB_H_

# include "dynlib/IDlLoader.h"
# include "dynlib/IDynamicLibrary.h"

# if defined(POSIX)
#  include "dynlib/ug/PosixDynamicLibrary.h"
#  include "dynlib/ug/PosixDlLoader.h"
# elif defined(WIN32)
#  include "dynlib/ug/WindowsDynamicLibrary.h"
#  include "dynlib/ug/WindowsDlLoader.h"
# else
#  error "Unhandeled build environment."
# endif

#endif // _DYNLIB_H_
