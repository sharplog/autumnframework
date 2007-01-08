
#include "AutumnException.h"
#include "TypeManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeManagerTest);

void TypeManagerTest::testBasicType()
{
	TypeManager* tm = TypeManager::getInstance();

	vector<string> vl, vl2;
	vl.push_back("1234.567");
	vl2.push_back("-12345678.123");
	
	//const string charBT("char");
	char* c = (char*)tm->createValue(vl, charBT);
	CPPUNIT_ASSERT( *c == '1' );
	tm->freeValue(c, charBT);
	
	char c1[10] = {-11, 0};
	vector<string> vl_c;
	vl_c.push_back((char*)c1);
	c = (char*)tm->createValue(vl_c, charBT);
	CPPUNIT_ASSERT( *c == -11 );
	tm->freeValue(c, charBT);
	
	//const string ucharBT("unsignedchar");
	unsigned char* uc = (unsigned char*)tm->createValue(vl, ucharBT);
	CPPUNIT_ASSERT( *uc == '1' );
	tm->freeValue(uc, ucharBT);
	
	unsigned char uc1[10] = {245, 0};
	vector<string> vl_uc;
	vl_uc.push_back((char*)uc1);
	uc = (unsigned char*)tm->createValue(vl_uc, ucharBT);
	CPPUNIT_ASSERT( *uc == 245 );
	tm->freeValue(uc, ucharBT);
	
	//const string shortBT("short");
	short * sh = (short*)tm->createValue(vl, shortBT);
	CPPUNIT_ASSERT( *sh == 1234 );
	tm->freeValue(sh, shortBT);
	
	//const string ushortBT("unsignedshort");
	unsigned short * ush = (unsigned short *)tm->createValue(vl, ushortBT);
	CPPUNIT_ASSERT( *ush == 1234 );
	tm->freeValue(ush, ushortBT);

	vector<string> vl_ush;
	vl_ush.push_back("65533");
	ush = (unsigned short *)tm->createValue(vl_ush, ushortBT);
	CPPUNIT_ASSERT( *ush == 65533 );
	tm->freeValue(ush, ushortBT);
	
	//const string intBT("int");
	int* i = (int*)tm->createValue(vl, intBT);
	CPPUNIT_ASSERT( *i == 1234 );
	tm->freeValue(c, intBT);
	
	//const string uintBT("unsignedint");
	unsigned int* ui = (unsigned int *)tm->createValue(vl, uintBT);
	CPPUNIT_ASSERT( *ui == 1234 );
	tm->freeValue(ui, uintBT);
	
	//const string longBT("long");
	long* l = (long*)tm->createValue(vl, longBT);
	CPPUNIT_ASSERT( *l == 1234 );
	tm->freeValue(l, longBT);
	
	//const string ulongBT("unsingedlong");
	unsigned long* ul = (unsigned long*)tm->createValue(vl2, ulongBT);
	CPPUNIT_ASSERT( *ul == -12345678 );
	tm->freeValue(ul, ulongBT);
	
	//const string floatBT("float");
	vector<string> vf;
	vf.push_back("-1.23456");
	float* f = (float*)tm->createValue(vf, floatBT);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(*f, -1.23456, 0.0000001);
	tm->freeValue(f, floatBT);
	
	//const string doubleBT("double");
	double* d = (double*)tm->createValue(vl2, doubleBT);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( *d, -12345678.123, 0.0000001 );
	tm->freeValue(d, doubleBT);
	
	//const string stringBT("string");
	string* s = (string*)tm->createValue(vl2, stringBT);
	CPPUNIT_ASSERT( s->compare("-12345678.123") == 0 );
	tm->freeValue(s, stringBT);
	
	//const string cstrBT("char*");
	char** cs = (char**)tm->createValue(vl2, cstrBT);
	CPPUNIT_ASSERT( strcmp(*cs, "-12345678.123") == 0 );
	tm->freeValue(cs, cstrBT);
	
	//const string ucstrBT("unsignedchar*");
	unsigned char** ucs = (unsigned char**)tm->createValue(vl2, ucstrBT);
	CPPUNIT_ASSERT( strcmp(*cs, "-12345678.123") == 0 );
	tm->freeValue(cs, ucstrBT);

	//Exception
	vector<string> vEmpty;
	typedef NonValueEx* ep;
	CPPUNIT_ASSERT_THROW(tm->createValue(vEmpty, charBT), ep);
	
}

void TypeManagerTest::testCombinedType()
{
	TypeManager* tm = TypeManager::getInstance();
	vector<string> vl;
	vl.push_back("aaa");

	char*** p = (char***)tm->createValue(vl, "char**");
	CPPUNIT_ASSERT( strcmp(**p, "aaa") == 0 );
	char** p1 = *p;
	tm->freeSelfSpace(p, "char**");
	CPPUNIT_ASSERT( strcmp(*p1, "aaa") == 0 );
	delete p1;
}

void TypeManagerTest::testTypeSetter()
{
	TypeManager* tm = TypeManager::getInstance();
	vector<string> vl;
	vl.push_back("aaa");
	typedef MissDefinitionEx* ep;

	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "dumbBT"), ep);
	tm->setBasicType("dumbBT", new dumbBT);
	CPPUNIT_ASSERT_NO_THROW(tm->createValue(vl, "dumbBT"));
	CPPUNIT_ASSERT_NO_THROW(tm->freeValue(NULL, "dumbBT"));
	tm->eraseValueType("dumbBT");
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "dumbBT"), ep);
	
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "char_dumbCT"), ep);
	tm->setCombinedType("_dumbCT", new dumbCT);
	CPPUNIT_ASSERT_NO_THROW(tm->createValue(vl, "char_dumbCT"));
	CPPUNIT_ASSERT_NO_THROW(tm->freeValue(NULL, "char_dumbCT"));
	tm->eraseValueType("_dumbCT");
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "char_dumbCT"), ep);
	
}