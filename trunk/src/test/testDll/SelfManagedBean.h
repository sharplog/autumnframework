
#ifndef AUTUMN_SELFMANAGEDBEAN_H
#define AUTUMN_SELFMANAGEDBEAN_H

#include "IBasicTypesBean.h"
#include "SingletonBean.h"

/** class for self-managed property */
class SelfManagedBean: public IBasicTypesBean{
private:
	SingletonBean* sb;
	char* CStr;
	
public:
	SelfManagedBean(SingletonBean* p):sb(p){}
	~SelfManagedBean(){ 
		//Can't self-Managed
		//delete this->sb;
		//delete this->CStr;
	}

	//setter
	void setCStr(char* s){this->CStr = s;}
	
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
	virtual string getString()		{ return string(""); }
	virtual char* getCStr()			{ return NULL; }
	virtual unsigned char* getUCStr(){ return NULL; }
};
#endif
