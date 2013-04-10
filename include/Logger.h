// -*- c++ -*-
#ifndef _LOGGER_H_
# define _LOGGER_H_

/*
** TODO:
**   - Print timestamp on a log message.
**   - Set a "verbose mode", that would print line and file on a log.
**   - Once the thread part is finished, use a mutex for printing write
**     a "raw" logging method that would'nt use it.
**   - Propose a way to log to a file.
**   - On GNU/Linux, propose a way to also use syslog.
*/

# include <iostream>
# include <sstream>

# include "Singleton.h"

# include "Ug.h"

# define ulog_ERROR() Uaapi::Log().e()
# define ulog_WARN() Uaapi::Log().w()
# define ulog_DEBUG() Uaapi::Log().d()
# define ulog_INFO() Uaapi::Log().i()

# define ulog(log_level) ulog_##log_level()

namespace Uaapi
{
    class LoggerImpl;
    typedef SingletonHolder<LoggerImpl> Logger;

    class Log
    {
    public:
        enum Level
        {
            L_FATAL = 0,
            L_ERROR,
            L_WARN,
            L_DEBUG,
            L_INFO,
            L_NONE
        };

    private:
        std::ostringstream _stream;
        Log::Level _logLevel;

        static const char* _prefixes[];

        _dldecl std::ostream& _log(Log::Level level);

    public:
        _dldecl Log();
        _dldecl ~Log();

        _dldecl std::ostream& e();
        std::ostream& w()
        { return _log(Log::L_WARN); }
        std::ostream& d()
        { return _log(Log::L_DEBUG); }
        std::ostream& i()
        { return _log(Log::L_INFO); }

        /*
        ** We need tranpolines since Uaapi is a dynamic library and
        ** has his own instance of Uaapi::Logger.
        ** Providing direct acces to Uaapi::Logger to the Uaapi user
        ** will result in 2 existing instances of the Singleton...
        */
        _dldecl static void failOnError(bool fail);
        _dldecl static void logTo(
            const std::string& fileName,
            std::ios_base::openmode mode = std::ios_base::out);
        _dldecl static void logTo(std::ostream& stream);
        _dldecl static Log::Level getMinLogLevel();
        _dldecl static void setMinLogLevel(Log::Level level);
    };

    class _dldecl LoggerImpl
    {
    private:
        bool _failOnError;
        Log::Level _minLogLevel;
        std::ostream* _ostream;
        bool _deleteStream;

    public:
        LoggerImpl();
        ~LoggerImpl();

        bool failOnError()
        { return _failOnError; }
        void failOnError(bool fail)
        { _failOnError = fail; }

        // Log to fileName
        void logTo(
            const std::string& fileName,
            std::ios_base::openmode mode = std::ios_base::out);
        // Log to a given std::ostream
        void logTo(std::ostream& stream);

        void setMinLogLevel(Log::Level level)
        { _minLogLevel = level; }
        Log::Level getMinLogLevel()
        { return _minLogLevel; }

        std::ostream& getOutStream()
        { return *_ostream; }
    };
}

#endif  // _LOGGER_H_
