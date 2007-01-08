
#include <iostream>
#include <exception>
#include "Action.h"
#include "IBeanFactory.h"

using namespace std;

void main(int argc, char* argv[])
{
	try{
		IBeanFactory* bf = IBeanFactory::getInstanceWithXML(argv[1]);
		Action* pa = (Action*)bf->getBean("TheAction");
		cout<<pa->excute("Vicent")<<endl;
		bf->freeBean(pa);
		
		cout<<"OK!"<<endl;
	}catch (exception* e ) {
		cout<<"Exception: "<<e->what()<<endl;
		delete e;
	}
}