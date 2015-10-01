#pragma once

//Project
#include "CGTShare.h"

//STL

//Qt

namespace ProxyCgt
{
    void saveOriginalCgt(PCodeGenTools cgt);
    PCodeGenTools getOriginalCgt();
    PCodeGenTools getProxyCgt();
}
