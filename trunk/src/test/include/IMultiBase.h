
#ifndef AUTUMN_IMULTIBASE_H
#define AUTUMN_IMULTIBASE_H


class IBase1{
	char c;
public:
	virtual int f1()=0;
};

class IBase2{
	int i;
public:
	virtual int f2()=0;
};

class IBase3{
	long l;
public:
	virtual int f3()=0;
};

class IMulti_Bean{
public:
	virtual int getB1()=0;
	virtual int getB2()=0;
};

#endif

