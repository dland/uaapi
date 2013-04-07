// -*- c++ -*-
#ifndef _IDYNAMICLIBRARY_H_
# define _IDYNAMICLIBRARY_H_

# include "Ug.h"

namespace Uaapi
{
    class _dldecl IDynamicLibrary
    {
    public:
        virtual ~IDynamicLibrary() {}

        virtual const std::string& getName() const=0;

        virtual bool hasSymbol(const std::string& symbol)=0;
        virtual void* getSymbolAddress(const std::string& symbol)=0;

        template < class T > T getSymbol(const std::string& symbol)
        {
            void* add = getSymbolAddress(symbol);

            return reinterpret_cast<T>(add);
        }
    };
};

#endif // _IDYNAMICLIBRARY_H_
