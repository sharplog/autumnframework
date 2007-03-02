
#ifndef AUTUMN_INITDESTBEAN_H
#define AUTUMN_INITDESTBEAN_H

#include "IBasicTypesBean.h"
#include "SingletonBean.h"

/** class for initialize and destroyable property */
class InitDestBean: public IBasicTypesBean{
private:
	SingletonBean* sb;

public:
	InitDestBean(SingletonBean* p):sb(p){}

	void initialize(){
		sb->setString("Initialize");
	}

	void destroy(){
		sb->setString("Destroy");
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
	virtual string getString()		{ return string(""); }
	virtual char* getCStr()			{ return NULL; }
	virtual unsigned char* getUCStr(){ return NULL; }
};
#endif
