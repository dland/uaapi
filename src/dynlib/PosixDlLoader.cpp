#include <algorithm>

#include "Exception.h"

#include "dynlib/ug/PosixDlLoader.h"

namespace Uaapi
{
    namespace
    {
        class isSameDl
        {
            std::string _name;

        public:
            isSameDl(const std::string& name)
                : _name(name)
            {}
            isSameDl(const DynamicLibrary* lib)
                : _name(lib->getName())
            {}

            bool operator()(const DynamicLibrary* lib)
            { return _name == lib->getName(); }
        };

        bool dlIsUnused(const DynamicLibrary* lib)
        { return lib->isUnused(); }

        void unloadDl(DynamicLibrary* lib)
        { delete lib; }

        bool isNull(DynamicLibrary* lib)
        { return lib == NULL; }
    }

    // Private
    void PosixDlLoader::_deleteOldest()
    {
        // Delete oldest unused element or throw exception
        CacheType::iterator it =  std::find_if(_cache.begin(), _cache.end(),
                                               Uaapi::dlIsUnused);
        if (it == _cache.end())
            throw RuntimeError("Cache is full.");

        delete *it;
        _cache.erase(it);
    }

    void PosixDlLoader::_deleteUnused()
    {
        for (CacheType::iterator it = _cache.begin(); it != _cache.end(); ++it)
            if ((*it)->isUnused())
            {
                delete *it;
                *it = NULL;
            }

        CacheType::iterator end =
            std::remove_if(_cache.begin(), _cache.end(), Uaapi::isNull);

        _cache.resize(end - _cache.begin());
    }

    // Contructor / Destructor
    PosixDlLoader::PosixDlLoader()
        : _cacheSize(PosixDlLoader::DEFAULT_SIZE)
    { _cache.reserve(PosixDlLoader::DEFAULT_SIZE); }

    PosixDlLoader::~PosixDlLoader()
    { std::for_each(_cache.begin(), _cache.end(), Uaapi::unloadDl); }

    // Public
    DynamicLibrary* PosixDlLoader::load(const std::string& dlName)
    {
        // Check if dl is in cache
        CacheType::iterator it = std::find_if(_cache.begin(), _cache.end(),
                                              Uaapi::isSameDl(dlName));
        if (it != _cache.end())
        {
            (*it)->isUnused(false);
            return *it;
        }

        // Check if cache is full
        if (_cache.size() == _cacheSize)
            _deleteOldest();

        // Load library
        DynamicLibrary* lib = new DynamicLibrary(dlName);
        _cache.push_back(lib);

        return lib;
    }

    void PosixDlLoader::setCacheSize(size_t size)
    {
        if (size == _cacheSize)
            return;

        if (size < _cacheSize)
        {
            _deleteUnused();
            if (_cache.size() > size)
                throw RuntimeError("Setting cache will remove used libraries.");

            _cache.resize(size);
        }
        else
            _cache.reserve(size);
        _cacheSize = size;
    }
}
