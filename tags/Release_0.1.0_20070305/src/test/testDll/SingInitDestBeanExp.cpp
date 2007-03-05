
#include "BeanWrapperMacro.h"
#include "SingletonBean.h"
#include "InitDestBean.h"
#include "SelfManagedBean.h"

AUTUMNBEAN(SingletonBean)
AUTUMNBEAN_CONSTRUCTOR(SingletonBean)
AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(String, string)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(SingletonBean)

AUTUMNBEAN(InitDestBean)
AUTUMNBEAN_CON_PARAMS(InitDestBean, 1, SingletonBean*)
AUTUMNBEAN_CON_PARAMS_END()
AUTUMNBEAN_INIT(initialize)
AUTUMNBEAN_DESTROY(destroy)
AUTUMNBEAN_END(InitDestBean)

AUTUMNBEAN(SelfManagedBean)
AUTUMNBEAN_CON_PARAMS(SelfManagedBean, 1, SingletonBean*)
AUTUMNBEAN_CON_PARAMS_END()
AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(CStr, char*)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(SelfManagedBean)
