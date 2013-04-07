#include "Exception.h"

#include "dynlib/ug/WindowsDynamicLibrary.h"

namespace Uaapi
{
    WindowsDynamicLibrary::WindowsDynamicLibrary(const std::string& dlName)
        : _unused(false), _name(dlName)
    {
        std::string fileName = dlName + ".dll";

        _handle = LoadLibrary(fileName.c_str());

        if (!_handle)
            throw FatalError(getErrorMess(::GetLastError()));
    }

    WindowsDynamicLibrary::~WindowsDynamicLibrary()
    { ::FreeLibrary(_handle); }

    bool WindowsDynamicLibrary::hasSymbol(const std::string& symbol)
    {
        try
        { getSymbolAddress(symbol); }
        catch (Exception&)
        { return false; }
        return true;
    }

    void* WindowsDynamicLibrary::getSymbolAddress(const std::string& symbol)
    {
        void* addr = ::GetProcAddress(_handle, symbol.c_str());

        if (!addr)
            throw FatalError(getErrorMess(::GetLastError()));
        return addr;
    }
}
