#ifndef DEMO_ACTION_H
#define DEMO_ACTION_H

#include <string>

class Action {
public:
	virtual std::string excute(const char* s) = 0;
};
#endif

