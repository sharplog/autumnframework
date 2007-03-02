
#include "BeanWrapperMacro.h"
#include "BeanTypeBean.h"

AUTUMNBEAN(BeanTypeBean)

AUTUMNBEAN_CONSTRUCTOR(BeanTypeBean)

AUTUMNBEAN_CON_PARAMS(BeanTypeBean, 1, BasicTypesBean*)
AUTUMNBEAN_CON_PARAMS_END()

AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Int, BasicTypesBean*)
AUTUMNBEAN_PROPERTY(CStr, BasicTypesBean)
AUTUMNBEAN_SETTER_END()

AUTUMNBEAN_END(BeanTypeBean)
