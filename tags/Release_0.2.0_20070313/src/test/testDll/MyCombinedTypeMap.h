
#ifndef AUTUMN_MYCOMBINEDTYPEMAP_H
#define AUTUMN_MYCOMBINEDTYPEMAP_H

#include <cstdlib>
#include <map>
#include "ICombinedType.h"

using namespace std;

class MyCombinedTypeMap: public ICombinedType{
public:
	void* createValue(const vector<string>& vl, string basicType, vector<string>::iterator& it){
		//如果在这儿解析出两个基本类型，利用父类的方法去构造基本类型，但是，没法声明
		//这个map。如此构造，还是一个基本类型。
		map<string, int>* p = new map<string, int>;
		for( ; it!=vl.end(); it++){
			string s = *it++;
			int i;
			if( it != vl.end() ) i = atoi(*it++);
			p->insert(make_pair(name, i));
		}
		return (void*)p;
	}

	void free
};

#endif
