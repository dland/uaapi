#ifndef _CREATIONPOLICIES_H_
# define _CREATIONPOLICIES_H_

namespace Uaapi
{
    template < class T >
    struct CreateUsingNew
    {
        static T* create()
        { return new T; }

        static void destroy(T* instance)
        { delete instance; }
    };

    template < class T >
    struct CreateUsingStatic
    {
        static T* create()
        {
            static char _memory[sizeof(T)];
            return new(&_memory) T;
        }

        static void destroy(T* instance)
        { instance->~T(); }
    };
}

#endif // _CREATIONPOLICIES_H_
