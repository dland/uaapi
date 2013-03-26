#ifndef _LIFETIMEPOLICIES_H_
# define _LIFETIMEPOLICIES_H_

# include <stdexcept>
# include <cstdlib>

namespace Uaapi
{
    template < class T >
    struct DefaultLifetime
    {
        static void scheduleCall(void (*destroyFunc)())
        { std::atexit(destroyFunc); }

        // Should not happen
        static void onDeadReference()
        { throw std::logic_error("Dead reference"); }
    };

    template < class T >
    struct NoDestroy
    {
        static void scheduleCall(void (*destroyFunc)())
        { (void)destroyFunc; }

        // Never happens, instance is never destroyed
        static void onDeadReference() {}
    };
}

#endif // _LIFETIMEPOLICIES_H_
