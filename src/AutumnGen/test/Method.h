
class ClassA{
public:
	void f1();
	void f2(void);
	void f3(int i);
	void f4(int i=0);
	void f5(const int);
	void f6(const int&);
	void f7(int[]);
	void f8(int a[][2]);
	void f9(ClassA);
	void f10(const ClassA);
	void f10(ClassA*);
	void f11(ClassA a);

	void f12(int i, char c, string s);
	void f13(string s = "ad,ad", int = 0);
	void f14(vector<string>, map<int, char> m);
};

class ClassB{
public:
	ClassB(int, char);
	~ClassB();
	static void f1();

	virtual void f2();
	inline void f3();
	void f4() const;
	void f5() throw(Ex);
	ClassB operator +();

	ClassB* clone();
	// static factory method
	static ClassB* valueof(string);
	// instance factory method
	ClassA* makeClassA();
};

// has no public constructor
class ClassC{
	ClassC(){}
};

// public, private, protected and method body
class ClassD{
public:
	void f1(){}
protected:
	void f2(){
		return;
	}
private:
	int f3(){
		int a = 1 + 1;
		return a;
	}
};