
#ifndef AUTUMN_MYBASICTYPE_H
#define AUTUMN_MYBASICTYPE_H

#include <string>
#include <vector>
#include "IBasicType.h"
#include "MyData.h"

using namespace std;

class MyBasicType: public IBasicType{
public:
	void* createValue(const vector<string>& vl, vector<string>::iterator& it){
		if( it != vl.end() && ++it != vl.end()){
			MyData* p = new MyData;
			p->i = atoi((*--it).c_str());
			p->s = (*++it).c_str();
	
			return p;
		}
		return NULL;
	}

	void freeValue(void *p){
		delete (MyData*)p;
	}
};
#endif

