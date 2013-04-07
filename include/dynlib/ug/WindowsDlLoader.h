// -*- c++ -*-
#pragma once

#include <vector>

#include "WinClass.h"

#include "Ug.h"

#include "Singleton.h"

#include "dynlib/IDlLoader.h"

namespace Uaapi
{
    namespace ug
    { std::vector< DynamicLibrary* >* getCacheContainer(); }

    class _dldecl WindowsDlLoader : public IDlLoader, public WinClass
    {
        typedef std::vector< DynamicLibrary* > CacheType;

        size_t _cacheSize;
        CacheType* _cache;

        void _deleteUnused();
        void _deleteOldest();

        static const size_t DEFAULT_SIZE = 8;

    public:
        WindowsDlLoader();
        ~WindowsDlLoader();

        DynamicLibrary* load(const std::string& dlName);

        void unload(DynamicLibrary* lib)
        { lib->isUnused(true); }

        void setCacheSize(size_t size);
        size_t getCacheSize() const
        { return _cacheSize; }
    };

    typedef SingletonHolder< WindowsDlLoader > DlLoader;
}
