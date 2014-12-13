#ifndef CGTSHAREWRAPPER_H
#define CGTSHAREWRAPPER_H

//STL

//Qt

//Project
#include "CGTShare.h"

namespace cgt
{
    bool isSelect(ElementFlgs flags);
    bool isParent(ElementFlgs flags);
    bool isCore(ElementFlgs flags);
    bool isNoDelete(ElementFlgs flags);
    bool isMulti(ElementFlgs flags);
    bool isEdit(ElementFlgs flags);
    bool isSystem(ElementFlgs flags);

    bool isEditMultiEx(ElementClasses eClass);
    bool isPolyMulti(ElementClasses eClass);
}



#endif // CGTSHAREWRAPPER_H
