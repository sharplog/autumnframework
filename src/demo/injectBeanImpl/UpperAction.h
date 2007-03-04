#ifndef DEMO_UPPERACTION_H
#define DEMO_UPPERACTION_H

#include <string>
#include "Action.h"

using namespace std;

class UpperAction: public Action{
private:
	string Message;

public:
	const char* getMessage();
	void  setMessage(const char* msg);
	const char* excute(const char* s);
};
#endif

