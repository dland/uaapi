// -*- c++ -*-
#ifndef _UG_H_
# define _UG_H_

# if defined(POSIX)
#  define _dldecl
# elif defined(WIN32)
#  ifdef UAAPI_EXPORT
#   define _dldecl __declspec(dllexport)
#   define DLL_EXTERN
#  else
#   define _dldecl __declspec(dllimport)
#   define DLL_EXTERN extern
#  endif

// dll-export of std::string (Windows, U KILLIN ME)
#  pragma warning(push)
#  pragma warning(disable : 4231)

#  include <string>

DLL_EXTERN template class _dldecl std::allocator< char >;
DLL_EXTERN template class _dldecl std::basic_string<
    char,
    std::char_traits< char >,
    std::allocator< char >
    >;

#  pragma warning(pop)

# else
#  error "Unhandled build environment."
# endif

#endif  // _UG_H_
