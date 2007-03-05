
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
		MyData* p = new MyData;
		p->i = atoi(vl[0].c_str());
		p->s = vl[1];

		return p;
	}

	void freeValue(void *p){
		delete (MyData*)p;
	}
};
#endif

