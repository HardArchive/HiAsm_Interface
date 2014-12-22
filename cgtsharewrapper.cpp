//STL

//Qt

//Project
#include "cgtsharewrapper.h"

namespace cgt {

bool isSelect(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_SELECT;
}

bool isParent(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_PARENT;
}

bool isCore(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_CORE;
}

bool isNoDelete(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_NODELETE;
}

bool isMulti(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_MULTI;
}

bool isEdit(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_EDIT;
}

bool isSystem(const ElementFlgs& flags)
{
    return flags & ELEMENT_FLG_IS_SYSTEM;
}

bool isEditMultiEx(const ElementClasses& eClass)
{
    return eClass == CI_EditMultiEx;
}

bool isPolyMulti(const ElementClasses& eClass)
{
    return eClass == CI_PolyMulti;
}
}
