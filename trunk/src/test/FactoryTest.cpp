
#include "IProduct.h"
#include "FactoryTest.h"

extern char TestConFile[];

void FactoryTest::setUp()
{
	this->bf = getBeanFactoryWithXML(TestConFile);
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
	IProductB* pb2 = (IProductB*)this->bf->getBean("ProductB2");
	
	CPPUNIT_ASSERT(pa->getName().compare("ProductA_1_name_A1") == 0 );
	CPPUNIT_ASSERT(pb->getName().compare("ProductB_1_name_B1") == 0 );
	CPPUNIT_ASSERT(pc->getName().compare("ProductC_1_name_C1") == 0 );
	CPPUNIT_ASSERT(pa2->getName().compare("ProductA_2_name_A2") == 0 );
	CPPUNIT_ASSERT(pb2->getName().compare("ProductB_2_name_B2") == 0 );
	this->bf->freeBean(pa);
	this->bf->freeBean(pb);
	this->bf->freeBean(pc);
	this->bf->freeBean(pa2);
	this->bf->freeBean(pb2);
}

void FactoryTest::testStaticFacotryMethod()
{
	IProductA* pa = (IProductA*)this->bf->getBean("ProductAM");
	IProductA* pb = (IProductA*)this->bf->getBean("ProductBM");
	
	CPPUNIT_ASSERT(pa->getName().compare("ProductA_M_name_AM") == 0 );
	CPPUNIT_ASSERT(pb->getName().compare("ProductB_M_name_BM") == 0 );
	this->bf->freeBean(pa);
	this->bf->freeBean(pb);
}
