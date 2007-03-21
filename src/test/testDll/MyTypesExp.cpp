
#include "BeanWrapperMacro.h"
#include "MyBasicType.h"
#include "MyTypeBean.h"

// MyBasicType
AUTUMNTYPE(MyBasicType)

// MyTypeBean
AUTUMNBEAN(MyTypeBean)
AUTUMNBEAN_CREATOR()
AUTUMNBEAN_CONSTRUCTOR(MyTypeBean)
AUTUMNBEAN_CREATOR_END()

AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(MyData, MyData*)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(MyTypeBean)
