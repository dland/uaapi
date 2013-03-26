#ifndef _THREADINGPOLICIES_H_
# define _THREADINGPOLICIES_H_

// Thread part of the Uaapi not present yet

namespace Uaapi
{
    template <class T>
    struct NoLocking
    {
        typedef T Volatile;

        struct Lock
        { Lock() {} };
    };
}

#endif // _THREADINGPOLICIES_H_
