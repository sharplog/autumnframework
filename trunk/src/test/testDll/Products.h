
#ifndef AUTUMN_PRODUCTS_H
#define AUTUMN_PRODUCTS_H

#include <string>
#include "IProduct.h"

/** Products to test factory instance creating pattern*/

class ProductA_1 : public IProductA{
	string Name;
	string Rtn;
public:
	ProductA_1(string name): Name(name){}

	virtual string getName(){
		return "ProductA_1_" + this->Name;
	}
};

class ProductA_2 : public IProductA{
	string Name;
public:
	ProductA_2(string name): Name(name){}
	
	virtual string getName(){
		return "ProductA_2_" + this->Name;
	}
};


class ProductB_1 : public IProductB{
	string Name;
public:
	ProductB_1(string name): Name(name){}
	
	virtual string getName(){
		return "ProductB_1_" + this->Name;
	}
};

class ProductB_2 : public IProductB{
	string Name;
public:
	ProductB_2(string name): Name(name){}
	
	virtual string getName(){
		return "ProductB_2_" + this->Name;
	}
};

class ProductC_1 : public IProductC{
	string Name;
public:
	virtual void setName(string name){ this->Name = name; }
	
	virtual string getName(){
		return "ProductC_1_" + this->Name;
	}
};

class ProductC_2 : public IProductC{
	string Name;
public:
	virtual void setName(string name){ this->Name = name; }
	
	virtual string getName(){
		return "ProductC_2_" + this->Name;
	}
};

#endif
