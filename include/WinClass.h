// -*- c++ -*-
#pragma once

#include <string>

#include "Ug.h"

namespace Uaapi
{
    class _dldecl WinClass
    {
    public:
        static std::string getErrorMess(int errCode);
    };
}
