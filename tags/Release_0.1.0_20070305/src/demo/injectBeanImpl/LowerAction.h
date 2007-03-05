#ifndef DEMO_LOWERACTION_H
#define DEMO_LOWERACTION_H

#include <string>
#include "Action.h"

using namespace std;

class LowerAction: public Action{
private:
	string Message;

public:
	const char* getMessage();
	void  setMessage(const char* msg);
	const char* excute(const char* s);
};
#endif

