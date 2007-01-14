
#include "AutumnException.h"
#include "TypeManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeManagerTest);

void TypeManagerTest::testBasicType()
{
	vector<string> vl, vl2;
	vector<string>::iterator it;
	vl.push_back("1234.567");
	vl2.push_back("-12345678.123");
	
	//const string charBT("char");
	it = vl.begin();
	char* c = (char*)tm->createValue(vl, charBT, it);
	CPPUNIT_ASSERT( *c == '1' );
	tm->freeValue(c, charBT);
	
	char c1[10] = {-11, 0};
	vector<string> vl_c;
	vl_c.push_back((char*)c1);
	it = vl_c.begin();
	c = (char*)tm->createValue(vl_c, charBT, it);
	CPPUNIT_ASSERT( *c == -11 );
	tm->freeValue(c, charBT);
	
	//const string ucharBT("unsignedchar");
	it = vl.begin();
	unsigned char* uc = (unsigned char*)tm->createValue(vl, ucharBT, it);
	CPPUNIT_ASSERT( *uc == '1' );
	tm->freeValue(uc, ucharBT);
	
	unsigned char uc1[10] = {245, 0};
	vector<string> vl_uc;
	vl_uc.push_back((char*)uc1);
	it = vl_uc.begin();
	uc = (unsigned char*)tm->createValue(vl_uc, ucharBT, it);
	CPPUNIT_ASSERT( *uc == 245 );
	tm->freeValue(uc, ucharBT);
	
	//const string shortBT("short");
	it = vl.begin();
	short * sh = (short*)tm->createValue(vl, shortBT, it);
	CPPUNIT_ASSERT( *sh == 1234 );
	tm->freeValue(sh, shortBT);
	
	//const string ushortBT("unsignedshort");
	it = vl.begin();
	unsigned short * ush = (unsigned short *)tm->createValue(vl, ushortBT, it);
	CPPUNIT_ASSERT( *ush == 1234 );
	tm->freeValue(ush, ushortBT);

	vector<string> vl_ush;
	vl_ush.push_back("65533");
	it = vl_ush.begin();
	ush = (unsigned short *)tm->createValue(vl_ush, ushortBT, it);
	CPPUNIT_ASSERT( *ush == 65533 );
	tm->freeValue(ush, ushortBT);
	
	//const string intBT("int");
	it = vl.begin();
	int* i = (int*)tm->createValue(vl, intBT, it);
	CPPUNIT_ASSERT( *i == 1234 );
	tm->freeValue(c, intBT);
	
	//const string uintBT("unsignedint");
	it = vl.begin();
	unsigned int* ui = (unsigned int *)tm->createValue(vl, uintBT, it);
	CPPUNIT_ASSERT( *ui == 1234 );
	tm->freeValue(ui, uintBT);
	
	//const string longBT("long");
	it = vl.begin();
	long* l = (long*)tm->createValue(vl, longBT, it);
	CPPUNIT_ASSERT( *l == 1234 );
	tm->freeValue(l, longBT);
	
	//const string ulongBT("unsingedlong");
	it = vl2.begin();
	unsigned long* ul = (unsigned long*)tm->createValue(vl2, ulongBT, it);
	CPPUNIT_ASSERT( *ul == -12345678 );
	tm->freeValue(ul, ulongBT);
	
	//const string floatBT("float");
	vector<string> vf;
	vf.push_back("-1.23456");
	it = vf.begin();
	float* f = (float*)tm->createValue(vf, floatBT, it);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(*f, -1.23456, 0.0000001);
	tm->freeValue(f, floatBT);
	
	//const string doubleBT("double");
	it = vl2.begin();
	double* d = (double*)tm->createValue(vl2, doubleBT, it);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( *d, -12345678.123, 0.0000001 );
	tm->freeValue(d, doubleBT);
	
	//const string stringBT("string");
	it = vl2.begin();
	string* s = (string*)tm->createValue(vl2, stringBT, it);
	CPPUNIT_ASSERT( s->compare("-12345678.123") == 0 );
	tm->freeValue(s, stringBT);
	
	//const string cstrBT("char*");
	it = vl2.begin();
	char** cs = (char**)tm->createValue(vl2, cstrBT, it);
	CPPUNIT_ASSERT( strcmp(*cs, "-12345678.123") == 0 );
	tm->freeValue(cs, cstrBT);
	
	//const string ucstrBT("unsignedchar*");
	it = vl2.begin();
	unsigned char** ucs = (unsigned char**)tm->createValue(vl2, ucstrBT, it);
	CPPUNIT_ASSERT( strcmp(*cs, "-12345678.123") == 0 );
	tm->freeValue(cs, ucstrBT);

	//Exception
	vector<string> vEmpty;
	typedef NonValueEx* ep;
	it = vEmpty.begin();
	CPPUNIT_ASSERT_THROW(tm->createValue(vEmpty, charBT, it), ep);
	
}

void TypeManagerTest::testCombinedType()
{
//	TypeManager* tm = new TypeManager();
	vector<string> vl;
	vector<string>::iterator it;
	vl.push_back("aaa");

	it = vl.begin();
	char*** p = (char***)tm->createValue(vl, "char**", it);
	CPPUNIT_ASSERT( strcmp(**p, "aaa") == 0 );
	char** p1 = *p;
	tm->freeSelfSpace(p, "char**");
	CPPUNIT_ASSERT( strcmp(*p1, "aaa") == 0 );
	delete p1;
}

void TypeManagerTest::testTypeSetter()
{
//	TypeManager* tm = new TypeManager();
	vector<string> vl;
	vector<string>::iterator it;
	vl.push_back("aaa");
	typedef MissDefinitionEx* ep;

	it = vl.begin();
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "dumbBT", it), ep);
	tm->setBasicType("dumbBT", new dumbBT);
	it = vl.begin();
	CPPUNIT_ASSERT_NO_THROW(tm->createValue(vl, "dumbBT", it));
	CPPUNIT_ASSERT_NO_THROW(tm->freeValue(NULL, "dumbBT"));
	tm->eraseValueType("dumbBT");
	it = vl.begin();
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "dumbBT", it), ep);
	
	it = vl.begin();
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "char_dumbCT", it), ep);
	tm->setCombinedType("_dumbCT", new dumbCT);
	it = vl.begin();
	CPPUNIT_ASSERT_NO_THROW(tm->createValue(vl, "char_dumbCT", it));
	CPPUNIT_ASSERT_NO_THROW(tm->freeValue(NULL, "char_dumbCT"));
	tm->eraseValueType("_dumbCT");
	it = vl.begin();
	CPPUNIT_ASSERT_THROW(tm->createValue(vl, "char_dumbCT", it), ep);
	
}