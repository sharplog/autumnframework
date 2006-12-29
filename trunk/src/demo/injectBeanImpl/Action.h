#ifndef DEMO_ACTION_H
#define DEMO_ACTION_H

class Action {
public:
	virtual const char* excute(const char* s) = 0;
};
#endif