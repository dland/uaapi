#ifndef _PLUGINLOADER_H_
# define _PLUGINLOADER_H_

# include <map>

# include <algorithm>

# include "Exception.h"
# include "Dynlib.h"

namespace Uaapi
{
    /**
     * Singleton to manage loading/unloading plugins.
     *
     * A plugin is defined as a object of any type that can be
     * instanciated by calling the init() function present in a shared
     * object file, which returns a pointer to the plugin. The
     * PluginLoaderImpl::load() is used to instanciate the plugin.
     *
     * A plugin is identified by a name, which is the name of the
     * shared object file (without the systemn dependant extension).
     */
    class PluginLoaderImpl
    {
        std::map< Uaapi::DynamicLibrary*, int > _counts;
        std::map< void*, Uaapi::DynamicLibrary* > _plugins;

    public:

        /**
         * @brief Instanciate a plugin and return a pointer to it.
         *
         * @param name The plugin name
         */
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

        /**
         * @brief Unload the attached shared object file of given
         * plugin.
         *
         * @param plugin the plugin instance.
         */
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
