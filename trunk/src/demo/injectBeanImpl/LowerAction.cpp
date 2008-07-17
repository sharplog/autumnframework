
#include <iostream>
#include "LowerAction.h"

using namespace std;

const char* LowerAction::getMessage()
{
	return this->Message.c_str();
}

void  LowerAction::setMessage(const char* msg)
{
	this->Message = msg;
}

string LowerAction::excute(const char* s)
{
	return string("Lower: ") + this->getMessage() + "," + s;
	//cout<<string("Lower: ") + this->getMessage() + ", " + s<<endl;;
	//return "Lower";
}
