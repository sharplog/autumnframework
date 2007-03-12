
#ifndef AUTUMN_FACTORY_H
#define AUTUMN_FACTORY_H

#include <string>
#include "IProduct.h"

/** Factory interface to test factory instance creating pattern */

class IFactory{
public:
	virtual IProductA* createProductA(string name) = 0;

	virtual IProductB* createProductB(string name) = 0;
	
	virtual IProductC* createProductC() = 0;
};

#endif
