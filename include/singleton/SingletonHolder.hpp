#ifndef _SINGLETONHOLDER_H_
# define _SINGLETONHOLDER_H_

# include "Policies.h"

namespace Uaapi
{
    template
    < class T,
      template < class > class CreationPolicy = CreateUsingNew,
      template < class > class LifetimePolicy = DefaultLifetime,
      template < class > class ThreadingPolicy = NoLocking
      >
    class SingletonHolder
    {
        typedef typename ThreadingPolicy< T* >::Volatile PtrInstanceType;

        static void destroySingleton();

        SingletonHolder();

        static PtrInstanceType _instance;
        static bool _destroyed;

    public:
        static T& instance();
    };

    template
    < class T,
      template < class > class Cp,
      template < class > class Lp,
      template < class > class Tp
      >
    typename SingletonHolder< T, Cp, Lp, Tp >::PtrInstanceType
    SingletonHolder
    < T, Cp, Lp, Tp >::_instance = NULL;

    template
    < class T,
      template < class > class Cp,
      template < class > class Lp,
      template < class > class Tp
      >
    bool SingletonHolder< T, Cp, Lp, Tp >::_destroyed = false;

    template
    < class T,
      template < class > class CreationPolicy,
      template < class > class LifetimePolicy,
      template < class > class ThreadingPolicy
      >
    T& SingletonHolder
    < T,
      CreationPolicy,
      LifetimePolicy,
      ThreadingPolicy >::instance()
    {
        if (!_instance)
        {
            typename ThreadingPolicy<T>::Lock guard;

            if (!_instance)
            {
                if (_destroyed)
                {
                    LifetimePolicy< T >::onDeadReference();
                    _destroyed = false;
                }
                _instance = CreationPolicy< T >::create();
                LifetimePolicy< T >::scheduleCall(&destroySingleton);
            }
        }
        return *_instance;
    }

    template
    < class T,
      template < class > class CreationPolicy,
      template < class > class LifetimePolicy,
      template < class > class ThreadingPolicy
      >
    void SingletonHolder
    < T,
      CreationPolicy,
      LifetimePolicy,
      ThreadingPolicy >::destroySingleton()
    {
        if (!_destroyed)
	{
            CreationPolicy< T >::destroy(_instance);
            _instance = NULL;
            _destroyed = true;
	}
    }
}

#endif // _SINGLETONHOLDER_H_
