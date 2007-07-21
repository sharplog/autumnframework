
#ifndef AUTUMN_TYPEINJECTIONTEST_H
#define AUTUMN_TYPEINJECTIONTEST_H

#include "UnitTestMacro.h"
#include "IBeanFactory.h"

class TypeInjectionTest{
	CPPUNIT_TEST_SUITE(TypeInjectionTest);
	CPPUNIT_TEST(testBasicType);
	CPPUNIT_TEST(testCombinedType);
	CPPUNIT_TEST(testBeanType);
	CPPUNIT_TEST(testSingleton);
	CPPUNIT_TEST(testInitDestroyable);
//	CPPUNIT_TEST(testSelfManage);
	CPPUNIT_TEST(testInjectFromLibElse);
	CPPUNIT_TEST(testLocalBean);
	CPPUNIT_TEST(testCustomizedType);
	CPPUNIT_TEST(testMultiInherite);
	CPPUNIT_TEST_SUITE_END();

private:
	Autumn::IBeanFactory* bf;

public:
	void setUp();
	void tearDown();

	void testBasicType();
	void testCombinedType();
	void testBeanType();
	void testSingleton();
	void testInitDestroyable();
	void testSelfManage();
	void testInjectFromLibElse();
	void testLocalBean();
	void testCustomizedType();
	void testMultiInherite();
};

#endif
