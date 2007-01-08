
#ifndef AUTUMN_BASICTYPESBEAN_H
#define AUTUMN_BASICTYPESBEAN_H

#include <string>
#include "IBasicTypesBean.h"

using namespace std;

class BasicTypesBean: public IBasicTypesBean{
private:
	char			mChar;
	unsigned char	mUChar;
	short			mShort;
	unsigned short	mUShort;
	int				mInt;
	unsigned int	mUInt;
	long			mLong;
	unsigned long	mULong;
	float			mFloat;
	double			mDouble;
	string			mString;
	char*			mCStr;
	unsigned char*	mUCStr;
	
public:
	//constructor
	BasicTypesBean(){}
	BasicTypesBean(	char			pChar,
					unsigned char	pUChar,
					short			pShort,
					unsigned short	pUShort,
					int				pInt,
					unsigned int	pUInt,
					long			pLong,
					unsigned long	pULong,
					float			pFloat,
					double			pDouble,
					string			pString,
					char*			pCStr,
					unsigned char*	pUCStr):
					mChar(pChar),
					mUChar(pUChar),
					mShort(pShort),
					mUShort(pUShort),
					mInt(pInt),
					mUInt(pUInt),
					mLong(pLong),
					mULong(pULong),
					mFloat(pFloat),
					mDouble(pDouble),
					mString(pString),
					mCStr(pCStr),
					mUCStr(pUCStr){}
					

	//setter
	void setChar(char p)			{ this->mChar = p; }
	void setUChar(unsigned char p)	{ this->mUChar = p; }
	void setShort(short p)			{ this->mShort = p; }
	void setUShort(unsigned short p){ this->mUShort = p; }
	void setInt(int p)				{ this->mInt = p; }
	void setUInt(unsigned int p)	{ this->mUInt = p; }
	void setLong(long p)			{ this->mLong = p; }
	void setULong(unsigned long p)	{ this->mULong = p; }
	void setFloat(float p)			{ this->mFloat = p; }
	void setDouble(double p)		{ this->mDouble = p; }
	void setString(string p)		{ this->mString = p; }
	void setCStr(char* p)			{ this->mCStr = p; }
	void setUCStr(unsigned char* p)	{ this->mUCStr = p; }

	//setter using pointer
	void setInt(int* p)				{this->mInt = *p; }
	void setCStr(char** p)			{this->mCStr = *p; }

	//getter
	virtual char getChar()			{ return this->mChar; }
	virtual unsigned char getUChar(){ return this->mUChar; }
	virtual short getShort()		{ return this->mShort; }
	virtual unsigned short getUShort(){ return this->mUShort; }
	virtual int getInt()			{ return this->mInt; }
	virtual unsigned int getUInt()	{ return this->mUInt; }
	virtual long getLong()			{ return this->mLong; }
	virtual unsigned long getULong(){ return this->mULong; }
	virtual float getFloat()		{ return this->mFloat; }
	virtual double getDouble()		{ return this->mDouble; }
	virtual string getString()		{ return this->mString; }
	virtual char* getCStr()			{ return this->mCStr; }
	virtual unsigned char* getUCStr(){ return this->mUCStr; }
};
#endif
