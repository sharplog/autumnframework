
#include "XMLResourceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(XMLResourceTest);

void XMLResourceTest::setUp()
{
	this->res1 = new XMLResource("../TestXMLDefaultConfig.xml");
	this->res2 = NULL;
}

void XMLResourceTest::tearDown()
{
	delete this->res1;
	delete this->res2;
}

void XMLResourceTest::testDefaultConfig()
{
	const vector<TLibrary*>* plibs = res1->getLibraries();
	TLibrary* l = plibs->at(0);

	CPPUNIT_ASSERT( l->Path == "dumb.dll" );
	CPPUNIT_ASSERT( l->Name == "dumb.dll" );
	CPPUNIT_ASSERT( l->NS == "" );

	TBean b = l->Beans.at(0);
	CPPUNIT_ASSERT( b.ClassName == "dumbclass" ); 
	CPPUNIT_ASSERT( b.Name == "dumbclass" ); 
	CPPUNIT_ASSERT( b.Initializable == false ); 
	CPPUNIT_ASSERT( b.Destroyable == false ); 
	CPPUNIT_ASSERT( b.Singleton == false ); 
	CPPUNIT_ASSERT( b.DependedObjects.size() == 0 );
	CPPUNIT_ASSERT( b.ConArgs.size() == 0 ); 

	TProperty p = b.Properties.at(0);
	CPPUNIT_ASSERT( p.Name == "dumbproperty" ); 
	CPPUNIT_ASSERT( p.Type == "dumbtype" ); 
	CPPUNIT_ASSERT( p.Managed == true ); 
	CPPUNIT_ASSERT( p.Value.at(0) == "dumb" ); 
	
	TType t = l->Types.at(0);
	CPPUNIT_ASSERT( t.Name == "typeclass" ); 
	CPPUNIT_ASSERT( t.ClassName == "typeclass" ); 
	CPPUNIT_ASSERT( t.IsBasic == true ); 
}

void XMLResourceTest::testAllConfig()
{
}