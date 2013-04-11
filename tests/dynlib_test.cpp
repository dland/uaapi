#include "Dynlib.h"
#include "Logger.h"
#include "Exception.h"

#if defined(POSIX)
# define LIBRARY_NAME "m"
#elif defined(WIN32)
# define LIBRARY_NAME "msvcrt"
#endif

int main()
{
    try
    {
        Uaapi::DynamicLibrary* libm =
            Uaapi::DlLoader::instance().load(LIBRARY_NAME);

        ulog(INFO) << "Loaded library " << libm->getName();

        if (!libm->hasSymbol("fabs"))
            ulog(ERROR) << "Missing \"fabs\" symbol";
        else
            ulog(INFO) << "Symbol \"fabs\" is present";

        if (!libm->hasSymbol("foobar"))
            ulog(INFO) << "Missing \"foobar\" symbol";
        else
            ulog(ERROR) << "Symbol \"foobar\" is present";

        double (*fabs_func)(double);

        fabs_func = libm->getSymbol< double (*)(double) >("fabs");
        ulog(INFO) << "fabs(42.2) = " << fabs_func(42.2);
        ulog(INFO) << "fabs(-42.2) = " << fabs_func(-42.2);
    }
    catch (Uaapi::Exception& e)
    {
        ulog(ERROR) << "Exception cought: " << e.what();
    }
    return 0;
}
