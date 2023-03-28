#include <iostream>
 
using namespace std;
 
class A
{
public:
	A(){cout << "Construct A" << endl;}
	~A(){cout << "Destruct A" << endl;}
};
 
class C
{
public:
	C(){cout << "Construct C" << endl;}
	~C(){cout << "Destruct C" << endl;}
	
};
 
class B: public A, public C
{
public:
	B(){cout << "Construct B" << endl;}
	~B(){cout << "Destruct B" << endl;}
};
 
int main(int argc, char const *argv[])
{
	B b;
	return 0;
}

/**
Construct A
Construct C
Construct B
Destruct B
Destruct C
Destruct A
 * 
 */