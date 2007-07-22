
#ifndef AUTUMN_SINGLETONBEAN_H
#define AUTUMN_SINGLETONBEAN_H

#include "IBasicTypesBean.h"

using namespace std;

/** class for testing singleton property */
class SingletonBean: public IBasicTypesBean{
private:
	string mString;

public:
	//setter
	virtual void setString(string s){
		this->mString = s;
	}
	
	//getter
	virtual char getChar()			{ return ' '; }
	virtual unsigned char getUChar(){ return ' '; }
	virtual short getShort()		{ return 0; }
	virtual unsigned short getUShort(){ return 0; }
	virtual int getInt()			{ return 0; }
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
