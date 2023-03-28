#include <iostream>

using namespace std;

class A{
public:
	A(){
		this->num = new int(10);
		cout << "构造函数" << endl;
	}
	A(A&x){
		this->num = new int(*x.num);
		cout << "拷贝构造函数" << endl;
	}
	A(A&&x){
		this->num = x.num;
		x.num = nullptr;
		cout << "移动构造函数" << endl;
	}
	
	void operator = (A && x){
		this->num = x.num;
		x.num = nullptr;
		cout << "移动赋值函数" << endl;
	}
	void operator = (A & x){
		this->num = new int(*x.num);
		cout << "operator=" << endl;
	}
	~A(){
		cout << "析构函数" << endl;
	}
    void toString() {
        cout << "num=" << *num << endl;
    }

	int *num;
};

int main() {

    A a1;
    a1.toString();
    A a2(a1);
    a2.toString();
    A a3 = std::move(A());
    a3.toString();

    return 0;
}