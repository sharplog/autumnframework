
#include <cmath>
#include "TypeInjectionTest.h"
#include "IBasicTypesBean.h"
#include "IMultiBase.h"

void TypeInjectionTest::setUp()
{
	this->bf = getBeanFactoryWithXML("FrameworkTest.xml");
}

void TypeInjectionTest::tearDown()
{
	deleteBeanFactory(this->bf);
}

void TypeInjectionTest::testBasicType()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("BasicTypesBean1");

	CPPUNIT_ASSERT(b->getChar() == 'c');
	CPPUNIT_ASSERT(b->getUChar() == 'u');
	CPPUNIT_ASSERT(b->getShort() == 123);
	CPPUNIT_ASSERT(b->getUShort() == 65530);
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(b->getUInt() == 77777);
	CPPUNIT_ASSERT(b->getLong() == 8000000);
	CPPUNIT_ASSERT(b->getULong() == 4294967295);
	CPPUNIT_ASSERT( fabs(b->getFloat() - 1.234567) < 1e-7);
	CPPUNIT_ASSERT( fabs(b->getDouble() - 1.23456789012345) < 1e-15);
	CPPUNIT_ASSERT(b->getString().compare("hello, String") == 0 );
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr") == 0);
	CPPUNIT_ASSERT(strcmp((const char*)b->getUCStr(), "hello, UCStr") == 0);
	this->bf->freeBean(b);

	b = (IBasicTypesBean*)this->bf->getBean("BasicTypesBean2");
	CPPUNIT_ASSERT(b->getChar() == 'c');
	CPPUNIT_ASSERT(b->getUChar() == 'u');
	CPPUNIT_ASSERT(b->getShort() == 123);
	CPPUNIT_ASSERT(b->getUShort() == 65530);
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(b->getUInt() == 77777);
	CPPUNIT_ASSERT(b->getLong() == 8000000);
	CPPUNIT_ASSERT(b->getULong() == 4294967295);
	CPPUNIT_ASSERT( fabs(b->getFloat() - 1.234567) < 1e-7);
	CPPUNIT_ASSERT( fabs(b->getDouble() - 1.23456789012345) < 1e-15);
	CPPUNIT_ASSERT(b->getString().compare("hello, String") == 0 );
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr") == 0);
	CPPUNIT_ASSERT(strcmp((const char*)b->getUCStr(), "hello, UCStr") == 0);
	this->bf->freeBean(b);
}

void TypeInjectionTest::testCombinedType()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("BasicTypesBean3");

	//test pointer type
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr") == 0);
	this->bf->freeBean(b);
}

void TypeInjectionTest::testBeanType()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("BeanTypeBean1");
	
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr for bean4") == 0);
	this->bf->freeBean(b);

	b = (IBasicTypesBean*)this->bf->getBean("BeanTypeBean2");
	
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr") == 0);

	this->bf->freeBean(b);
}

void TypeInjectionTest::testSingleton()
{
	IBasicTypesBean* b1 = (IBasicTypesBean*)this->bf->getBean("NotSingleton1");
	IBasicTypesBean* b2 = (IBasicTypesBean*)this->bf->getBean("NotSingleton1");
	
	b1->setString("I'm changed");
	CPPUNIT_ASSERT(b1->getString().compare("I'm changed") == 0);
	CPPUNIT_ASSERT(b2->getString().compare("Not Singleton") == 0);
	this->bf->freeBean(b1);
	this->bf->freeBean(b2);
	
	b1 = (IBasicTypesBean*)this->bf->getBean("SingletonBean1");
	b2 = (IBasicTypesBean*)this->bf->getBean("SingletonBean1");

	b1->setString("I'm changed");
	CPPUNIT_ASSERT(b1->getString().compare("I'm changed") == 0);
	CPPUNIT_ASSERT(b2->getString().compare("I'm changed") == 0);
	this->bf->freeBean(b1);
	this->bf->freeBean(b2);
}

void TypeInjectionTest::testInitDestroyable()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("InitDestBean1");
	IBasicTypesBean* b1 = (IBasicTypesBean*)this->bf->getBean("SingletonBean1");

	CPPUNIT_ASSERT(b1->getString().compare("Initialize") == 0);
	this->bf->freeBean(b);
	CPPUNIT_ASSERT(b1->getString().compare("Destroy") == 0);
}

void TypeInjectionTest::testSelfManage()
{
	//can't self managed
	//IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("SelfManagedBean1");
	//CPPUNIT_ASSERT_NO_THROW(this->bf->freeBean(b));
}

void TypeInjectionTest::testInjectFromLibElse()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("BeanTypeBean5");
	
	CPPUNIT_ASSERT(b->getInt() == 70021);
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr2-1") == 0);
	this->bf->freeBean(b);
}

void TypeInjectionTest::testLocalBean()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("LocalBean1");
	
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, Local Bean") == 0);
	this->bf->freeBean(b);
}

void TypeInjectionTest::testCustomizedType()
{
	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("MyTypeBean1");
	
	CPPUNIT_ASSERT(b->getInt() == 100);
	CPPUNIT_ASSERT(b->getString().compare("Hi, MyData!") == 0);
	this->bf->freeBean(b);
}

void TypeInjectionTest::testMultiInherite()
{
	IBase1* b1 = (IBase1*)this->bf->getBean("MultiBase");
	IBase2* b2 = (IBase2*)this->bf->getBean("MultiBase");
	
	CPPUNIT_ASSERT(b1->f1() == 1);
	CPPUNIT_ASSERT(b2->f2() == 2);
	this->bf->freeBean(b1);
	this->bf->freeBean(b2);
}
