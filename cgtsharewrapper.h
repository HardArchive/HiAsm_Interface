#ifndef CGTSHAREWRAPPER_H
#define CGTSHAREWRAPPER_H

//STL

//Qt

//Project
#include "CGTShare.h"

namespace cgt
{
    bool isSelect(const ElementFlgs &flags);
    bool isParent(const ElementFlgs &flags);
    bool isCore(const ElementFlgs &flags);
    bool isNoDelete(const ElementFlgs &flags);
    bool isMulti(const ElementFlgs &flags);
    bool isEdit(const ElementFlgs &flags);
    bool isSystem(const ElementFlgs &flags);

    bool isEditMultiEx(const ElementClasses &eClass);
    bool isPolyMulti(const ElementClasses &eClass);
}

namespace cgt
{
    void saveOriginalCgt(PCodeGenTools cgt);
    PCodeGenTools getOriginalCgt();
    PCodeGenTools getProxyCgt();
}

#endif // CGTSHAREWRAPPER_H
