
#include "BeanWrapperMacro.h"
#include "IProduct.h"
#include "IFactory.h"

AUTUMNBEAN(IProductA)
AUTUMNBEAN_CON_FACTORY_PARAMS(IFactory, createProductA, 1, string)
AUTUMNBEAN_CON_PARAMS_END()
AUTUMNBEAN_END(IProductA)

AUTUMNBEAN(IProductB)
AUTUMNBEAN_CON_FACTORY_PARAMS(IFactory, createProductB, 1, string)
AUTUMNBEAN_CON_PARAMS_END()
AUTUMNBEAN_END(IProductB)

AUTUMNBEAN(IProductC)
AUTUMNBEAN_CON_FACTORY(IFactory, createProductC)
AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Name, string)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(IProductC)

