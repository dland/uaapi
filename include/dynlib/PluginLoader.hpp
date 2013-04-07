#ifndef _PLUGINLOADER_H_
# define _PLUGINLOADER_H_

# include <map>

# include <algorithm>

# include "Exception.h"
# include "Dynlib.h"

namespace Uaapi
{
    class PluginLoaderImpl
    {
        std::map< Uaapi::DynamicLibrary*, int > _counts;
        std::map< void*, Uaapi::DynamicLibrary* > _plugins;

    public:
        template < class PluginType >
        PluginType* load(const std::string& name)
        {
            Uaapi::DynamicLibrary* lib =
                Uaapi::DlLoader::instance().load(name);

            _counts[lib]++;

            PluginType* (*init)() =
                lib->getSymbol< PluginType* (*)() >("init");
            PluginType* plugin = init();

            _plugins[plugin] = lib;

            return plugin;
        }

        template < class PluginType >
        void unload(PluginType* plugin)
        {
            if (_plugins.find(plugin) == _plugins.end())
                throw RuntimeError("Given plugin wasn't "
                                   "loaded by PluginManager.");

            _counts[_plugins[plugin]]--;
            if (_counts[_plugins[plugin]] == 0)
            {
                Uaapi::DlLoader::instance().unload(_plugins[plugin]);
                _counts.erase(_plugins[plugin]);
            }

            _plugins.erase(plugin);
            delete plugin;
        }
    };

    typedef SingletonHolder< PluginLoaderImpl > PluginLoader;
}

#endif // _PLUGINLOADER_H_
