
#include "TypeInjectionTest.h"
#include "FactoryTest.h"

#ifdef _DEBUG
char TestConFile[] = "FrameworkTest_D.xml";
#else
char TestConFile[] = "FrameworkTest.xml";
#endif

int main()
{
	TypeInjectionTest test1;
	FactoryTest	test2;

	test1.excuteTest();
	test2.excuteTest();

	return 0;
}
