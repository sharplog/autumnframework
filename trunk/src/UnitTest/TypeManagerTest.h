
#ifndef AUTUMN_TYPEMANAGERTEST_H
#define AUTUMN_TYPEMANAGERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "TypeManager.h"

using namespace CppUnit;

class TypeManagerTest: public TestFixture{
	CPPUNIT_TEST_SUITE(TypeManagerTest);
	CPPUNIT_TEST(testBasicType);
	CPPUNIT_TEST(testCombinedType);
	CPPUNIT_TEST(testTypeSetter);
	CPPUNIT_TEST_SUITE_END();

	class dumbBT: public IBasicType{
	public:
		void* createValue(StrValueList& vl){return NULL;}
		void freeValue(void* p){ delete p;}
	};
	class dumbCT: public ICombinedType{
	public:
		void* createValue(StrValueList& vl, string basicType){return NULL;}
		void freeValue(void* p, string basicType){ delete p;}
		void freeSelfSpace(void* p){ delete p;}
	};
public:
	void setUp(){}
	void tearDown(){}

	void testBasicType();
	void testCombinedType();
	void testTypeSetter();
	
};

#endif
