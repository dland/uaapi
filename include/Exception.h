// -*- c++ -*-
#ifndef _EXCEPTION_H_
# define _EXCEPTION_H_

# include <exception>
# include <string>

namespace Uaapi
{
    class Exception : public std::exception
    {
        std::string _errStr;

    public:
        Exception(const std::string& errStr) throw()
            : _errStr(errStr)
        {}

        // Do nothing
        virtual ~Exception() throw() {}

        virtual const char* what() const throw()
        { return _errStr.c_str(); }
    };

    class FatalError : public Exception
    {
    public:
        FatalError(const std::string& errStr) throw()
            : Exception(errStr)
        {}
    };

    class RuntimeError : public Exception
    {
    public:
        RuntimeError(const std::string& errStr) throw()
            : Exception(errStr)
        {}
    };
}

#endif // _EXCEPTION_H_
