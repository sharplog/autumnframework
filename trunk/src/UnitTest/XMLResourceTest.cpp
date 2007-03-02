
#include "XMLResourceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(XMLResourceTest);

void XMLResourceTest::setUp()
{
}

void XMLResourceTest::tearDown()
{
}

void XMLResourceTest::testDefaultConfig()
{
	this->res1 = new XMLResource("../TestXMLDefaultConfig.xml");

	const vector<TLibrary*>* plibs = res1->getLibraries();
	TLibrary* l = (*plibs)[0];

	CPPUNIT_ASSERT( l->Path == "dumb.dll" );
	CPPUNIT_ASSERT( l->Name == "dumb.dll" );
	CPPUNIT_ASSERT( l->NS == "" );

	TBean b = l->Beans[0];
	CPPUNIT_ASSERT( b.ClassName == "dumbclass" ); 
	CPPUNIT_ASSERT( b.Name == "dumbclass" ); 
	CPPUNIT_ASSERT( b.Initializable == false ); 
	CPPUNIT_ASSERT( b.Destroyable == false ); 
	CPPUNIT_ASSERT( b.Singleton == false ); 
	CPPUNIT_ASSERT( b.DependedObjects.size() == 0 );
	CPPUNIT_ASSERT( b.ConArgs.size() == 0 ); 

	TProperty p = b.Properties[0];
	CPPUNIT_ASSERT( p.Name == "dumbproperty" ); 
	CPPUNIT_ASSERT( p.Type == "dumbtype" ); 
	CPPUNIT_ASSERT( p.Managed == true ); 
	CPPUNIT_ASSERT( p.Value.at(0) == "dumb" ); 
	
	TType t = l->Types[0];
	CPPUNIT_ASSERT( t.Name == "typeclass" ); 
	CPPUNIT_ASSERT( t.ClassName == "typeclass" ); 
	CPPUNIT_ASSERT( t.IsBasic == true ); 

	delete this->res1;
}

void XMLResourceTest::testAllConfig()
{
	this->res2 = new XMLResource("../TestXMLAllConfig.xml");
	const vector<TLibrary*>* plibs = res2->getLibraries();
	
	CPPUNIT_ASSERT(plibs->size() == 2);

	// lib1
	TLibrary* l = (*plibs)[0];
	CPPUNIT_ASSERT( l->Path == "dumb.dll" );
	CPPUNIT_ASSERT( l->Name == "testlib1" );
	CPPUNIT_ASSERT( l->NS == "nstestlib1" );
	
	TBean b = l->Beans[0];
	CPPUNIT_ASSERT( b.ClassName == "dumbclass" ); 
	CPPUNIT_ASSERT( b.Name == "bean1-1" ); 
	CPPUNIT_ASSERT( b.Initializable == true ); 
	CPPUNIT_ASSERT( b.Destroyable == true ); 
	CPPUNIT_ASSERT( b.Singleton == true ); 

	CPPUNIT_ASSERT( b.DependedObjects.size() == 2 );
	CPPUNIT_ASSERT( b.DependedObjects[0] == "class1" );
	CPPUNIT_ASSERT( b.DependedObjects[1] == "class2" );

	CPPUNIT_ASSERT( b.ConArgs.size() == 1 ); 
	TProperty a = b.ConArgs[0];
	CPPUNIT_ASSERT( a.Name == "arg1" );
	CPPUNIT_ASSERT( a.Type == "argtype1" );
	CPPUNIT_ASSERT( a.Managed == true );
	CPPUNIT_ASSERT( a.Value[0] == "argvalue1" );
	
	CPPUNIT_ASSERT( b.Properties.size() == 2 ); 
	TProperty p = b.Properties[0];
	CPPUNIT_ASSERT( p.Name == "property1" ); 
	CPPUNIT_ASSERT( p.Type == "dumbtype" ); 
	CPPUNIT_ASSERT( p.Managed == false ); 
	CPPUNIT_ASSERT( p.Value.size() == 2 ); 
	CPPUNIT_ASSERT( p.Value[0] == "dumb1" ); 
	CPPUNIT_ASSERT( p.Value[1] == "dumb2" ); 
	p = b.Properties[1];
	CPPUNIT_ASSERT( p.Name == "property2" ); 
	CPPUNIT_ASSERT( p.Type == "type2" ); 
	CPPUNIT_ASSERT( p.Managed == true ); 
	CPPUNIT_ASSERT( p.Value.size() == 1 ); 
	CPPUNIT_ASSERT( p.Value[0] == "" ); 
	
	CPPUNIT_ASSERT( l->Types.size() == 2 ); 
	TType t = l->Types[0];
	CPPUNIT_ASSERT( t.Name == "ctype1" ); 
	CPPUNIT_ASSERT( t.ClassName == "typeclass" ); 
	CPPUNIT_ASSERT( t.IsBasic == false ); 
	t = l->Types[1];
	CPPUNIT_ASSERT( t.Name == "typeclass2" ); 
	CPPUNIT_ASSERT( t.ClassName == "typeclass2" ); 
	CPPUNIT_ASSERT( t.IsBasic == true ); 

	//lib2
	l = (*plibs)[1];
	CPPUNIT_ASSERT( l->Path == "dumb2.dll" );
	CPPUNIT_ASSERT( l->Beans.size() == 2);
	CPPUNIT_ASSERT( l->Beans[0].ClassName == "bean2-1");
	CPPUNIT_ASSERT( l->Beans[1].ClassName == "bean2-2");

	delete this->res2;
}