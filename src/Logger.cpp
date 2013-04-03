#include <fstream>

#include "Logger.h"

namespace Uaapi
{
    LoggerImpl::LoggerImpl()
        : _failOnError(false),
#ifdef _DEBUG
          _minLogLevel(Log::L_INFO),
#else
          _minLogLevel(Log::L_WARN),
#endif
          _ostream(&std::cout),
          _deleteStream(false)
    {}

    LoggerImpl::~LoggerImpl()
    {
        if (_deleteStream)
            delete _ostream;
    }

    void LoggerImpl::logTo(const std::string& fileName,
                           std::ios_base::openmode mode)
    {
        std::ostream* stream = new std::ofstream(fileName.c_str(), mode);
        logTo(*stream);
        _deleteStream = true;
    }

    void LoggerImpl::logTo(std::ostream& stream)
    {
        if (_deleteStream)
            delete _ostream;
        _ostream = &stream;
        _deleteStream = false;
    }
}
