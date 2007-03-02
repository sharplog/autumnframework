#ifndef AUTUMN_UNITTESTMACRO_H
#define AUTUMN_UNITTESTMACRO_H

#include <iostream>
#include <string>

using namespace std;

/** throw this exception when a test condition failed */
class CppUnitTestException
{
private:
	string Message;
	string File;
	int Line;
public:
	CppUnitTestException(string msg, string file, int line)
	{
		this->Message= msg;
		this->File = file;
		this->Line = line;
	}
	string getMessage()
	{ 
		return this->Message; 
	}
};


#define TESTSUCCESS 0
#define TESTFAILED -1

/** define message outputing */
#define CPPUNIT_MESSAGE(message)									\
	cout<<message;

/** define a test suite */
#define CPPUNIT_TEST_SUITE(suiteName)								\
public:																\
	int excuteTest() {												\
		CPPUNIT_MESSAGE(string("\nstart testing suite ") + #suiteName + ":\n");

/** define a test function excuting */																	
#define CPPUNIT_TEST(testFunc)										\
		CPPUNIT_MESSAGE(string("\t") + #testFunc + "......")		\
		try{														\
			this->setUp();											\
			this->##testFunc##();									\
			this->tearDown();										\
			CPPUNIT_MESSAGE("OK!\n");								\
		}															\
		catch (CppUnitTestException e) {							\
			CPPUNIT_MESSAGE("Failed!\n");							\
			CPPUNIT_MESSAGE(e.getMessage());						\
			return TESTFAILED;										\
		}															\
		catch (...) {												\
			CPPUNIT_MESSAGE("Failed!\n");							\
			CPPUNIT_MESSAGE("Unknown exception happened!\n");		\
			return TESTFAILED;										\
		}															\

#define CPPUNIT_TEST_SUITE_END()									\
		return TESTSUCCESS;											\
	}

/** define a condition jusdgement */
#define CPPUNIT_ASSERT(condition)									\
	if( !(condition) )	throw CppUnitTestException(					\
		"Assertion failed. Expression: " #condition,				\
		__FILE__ , __LINE__);

#endif

