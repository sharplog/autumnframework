
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

int main(int argc, char* argv[])
{
	try{
		Autumn::IBeanFactory* bf;
		if( argc > 1 )
			bf = Autumn::getBeanFactoryWithXML(argv[1]);
		else
			bf = Autumn::getBeanFactoryWithXML(xmlFile);

		Action* pa = (Action*)bf->getBean("TheAction");
		cout<<pa->excute("Vicent")<<endl;
		bf->freeBean(pa);
		
		Autumn::deleteBeanFactory(bf);
		cout<<"OK!"<<endl;
	}catch (const exception& e ) {
		cout<<"Exception: "<<e.what()<<endl;
	}
	return 0;
}

