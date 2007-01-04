
#ifndef AUTUMN_XMLRESOURCETEST_H
#define AUTUMN_XMLRESOURCETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "XMLResource.h"

using namespace CppUnit;

class XMLResourceTest: public TestFixture{
	CPPUNIT_TEST_SUITE(XMLResourceTest);
	CPPUNIT_TEST(testDefaultConfig);
	CPPUNIT_TEST(testAllConfig);
	CPPUNIT_TEST_SUITE_END();

	XMLResource* res1, *res2;
public:
	void setUp();
	void tearDown();

	void testDefaultConfig();
	void testAllConfig();
};
#endif
