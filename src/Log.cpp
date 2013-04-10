#include "Logger.h"

namespace Uaapi
{
    const char* Log::_prefixes[] = {
        "FATAL ERROR",
        "ERROR",
        "Warning",
        "Debug",
        "Information",
        ""
    };

    Log::Log()
        : _stream(std::ostringstream::out),
          _logLevel(Log::L_NONE)
    {}

    Log::~Log()
    {
        _stream << std::endl;
        {
            std::string mess = _stream.str();

            Logger::instance().getOutStream() << mess;
        }

        if (_logLevel == Log::L_FATAL)
        {
            // Explicitly call th stream destructor so it releases its
            // resources
            _stream.std::ostringstream::~ostringstream();
            ::exit(1);
        }
    }

    std::ostream& Log::_log(Log::Level level)
    {
        _logLevel = level;

        _stream << "[" << _prefixes[level] << "] ";
        return _stream;
    }

    std::ostream& Log::e()
    {
        return _log(Logger::instance().failOnError() ?
                    Log::L_FATAL : Log::L_ERROR);
    }

    void Log::failOnError(bool fail)
    { Uaapi::Logger::instance().failOnError(fail); }

    void Log::logTo(const std::string& fileName,
                    std::ios_base::openmode mode)
    { Uaapi::Logger::instance().logTo(fileName, mode); }

    void Log::logTo(std::ostream& stream)
    { Uaapi::Logger::instance().logTo(stream); }

    void Log::setMinLogLevel(Log::Level level)
    { Uaapi::Logger::instance().setMinLogLevel(level); }

    Log::Level Log::getMinLogLevel()
    { return Uaapi::Logger::instance().getMinLogLevel(); }
}
