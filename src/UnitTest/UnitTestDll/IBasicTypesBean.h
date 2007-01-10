
#ifndef AUTUMN_IBASICTYPESBEAN_H
#define AUTUMN_IBASICTYPESBEAN_H

class IBasicTypesBean{
public:
	/* Basic types
	const string charBT("char");
	const string ucharBT("unsignedchar");
	const string shortBT("short");
	const string ushortBT("unsignedshort");
	const string intBT("int");
	const string uintBT("unsignedint");
	const string longBT("long");
	const string ulongBT("unsignedlong");
	const string floatBT("float");
	const string doubleBT("double");
	const string stringBT("string");
	const string cstrBT("char*");
	const string ucstrBT("unsignedchar*");
	*/
	virtual void setString(string s){}
	
	virtual char getChar() = 0;
	virtual unsigned char getUChar() = 0;
	virtual short getShort() = 0;
	virtual unsigned short getUShort() = 0;
	virtual int getInt() = 0;
	virtual unsigned int getUInt() = 0;
	virtual long getLong() = 0;
	virtual unsigned long getULong() = 0;
	virtual float getFloat() = 0;
	virtual double getDouble() = 0;
	virtual string getString() = 0;
	virtual char* getCStr() = 0;
	virtual unsigned char* getUCStr() = 0;
		
};
#endif
