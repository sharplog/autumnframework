
#include "BeanWrapperMacro.h"
#include "LocalBean.h"

AUTUMNBEAN(LocalBean)

AUTUMNBEAN_CONSTRUCTOR(LocalBean)

AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Int, IBasicTypesBean*)
AUTUMNBEAN_PROPERTY(CStr, char*)
AUTUMNBEAN_SETTER_END()

AUTUMNBEAN_END(LocalBean)
AUTUMN_LOCALBEAN(LocalBean)