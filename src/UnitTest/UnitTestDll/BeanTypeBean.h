
#ifndef AUTUMN_BEANTYPEBEAN_H
#define AUTUMN_BEANTYPEBEAN_H

#include "IBasicTypesBean.h"
#include "BasicTypesBean.h"

class BeanTypeBean: public IBasicTypesBean{
private:
	int mInt;
	char* mCStr;

public:
	BeanTypeBean(){
		this->mInt = 0;
		this->mCStr = NULL;
	}
	BeanTypeBean(BasicTypesBean* pb){
		this->mInt = pb->getInt();
		char* p = pb->getCStr();
		this->mCStr = new char[strlen(p) + 1];
		strcpy(this->mCStr, p);
	}
	~BeanTypeBean(){
		delete this->mCStr;
	}

	//setter
	void setInt(BasicTypesBean* pb){
		this->mInt = pb->getInt();
	}

	void setCStr(BasicTypesBean b){
		char* p = b.getCStr();
		if( this->mCStr ) delete this->mCStr;
		this->mCStr = new char[strlen(p) + 1];
		strcpy(this->mCStr, p);
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
	virtual string getString()		{ return string(""); }
	virtual char* getCStr()			{ return this->mCStr; }
	virtual unsigned char* getUCStr(){ return NULL; }
	
};
#endif
