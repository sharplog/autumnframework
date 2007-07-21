
#ifndef AUTUMN_FACTORYTEST_H
#define AUTUMN_FACTORYTEST_H

#include "UnitTestMacro.h"
#include "IBeanFactory.h"

class FactoryTest{
	CPPUNIT_TEST_SUITE(FactoryTest);
	CPPUNIT_TEST(testInstanceFacotry);
	CPPUNIT_TEST(testStaticFacotryMethod);
	CPPUNIT_TEST_SUITE_END();
	
private:
	Autumn::IBeanFactory* bf;
	
public:
	void setUp();
	void tearDown();
	
	void testInstanceFacotry();
	void testStaticFacotryMethod();
};

#endif
