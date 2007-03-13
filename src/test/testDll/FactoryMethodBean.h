
#ifndef AUTUMN_FACTORYMETHODBEAN_H
#define AUTUMN_FACTORYMETHODBEAN_H

#include "IProduct.h"

class ProductA_M: IProductA{
	string Name;
	
	static int RefNum;
	static ProductA_M* instance;
	ProductA_M(string name): Name(name){}
public:
	static ProductA_M* getInstance(string name){
		if( ProductA_M::instance == NULL ){
			ProductA_M::instance = new ProductA_M(name);
			ProductA_M::RefNum = 1;
		}
		else{
			ProductA_M::RefNum ++;
		}
		return ProductA_M::instance;
	}

	static void deleteInstance(ProductA_M* p){
		ProductA_M::RefNum--;
		if( ProductA_M::RefNum == 0){
			delete ProductA_M::instance;
			ProductA_M::instance = NULL;
		}
	}
	
	virtual string getName(){
		return "ProductA_M_" + this->Name;
	}

};

class ProductB_M: IProductA{
	static int RefNum;
	static ProductB_M* instance;
	ProductB_M(){}
public:
	static ProductB_M* getInstance(){
		if( ProductB_M::instance == NULL ){
			ProductB_M::instance = new ProductB_M();
			ProductB_M::RefNum = 1;
		}
		else{
			ProductB_M::RefNum ++;
		}
		return ProductB_M::instance;
	}
	
	static void deleteInstance(ProductB_M* p){
		ProductB_M::RefNum--;
		if( ProductB_M::RefNum == 0){
			delete ProductB_M::instance;
			ProductB_M::instance = NULL;
		}
	}
	
	virtual string getName(){
		return "ProductB_M_name_BM";
	}
	
};

#endif
