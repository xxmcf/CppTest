/**
 * @file vsprintf_test.cpp
 * @author xiao2macf
 * @brief 
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <algorithm>
using namespace std;


//0-9 a-z 
//36 10 
//72 20
//720  0
//108 30
//123  1*36~2 2*36~1 3
//123 3f

char toChar36(int num) {
    char ret = '\0';
    num %= 36;
    if (num < 10) {
        ret = num + '0';
    } else {
        ret = num - 10 + 'a';
    }
    return ret;
}

string toData36(int dec) {
    string ret, ret2;
    
    int pre = dec / 36;
    int mod = dec % 36;
    int span = 0;
    while (pre >= 36) {
        ret.push_back(toChar36(mod));
        mod = pre % 36;
        pre = pre / 36;
    }

    ret.push_back(toChar36(mod));
    
    if (pre != 0) {
        ret.push_back(toChar36(pre));
    }
    reverse(ret.begin(), ret.end());
    // for (int i = ret.size()-1; i >= 0; i--) {
    //     ret2.push_back(ret[i]);
    // }
    return ret;
}



int main() {

    int a = 108;
    
    cout << "108: " << toData36(108) << endl; //30
    cout << "109: " << toData36(109) << endl; //31
    cout << "123: " << toData36(123) << endl; //3f
    cout << "123456: " << toData36(123456) << endl; //2n9c
    cout << "'a' - '9': " << 'A'-'9' << endl;
    
    return 0;
}