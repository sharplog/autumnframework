
#include "TypeInjectionTest.h"
#include "IBasicTypesBean.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeInjectionTest);

void TypeInjectionTest::setUp()
{
	this->bf = getBeanFactoryWithXML("../AutumnUnitTest.xml");
}

void TypeInjectionTest::tearDown()
{
	deleteBeanFactory(this->bf);
}

void TypeInjectionTest::testBasicType()
{
/**/	IBasicTypesBean* b = (IBasicTypesBean*)this->bf->getBean("BasicTypesBean1");

	CPPUNIT_ASSERT(b->getChar() == 'c');
	CPPUNIT_ASSERT(b->getUChar() == 'u');
	CPPUNIT_ASSERT(b->getShort() == 123);
	CPPUNIT_ASSERT(b->getUShort() == 65530);
	CPPUNIT_ASSERT(b->getInt() == 70000);
	CPPUNIT_ASSERT(b->getUInt() == 77777);
	CPPUNIT_ASSERT(b->getLong() == 8000000);
	CPPUNIT_ASSERT(b->getULong() == 4294967295);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(b->getFloat(), 1.234567, 1e-7);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(b->getDouble(), 1.23456789012345, 1e-15);
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
	CPPUNIT_ASSERT_DOUBLES_EQUAL(b->getFloat(), 1.234567, 1e-7);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(b->getDouble(), 1.23456789012345, 1e-15);
	CPPUNIT_ASSERT(b->getString().compare("hello, String") == 0 );
	CPPUNIT_ASSERT(strcmp(b->getCStr(), "hello, CStr") == 0);
	CPPUNIT_ASSERT(strcmp((const char*)b->getUCStr(), "hello, UCStr") == 0);
	this->bf->freeBean(b);
/**/}

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

void TypeInjectionTest::testCustomizedType()
{
}
