// -*- c++ -*-
#pragma once

#include <string>

#include <Windows.h>

#include "WinClass.h"

#include "Ug.h"

#include "dynlib/IDynamicLibrary.h"

namespace Uaapi
{
    class _dldecl WindowsDynamicLibrary : public IDynamicLibrary,
                                          public WinClass
    {
        HMODULE _handle;
        bool _unused;
        std::string _name;

    public:
        WindowsDynamicLibrary(const std::string& dlName);
        ~WindowsDynamicLibrary();

        const std::string& getName() const
        { return _name; };

        bool hasSymbol(const std::string& symbol);
        void* getSymbolAddress(const std::string& symbol);

        bool isUnused() const { return _unused; }
        void isUnused(bool unused)  { _unused = unused; }
    };

    typedef WindowsDynamicLibrary DynamicLibrary;
}
