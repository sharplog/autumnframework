
#ifndef AUTUMN_IPRODUCT_H
#define AUTUMN_IPRODUCT_H
#include <string>

using namespace std;

/** Product interface to test factory instance creating pattern*/

class IProductA{
public:
	virtual string getName() = 0;
};

class IProductB{
public:
	virtual string getName() = 0;
};

class IProductC{
public:
	virtual void setName(string name) = 0;
	virtual string getName() = 0;
};

#endif
