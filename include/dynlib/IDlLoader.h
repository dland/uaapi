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
    /**
     * An abstract implementation of a class managing the
     * loading/unloading of dynamic libraries. The class also manages
     * a cache who's size can be changed.
     *
     * Each platform has its own implementation of each methods.
     */
    class _dldecl IDlLoader
    {
    public:
        virtual ~IDlLoader() {}

        // @brief Load a library indentified by the given name.
        virtual DynamicLibrary* load(const std::string& libName)=0;

        // @brief Unload a library.
        virtual void unload(DynamicLibrary* lib)=0;

        // @brief Set cache size.
        virtual void setCacheSize(size_t size)=0;

        // @brief Get cache size.
        virtual size_t getCacheSize() const=0;
    };
};

#endif // _IDLLOADER_H_
