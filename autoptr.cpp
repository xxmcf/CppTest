#include <memory>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Test {
public:
	Test() { cout << "Test的构造函数..." << endl; }
	~Test() { cout << "Test的析构函数..." << endl; }

	int getDebug() { return this->debug; }

private:
	int debug = 20;
};

int main() {
    auto_ptr<Test> test(new Test());

    cout << "test->debug：" << test->getDebug() << endl;
    cout << "(*test).debug：" << (*test).getDebug() << endl;

    //Test *tmp2 = test.release();	// 取消智能指针对动态内存的托管
    //delete tmp2;	// 之前分配的内存需要自己手动释放

    test.reset();

    // auto_ptr 被C++11抛弃的主要原因
    auto_ptr<string> p1(new string("I'm Li Ming!"));
    auto_ptr<string> p2(new string("I'm age 22."));

    cout << "p1：" << p1.get() << endl;
    cout << "p2：" << p2.get() << endl;

    // p2赋值给p1后，首先p1会先将自己原先托管的指针释放掉，然后接收托管p2所托管的指针，
    // 然后p2所托管的指针制NULL，也就是p1托管了p2托管的指针，而p2放弃了托管。
    p1 = p2;	
    cout << "p1 = p2 赋值后：" << endl;
    cout << "p1：" << p1.get() << endl;
    cout << "p2：" << p2.get() << endl;


    vector<auto_ptr<string>> vec;
    auto_ptr<string> p3(new string("I'm P3"));
    auto_ptr<string> p4(new string("I'm P4"));

    // 必须使用std::move修饰成右值，才可以进行插入容器中
    vec.push_back(std::move(p3));
    vec.push_back(std::move(p4));

    cout << "vec.at(0)：" <<  *vec.at(0) << endl;
    cout << "vec[1]：" <<  *vec[1] << endl;


    // 风险来了：
    vec[0] = vec[1];	// 如果进行赋值，问题又回到了上面一个问题中。
    cout << "vec.at(0)：" <<  vec.at(0).get() << endl;
    cout << "vec[1]：" <<  vec.at(1).get() << endl;
    cout << "vec.at(0)：" << *vec.at(0) << endl;
    //cout << "vec[1]：" << *vec[1] << endl; //崩

    return 0;
}