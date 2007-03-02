
#include <iostream>
#include <exception>
#include "Action.h"
#include "IBeanFactory.h"

using namespace std;

#ifdef _DEBUG
const char xmlFile[] = "autumnDemo_D.xml";
#else
const char xmlFile[] = "autumnDemo.xml";
#endif

void main()
{
	try{
		IBeanFactory* bf = getBeanFactoryWithXML(xmlFile);
		Action* pa = (Action*)bf->getBean("TheAction");
		cout<<pa->excute("Vicent")<<endl;
		bf->freeBean(pa);
		
		deleteBeanFactory(bf);
		cout<<"OK!"<<endl;
	}catch (exception* e ) {
		cout<<"Exception: "<<e->what()<<endl;
		delete e;
	}
}