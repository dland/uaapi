// -*- c++ -*-
#ifndef _POSIXDYNAMICLIBRARY_H_
# define _POSIXDYNAMICLIBRARY_H_

# include <string>

# include "dynlib/IDynamicLibrary.h"

namespace Uaapi
{
    class PosixDynamicLibrary : public IDynamicLibrary
    {
        void* _handle;
        bool _unused;
        std::string _name;

    public:
        PosixDynamicLibrary(const std::string& dlName);
        ~PosixDynamicLibrary();

        const std::string& getName() const
        { return _name; };

        bool hasSymbol(const std::string& symbol);
        void* getSymbolAddress(const std::string& symbol);

        bool isUnused() const { return _unused; }
        void isUnused(bool unused) { _unused = unused; }
    };

    typedef PosixDynamicLibrary DynamicLibrary;
}

#endif // _POSIXDYNAMICLIBRARY_H_
