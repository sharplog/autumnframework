
#ifndef AUTUMN_MYTYPEBEAN_H
#define AUTUMN_MYTYPEBEAN_H

#include "MyData.h"
#include "IBasicTypesBean.h"

class MyTypeBean: public IBasicTypesBean{
private:
	int mInt;
	string mString;
	
public:
	BeanTypeBean(){
		this->mInt = 0;
	}
	
	//setter
	void setMyData(MyData* pm){
		this->mInt = pm->i;
		this->mString = pm->s;
	}
	
	//getter
	virtual char getChar()			{ return ' '; }
	virtual unsigned char getUChar(){ return ' '; }
	virtual short getShort()		{ return 0; }
	virtual unsigned short getUShort(){ return 0; }
	virtual int getInt()			{ return this->mInt; }
	virtual unsigned int getUInt()	{ return 0; }
	virtual long getLong()			{ return 0; }
	virtual unsigned long getULong(){ return 0; }
	virtual float getFloat()		{ return 0; }
	virtual double getDouble()		{ return 0; }
	virtual string getString()		{ return this->mString; }
	virtual char* getCStr()			{ return NULL; }
	virtual unsigned char* getUCStr(){ return NULL; }
};
#endif