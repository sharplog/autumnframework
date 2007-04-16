
#include "BeanWrapperMacro.h"
#include "IProduct.h"

//product A
AUTUMNBEAN(IProductA)
AUTUMNBEAN_END(IProductA)

//product B
AUTUMNBEAN(IProductB)
AUTUMNBEAN_END(IProductB)

//product C
AUTUMNBEAN(IProductC)
AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Name, string)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(IProductC)

