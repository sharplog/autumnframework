
#ifndef AUTUMN_FACTORIES_H
#define AUTUMN_FACTORIES_H

#include <string>
#include "Products.h"
#include "IFactory.h"

/** Factories to test factory instance creating pattern */

class Factory1 : public IFactory{
public:
	virtual IProductA* createProductA(string name){
		return new ProductA_1(name);
	}

	virtual IProductB* createProductB(string name){
		return new ProductB_1(name);
	}
	
	virtual IProductC* createProductC(){
		return new ProductC_1();
	}
};

class Factory2 : public IFactory{
public:
	virtual IProductA* createProductA(string name){
		return new ProductA_2(name);
	}
	
	virtual IProductB* createProductB(string name){
		return new ProductB_2(name);
	}
	
	virtual IProductC* createProductC(){
		return new ProductC_2();
	}
};

#endif
