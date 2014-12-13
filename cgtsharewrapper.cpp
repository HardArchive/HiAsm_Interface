//STL

//Qt

//Project
#include "cgtsharewrapper.h"

namespace cgt
{
    bool isSelect(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_SELECT;
    }
    
    bool isParent(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_PARENT;
    }
    
    bool isCore(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_CORE;
    }
    
    bool isNoDelete(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_NODELETE;
    }
    
    bool isMulti(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_MULTI;
    }
    
    bool isEdit(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_EDIT;
    }
    
    bool isSystem(ElementFlgs flags)
    {
        return flags & ELEMENT_FLG_IS_SYSTEM;
    }
    
    bool isEditMultiEx(ElementClasses eClass)
    {
        return eClass == CI_EditMultiEx; 
    }
    
    bool isPolyMulti(ElementClasses eClass)
    {
        return eClass == CI_PolyMulti;
    }
    
}

