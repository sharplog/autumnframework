
/*
 * AutumnGen should skip comments and leteral string.
 * Class A{ public: void f();};
 *
 */

class ClassSkip{
public:
	void f1(int i, /* a comment, */ char);
	//void f2(){}

	string s1 = "class C{};";
	string s2 = "\"void f3();";

	void /*();*/ f4() /* {}*/;
}/*some comment here*/  ;