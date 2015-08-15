#pragma once

//Project
#include "CGTShare.h"

//STL

//Qt

namespace cgt
{
bool isSelect(const ElementFlgs &flags);
bool isParent(const ElementFlgs &flags);
bool isCore(const ElementFlgs &flags);
bool isNoDelete(const ElementFlgs &flags);
bool isMulti(const ElementFlgs &flags);
bool isEdit(const ElementFlgs &flags);
bool isSystem(const ElementFlgs &flags);


bool isEditMultiEx(const ClassesElements &eClass);
bool isPolyMulti(const ClassesElements &eClass);
}

namespace cgt
{
void saveOriginalCgt(PCodeGenTools cgt);
PCodeGenTools getOriginalCgt();
PCodeGenTools getProxyCgt();
}
