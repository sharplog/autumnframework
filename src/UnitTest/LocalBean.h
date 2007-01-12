
#ifndef AUTUMN_LOCALBEAN_H
#define AUTUMN_LOCALBEAN_H

#include "BasicTypesBean.h"

class LocalBean: public IBasicTypesBean{
private:
	int mInt;
	char* mCStr;
	
public:
	LocalBean(){
		this->mInt = 0;
		this->mCStr = NULL;
	}

	//setter
	void setInt(IBasicTypesBean* pb){ 
		this->mInt = pb->getInt(); 
	}
	void setCStr(char* s){ this->mCStr = s; }
	
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
	virtual string getString()		{ return string(""); }
	virtual char* getCStr()			{ return this->mCStr; }
	virtual unsigned char* getUCStr(){ return NULL; }
};
#endif
