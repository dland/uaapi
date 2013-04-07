#include <dlfcn.h>

#include "Exception.h"

#include "dynlib/ug/PosixDynamicLibrary.h"

namespace Uaapi
{
    PosixDynamicLibrary::PosixDynamicLibrary(const std::string& dlName)
        : _unused(false)
    {
        _name = dlName;
        std::string fileName = std::string("lib") + dlName + ".so";

        _handle = ::dlopen(fileName.c_str(), RTLD_LAZY);

        if (!_handle)
            throw FatalError(::dlerror());
    }

    PosixDynamicLibrary::~PosixDynamicLibrary()
    { ::dlclose(_handle); }

    bool PosixDynamicLibrary::hasSymbol(const std::string& symbol)
    {
        try
        { getSymbolAddress(symbol); }
        catch (Exception&)
        { return false; }
        return true;
    }

    void* PosixDynamicLibrary::getSymbolAddress(const std::string& symbol)
    {
        ::dlerror();
        void* addr = ::dlsym(_handle, symbol.c_str());

        const char* error = ::dlerror();

        if (error)
            throw FatalError(error);
        return addr;
    }
}
