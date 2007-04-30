
#ifndef AUTUMN_MULTIINHERITEBEAN_H
#define AUTUMN_MULTIINHERITEBEAN_H

#include "IMultiBase.h"


// Multi_Base1 and Multi_Base2 are not used now.
class Multi_Base1:public IBase1{
	int i, j, k;
public:
	int f1(){ return 1;}	
};

class Multi_Base2:public IBase2{
	char a, b, c;
public:
	int f2(){ return 2;}	
};

class Multi_Bean: public IBase2, IBase1{
public:
	int f1(){ return 1;}	
	int f2(){ return 2;}	

};

#endif