// -*- c++ -*-
#ifndef _POSIXDLLOADER_H_
# define _POSIXDLLOADER_H_

# include <vector>

# include "Singleton.h"

# include "dynlib/IDlLoader.h"

namespace Uaapi
{
    class PosixDlLoader : public IDlLoader
    {
        typedef std::vector< DynamicLibrary* > CacheType;
        CacheType _cache;
        size_t _cacheSize;

        void _deleteUnused();
        void _deleteOldest();

        static const size_t DEFAULT_SIZE = 8;

    public:
        PosixDlLoader();
        ~PosixDlLoader();

        DynamicLibrary* load(const std::string& dlName);

        void unload(DynamicLibrary* lib)
        { lib->isUnused(true); }

        void setCacheSize(size_t size);
        size_t getCacheSize() const
        { return _cacheSize; }
    };

    typedef SingletonHolder< PosixDlLoader > DlLoader;
}

#endif // _POSIXDLLOADER_H_
