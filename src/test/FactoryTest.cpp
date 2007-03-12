
#include "IProduct.h"
#include "FactoryTest.h"


void FactoryTest::setUp()
{
	this->bf = getBeanFactoryWithXML("FrameworkTest.xml");
}

void FactoryTest::tearDown()
{
	deleteBeanFactory(this->bf);
}

void FactoryTest::testInstanceFacotry()
{
	IProductA* pa = (IProductA*)this->bf->getBean("ProductA1");
	IProductB* pb = (IProductB*)this->bf->getBean("ProductB1");
	IProductC* pc = (IProductC*)this->bf->getBean("ProductC1");
	IProductA* pa2 = (IProductA*)this->bf->getBean("ProductA2");
	
	CPPUNIT_ASSERT(pa->getName().compare("ProductA_1_name_A1") == 0 );
	CPPUNIT_ASSERT(pb->getName().compare("ProductB_1_name_B1") == 0 );
	CPPUNIT_ASSERT(pc->getName().compare("ProductC_1_name_C1") == 0 );
	CPPUNIT_ASSERT(pa2->getName().compare("ProductA_2_name_A2") == 0 );
	this->bf->freeBean(pa);
	this->bf->freeBean(pb);
	this->bf->freeBean(pc);
	this->bf->freeBean(pa2);
}