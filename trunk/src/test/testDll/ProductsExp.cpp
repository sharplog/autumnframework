
#include "BeanWrapperMacro.h"
#include "IProduct.h"
#include "IFactory.h"

//product A
AUTUMNBEAN(IProductA)

AUTUMNBEAN_CREATOR()
AUTUMNBEAN_CON_FACTORY_1P(IFactory, createProductA, string)
AUTUMNBEAN_CREATOR_END()

AUTUMNBEAN_END(IProductA)

//product B
AUTUMNBEAN(IProductB)

AUTUMNBEAN_CREATOR()
AUTUMNBEAN_CON_FACTORY_1P(IFactory, createProductB, string)
AUTUMNBEAN_CREATOR_END()

AUTUMNBEAN_END(IProductB)

//product C
AUTUMNBEAN(IProductC)

AUTUMNBEAN_CREATOR()
AUTUMNBEAN_CON_FACTORY(IFactory, createProductC)
AUTUMNBEAN_CREATOR_END()

AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Name, string)
AUTUMNBEAN_SETTER_END()
AUTUMNBEAN_END(IProductC)

