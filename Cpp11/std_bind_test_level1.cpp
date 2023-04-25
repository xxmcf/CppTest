/**
 * @file std_bind_test.cpp
 * @author xiao2macf
 * @brief std::bind基本使用方法
 * @version 0.1
 * @date 2023-04-25
 * 参考：
 * C++11 – std::bind简要介绍以及可绑定函数的几种形式总结 https://www.stubbornhuang.com/917/
 * @copyright Copyright (c) 2023
 * 拓展：
 * 1 std::bind绑定重载函数
 * 2 std::bind与std::ref
 */
#include <string>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <functional>
#include <memory>
#include "../unit_test.h"

using namespace std::placeholders;


int StaticBindFunc(int a, int b) {
    return a*2 + b;
}

//非模板类型（普通函数）
void test_bind_to_no_template() {
//TEST_CASE(bind_to_no_template) {
    int ret = 0;
    
    // 1 使用占位符先占位，然后执行时再传参
    auto staticFunc1 =  std::bind(&StaticBindFunc, _1, _2);
    ret = staticFunc1(1,2);
    REQUIRE(ret == 4);

    // 2 使用一个占位符先占位，然后执行时传一个参
    auto staticFunc2 = std::bind(&StaticBindFunc, _1, 4);
    ret = staticFunc2(3);
    REQUIRE(ret == 10);
    auto staticFunc3 = std::bind(&StaticBindFunc, 5, _1);
    ret = staticFunc3(6);
    REQUIRE(ret == 16);

    // 3 使用占位符先占位，但是参数位置调换
    auto staticFunc4 = std::bind(&StaticBindFunc, _2, _1);
    ret = staticFunc4(7,8);
    REQUIRE(ret == 23);
}

template <class T>
T StaticBindTemplateFunc(T a, T b)
{
    return a * 2 + b;
}

//模板类型
void test_bind_to_template() {
    int ret = 0;

    // 1 使用占位符先占位，然后执行时再传参
    auto staticFunc1 = std::bind(&StaticBindTemplateFunc<int>, _1, _2);
    ret = staticFunc1(1, 2);
    REQUIRE(ret == 4);

    // 2 使用一个占位符先占位，然后执行时传一个参
    auto staticFunc2 = std::bind(&StaticBindTemplateFunc<int>, _1, 4);
    ret = staticFunc2(3);
    REQUIRE(ret == 10);
    auto staticFunc3 = std::bind(&StaticBindTemplateFunc<int>, 5, _1);
    ret = staticFunc3(6);
    REQUIRE(ret == 16);

    // 3 使用占位符先占位，但是参数位置调换
    auto staticFunc4 = std::bind(&StaticBindTemplateFunc<int>, _2, _1);
    ret = staticFunc4(7, 8);
    REQUIRE(ret == 23);
}

class A
{
public:
    A(): c(0), d(0)
    {
    };

public:
    int Func(int a, int b)
    {
        c = a * 2 + b;
        return c;
    }

    int get_c() {
        return c;
    }

private:
    int c;
public:
    int d;
};

//绑定成员函数-非模板类型
void test_bind_to_class_method_no_template() {
    int ret = 0;
    
    // 1 类的对象, 对象会拷贝
    A tempA;
    auto memberFunc1 = std::bind(&A::Func, tempA, _1, _2);
    ret = memberFunc1(1, 2);
    REQUIRE(ret == 4);
    REQUIRE(tempA.get_c() == 0); //对象拷贝，不影响原始对象

    // 2 类的对象的引用
    auto memberFunc2 = std::bind(&A::Func, std::ref(tempA), _1, _2);
    ret = memberFunc2(3, 4);
    REQUIRE(ret == 10);
    REQUIRE(tempA.get_c() == 10);

    // 3 类的对象的指针
    A* pTempA = new A();

    auto memberFunc3 = std::bind(&A::Func, pTempA, _1, _2);
    ret = memberFunc3(5, 6);
    REQUIRE(ret == 16);
    REQUIRE(pTempA->get_c() == 16);

    delete pTempA;

    // 4 类的对象的智能指针
    std::shared_ptr<A> pTempAPtr = std::make_shared<A>();
    auto memberFunc4 = std::bind(&A::Func, pTempAPtr, _1, _2);
    ret = memberFunc4(7, 8);
    REQUIRE(ret == 22);
    REQUIRE(pTempAPtr->get_c() == 22);
}

