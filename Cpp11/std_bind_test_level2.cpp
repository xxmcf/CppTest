/**
 * @file std_bind_test.cpp
 * @author xiao2macf
 * @brief std::bind易错点
 * 1 std::bind绑定重载函数
 * 2 std::bind与std::ref
 * 3 std::bind与QObject::connect
 *  connect(pPostFileReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
        [=](QNetworkReply::NetworkError code) 
    {        
		LOG_REPORT_HTTP(QList<QVariant>() << QString("QNetworkReply-error") << EXEC_NAME << strUri << "post" << QString(oSign.toString()) << QString::number(code), false);
    });
 * 4 std::bind总是使用值拷贝的形式传参，哪怕函数声明为引用
 * 5 std::bind可以使用std::ref来传引用
 * 6 std::bind虽然使用了std::ref传递了引用，如果函数本身只接受值类型参数，传递的仍然是值而不是引用。
 * 7 std::bind不接受只可以移动不可拷贝的类型，如std::unique_ptr
 * 8 不要把std::bind的结果传递给另一个std::bind
 * @version 0.1
 * @date 2023-04-25
 */
#include <string>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <functional>
#include <memory>
#include "../unit_test.h"

using namespace std::placeholders;

int OverrideMethod(int a) {
    return a * 2 ;
}

int OverrideMethod(int a, int b) {
    return a * 2 + b;
}

//绑定重载函数
void test_bind_to_override_method() {
    int ret = 0;

    //1 绑定重载函数要指定函数类型
    auto fun1 = std::bind((int(*)(int))&OverrideMethod, _1);
    ret = fun1(3);
    REQUIRE(ret == 6);

    auto fun2 = std::bind((int(*)(int, int))OverrideMethod, _1, _2);
    ret = fun2(3, 4);
    REQUIRE(ret == 10);

    auto fun3 = std::bind((int(*)(int, int))&OverrideMethod, _1, 5);
    ret = fun3(3);
    REQUIRE(ret == 11);

    //2 定义函数类型，绑定时转换到自定义函数类型
    typedef int (*my_func)(int, int);
    auto func4 = std::bind((my_func)OverrideMethod, 3, 4);
    ret = fun2(3, 4);
    REQUIRE(ret == 10);

    //3 模板写法
    auto func5 = std::bind<my_func>(&OverrideMethod, 3, 4);
    //auto func50 = std::bind<int(int, int)>(OverrideMethod, 3, 4);  与上一行写法一致
    ret = func5(3, 4);
    REQUIRE(ret == 10);
}

class A {
public:
    A() : c(0), is_copy_(false) {
        std::cout << "A construct" << std::endl;
    }

    A(const A& obj) {
        this->c = obj.c;
        is_copy_ = true;
        std::cout << "A copy construct" << std::endl;
    }

    int Func(int a, int b) {
        return c = a * 2 + b;
    }

    int get_c() {
        return c;
    }
    int* get_c_ptr() {
        return &c;
    }

private:
    int c;
    bool is_copy_;
};

//std::bind与std::ref协同使用
void test_bind_with_ref() {
    int ret = 0;

    //1.0 绑定类对象
    A tempA;
    std::function<int(int, int)> func1 = std::bind(&A::Func, tempA, _1, _2);
    ret = func1(2, 3);
    REQUIRE_EX(ret == 7);
    REQUIRE_EX(tempA.get_c() == 0);

    //1.1 绑定类对象，每次绑定都创建一个对象
    auto func2 = std::bind(&A::get_c_ptr, tempA);
    auto func3 = std::bind(&A::get_c_ptr, tempA);
    int* ptr_c2 = func2();
    int* ptr_c3 = func3();
    REQUIRE_EX(ptr_c2 != tempA.get_c_ptr()); //创建的对像与原始对象相互独立
    REQUIRE_EX(ptr_c3 != tempA.get_c_ptr()); //创建的对像与原始对象相互独立
    REQUIRE_EX(ptr_c2 != ptr_c3);            //创建的对像之间也相互独立
 
    //2 绑定类对象的引用
    auto func4 = std::bind(&A::get_c_ptr, std::ref(tempA));
    auto func5 = std::bind(&A::get_c_ptr, std::ref(tempA));
    int* ptr_c4 = func4();
    int* ptr_c5 = func5();
    REQUIRE_EX(ptr_c4 == tempA.get_c_ptr()); //对象引用，操作的是同一个对象
    REQUIRE_EX(ptr_c5 == tempA.get_c_ptr()); //对象引用，操作的是同一个对象
    REQUIRE_EX(ptr_c4 == ptr_c5);            //对象引用，操作的是同一个对象

    //3 类对象是指针，绑定对象引用，销毁对象后指针funcion是不安全的
    A* tempPtrA = new A();
    auto func6 = std::bind(&A::get_c_ptr, std::ref(*tempPtrA));
    delete tempPtrA;
    int* ptr_c6 = func6();
    *ptr_c6 = 13; //报错

}


int main() {
    TEST_CASES_INIT();
    
    test_bind_to_override_method();
    test_bind_with_ref();

    TEST_CASES_RESULT();
    return 0;
}