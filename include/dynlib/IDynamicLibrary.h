// -*- c++ -*-
#ifndef _IDYNAMICLIBRARY_H_
# define _IDYNAMICLIBRARY_H_

# include "Ug.h"

namespace Uaapi
{
    /**
     * An abstract manipulator class of the dynamic library concept.
     *
     * Each platform has an implementation of the different methods.
     */
    class _dldecl IDynamicLibrary
    {
    public:
        virtual ~IDynamicLibrary() {}

        // @brief Get the name of the dynamic library.
        virtual const std::string& getName() const=0;

        // @brief Return's true if the dynamic library has a specif
        // symbol.
        virtual bool hasSymbol(const std::string& symbol)=0;

        // @brief Return's a pointer to the given symbol.
        virtual void* getSymbolAddress(const std::string& symbol)=0;

        // @brief Returns an object of the given symbol and type
        // referencing the symbols addres.
        template < class T > T getSymbol(const std::string& symbol)
        {
            void* add = getSymbolAddress(symbol);

            return reinterpret_cast<T>(add);
        }
    };
};

#endif // _IDYNAMICLIBRARY_H_
