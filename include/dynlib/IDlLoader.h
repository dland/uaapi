// -*- c++ -*-
#ifndef _IDLLOADER_H_
# define _IDLLOADER_H_

# include "Ug.h"

# if defined(POSIX)
#  include "dynlib/ug/PosixDynamicLibrary.h"
# elif defined(WIN32)
#  include "dynlib/ug/WindowsDynamicLibrary.h"
# else
#  error "Unhandeled build environment."
# endif

namespace Uaapi
{
    class _dldecl IDlLoader
    {
    public:
        virtual ~IDlLoader() {}

        virtual DynamicLibrary* load(const std::string& libName)=0;
        virtual void unload(DynamicLibrary* lib)=0;

        virtual void setCacheSize(size_t size)=0;
        virtual size_t getCacheSize() const=0;
    };
};

#endif // _IDLLOADER_H_
