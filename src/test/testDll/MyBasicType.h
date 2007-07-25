
#ifndef AUTUMN_MYBASICTYPE_H
#define AUTUMN_MYBASICTYPE_H

#include <string>
#include <vector>
#include "IAutumnType.h"
#include "MyData.h"

using namespace std;
using namespace Autumn;

class MyBasicType: public IAutumnType{
public:
	void* createValue(const string& type, const vector<string>& vl, vector<string>::iterator& it)const{
		if( it != vl.end() && ++it != vl.end()){
			MyData* p = new MyData;
			p->i = atoi((*--it).c_str());
			p->s = (*++it).c_str();
	
			return p;
		}
		return NULL;
	}

	void freeValue(void *p, const string& type){
		delete (MyData*)p;
	}

	void freeSelfSpace(void *p){
		delete (MyData*)p;
	}

	bool isThisType(const string& type) const {
		return type.compare("MyData") == 0;
	}
};
#endif

