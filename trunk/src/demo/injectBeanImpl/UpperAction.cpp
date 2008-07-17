
#include <iostream>
#include "UpperAction.h"

using namespace std;

const char* UpperAction::getMessage()
{
	return this->Message.c_str();
}

void  UpperAction::setMessage(const char* msg)
{
	this->Message = msg;
}

string UpperAction::excute(const char* s)
{
	return string("Upper: ") + this->getMessage() + "," + s;
	//cout<<string("Upper: ") + this->getMessage() + ", " + s<<endl;;
	//return "Upper";
}
