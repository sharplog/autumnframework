
#include "MapHashTableTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MapHashTableTest);


void MapHashTableTest::testHashTable()
{
	MapHashTable<long, long> mh(7);

	long l1 = 11, l2 = 100;
	mh.insertElement(1, l1);
	mh.insertElement(10, l2);

	map<long, long> m;
	mh.listElement(m);

	int i = m.size();
	CPPUNIT_ASSERT( i == 2);

	map<long, long>::iterator it = m.begin();
	CPPUNIT_ASSERT( it->second == 11);
	it++;
	CPPUNIT_ASSERT( it->second == 100);
}