class ATemplateClass
{
public:
    ATemplateClass() : c(0)
    {
    };

public:
    template <class T>
    int Func(T a, T b)
    {
        c = a * 2 + b;
        return c;
    }

    int get_c() {
        return c;
    }

private:
    int c;
};

//绑定成员函数-模板类型
void test_bind_to_class_method_template() {
    int ret = 0;

    // 1 类的对象
    ATemplateClass tempA;
    auto memberFunc1 = std::bind(&ATemplateClass::Func<int>, tempA, _1, _2);
    ret = memberFunc1(1, 2);
    REQUIRE(ret == 4);
    REQUIRE(tempA.get_c() == 0);

    // 2 类的对象的引用
    auto memberFunc2 = std::bind(&ATemplateClass::Func<int>, std::ref(tempA), _1, _2);
    ret = memberFunc2(3, 4);
    REQUIRE(ret == 10);
    REQUIRE(tempA.get_c() == 10);

    // 3 类的对象的指针
    ATemplateClass* pTempA = new ATemplateClass();
    auto memberFunc3 = std::bind(&ATemplateClass::Func<int>, pTempA, _1, _2);
    ret = memberFunc3(5, 6);
    REQUIRE(ret == 16);
    REQUIRE(pTempA->get_c() == 16);

    delete pTempA;

    // 4 类的对象的智能指针
    std::shared_ptr<ATemplateClass> pTempAPtr = std::make_shared<ATemplateClass>();
    auto memberFunc4 = std::bind(&ATemplateClass::Func<int>, pTempAPtr, _1, _2);
    ret = memberFunc4(7, 8);
    REQUIRE(ret == 22);
    REQUIRE(pTempAPtr->get_c() == 22);
}

//绑定类的公有成员
void test_bind_to_class_public_variable() {
    // 绑定类公共成员变量，不可绑定私有成员变量
    auto memberVar = std::bind(&A::d, _1);

    // 1 类对象做参数传递
    A tempA;

    REQUIRE(memberVar(tempA) == 0);
    memberVar(tempA) = 10;
    REQUIRE(tempA.d == 10); //对象作参数也会改变原始对你的值!
    tempA.d = 0; //恢复原始值

    // 2 类对象引用做参数传递
    REQUIRE(memberVar(std::ref(tempA)) == 0);
    memberVar(std::ref(tempA)) = 10;
    REQUIRE(tempA.d == 10);

    // 3 类指针做参数传递
    A* pTempA = new A();
    REQUIRE(memberVar(pTempA) == 0);
    memberVar(pTempA) = 10;
    REQUIRE(pTempA->d == 10);

    delete pTempA;

    // 4 类智能指针做参数传递
    std::shared_ptr<A> pTempAPtr = std::make_shared<A>();

    REQUIRE(memberVar(pTempAPtr) == 0);
    memberVar(pTempAPtr) = 10;
    REQUIRE(pTempAPtr->d == 10);
}

//绑定lambda表达式
void test_bind_to_lambda() {
    int ret = 0;

    // 1 lambda表达式
    auto memberFunc1 = std::bind([](int a, int b)->int { 
        return a * 2 + b;
    }, _1, _2);
    ret = memberFunc1(1, 2);
    REQUIRE(ret == 4);
}

int main() {

    TEST_CASES_INIT();

    test_bind_to_no_template();
    test_bind_to_template();
    test_bind_to_class_method_no_template();
    test_bind_to_class_method_template();
    test_bind_to_class_public_variable();
    test_bind_to_lambda();

    TEST_CASES_RESULT();
    
    return 0;
}