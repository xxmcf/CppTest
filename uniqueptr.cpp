#include <memory>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    unique_ptr<string> p1(new string("I'm Li Ming!"));
    unique_ptr<string> p2(new string("I'm age 22."));
        
    cout << "p1：" << p1.get() << endl;
    cout << "p2：" << p2.get() << endl;

    //p1 = p2;					// 禁止左值赋值
    //unique_ptr<string> p3(p2);	// 禁止左值赋值构造
    unique_ptr<string> p3(std::move(p1));
    
    cout << "p1：" << p1.get() << endl;
    cout << "p3：" << p3.get() << endl;

    p1 = std::move(p2);	// 使用move把左值转成右值就可以赋值了，效果和auto_ptr赋值一样
    cout << "p1：" << p1.get() << endl;
    cout << "p2：" << p2.get() << endl;

    vector<unique_ptr<string>> vec;
    unique_ptr<string> p4(new string("I'm P4"));
    unique_ptr<string> p5(new string("I'm P5"));

    vec.push_back(std::move(p4));
    vec.push_back(std::move(p5));

    cout << "vec.at(0)：" << *vec.at(0) << endl;
    cout << "vec[1]：" << *vec[1] << endl;

    //vec[0] = vec[1];	/* 不允许直接赋值 */
    vec[0] = std::move(vec[1]);		// 需要使用move修饰，使得程序员知道后果

    cout << "vec.at(0)：" << *vec.at(0) << endl;
    cout << "vec[1]：" << *vec[1] << endl;

    return 0;
}