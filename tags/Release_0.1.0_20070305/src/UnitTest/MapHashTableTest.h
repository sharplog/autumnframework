#ifndef AUTUMN_MAPHASHTABLETEST_H
#define AUTUMN_MAPHASHTABLETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "MapHashTable.h"

using namespace CppUnit;

class MapHashTableTest: public TestFixture{
	CPPUNIT_TEST_SUITE(MapHashTableTest);
	CPPUNIT_TEST(testHashTable);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp() {}
	void tearDown() {}

	void testHashTable();
};

#endif
