/**
 * @file vsprintf_test.cpp
 * @author xiao2macf
 * @brief sizeof使用
 * @version 0.1
 * @date 2023-04-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class A {
    private:
    //char a; 加上a也是1
};

class A2 {};

class B {
    private:
    char a;
    char b;
    bool c;
};

class C {
    private:
    char a;
    char b;
    bool c;
    char* d;
    char e;
};

class D {
    private:
    int a;
};

class E : public A, public A2 {};

class F : public B, public D {};

class G : public B, public C {};


int main() {
    char* p = nullptr;
    
    cout << "sizeof(p)=" << sizeof(p) << endl; //8
    cout << "sizeof(A)=" << sizeof(A) << endl; //1
    cout << "sizeof(B)=" << sizeof(B) << endl; //3
    cout << "sizeof(C)=" << sizeof(C) << endl; //16
    cout << "sizeof(D)=" << sizeof(D) << endl; //4
    cout << "sizeof(E)=" << sizeof(E) << endl; //1
    cout << "sizeof(F)=" << sizeof(F) << endl; //8
    cout << "sizeof(G)=" << sizeof(G) << endl; //24
      
    
    return 0;
}