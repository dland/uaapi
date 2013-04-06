#include <iostream>

#include "Logger.h"

int main()
{
    ulog(WARN) << "This is a warning message.";

    Uaapi::Log::Level oldLogLevel = Uaapi::Log::getMinLogLevel();

    Uaapi::Log::setMinLogLevel(Uaapi::Log::L_INFO);
    ulog(INFO) << "Minimum log level was set to "
               << oldLogLevel
               << " and is now set to "
               << Uaapi::Log::getMinLogLevel();

    Uaapi::Log::setMinLogLevel(Uaapi::Log::L_WARN);
    ulog(INFO) << "This is a info message THAT SHOULD NOT BE PRINTED!";

    Uaapi::Log::setMinLogLevel(Uaapi::Log::L_INFO);
    ulog(WARN) << "Log will now be written to \"/tmp/uaapi_logger_test\".";

    Uaapi::Log::logTo("/tmp/uaapi_logger_test",
                      std::ios_base::out | std::ios_base::trunc);

    ulog(WARN) << "This is a warning message.";
    ulog(INFO) << "This is a information message.";
    ulog(DEBUG) << "This is a debug message.";

    Uaapi::Log::logTo(std::cout);

    ulog(INFO) << "We are now back to stdout.";

    Uaapi::Log::failOnError(false);
    ulog(ERROR) << "A error message that does not make the program abort.";

    Uaapi::Log::failOnError(true);
    ulog(ERROR) << "A error message that makes the program abort.";

    std::cout << "This message should not be printed..." << std::endl;
    return 0;
}
