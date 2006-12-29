
#include "BeanWrapperMacro.h"
#include "LowerAction.h"
#include "UpperAction.h"


AUTUMNBEAN(LowerAction)
AUTUMNBEAN_CONSTRUCTOR(LowerAction)
AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Message, char*)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(LowerAction)

AUTUMNBEAN(UpperAction)
AUTUMNBEAN_CONSTRUCTOR(UpperAction)
AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Message, char*)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(UpperAction)

