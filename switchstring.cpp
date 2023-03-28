/**
 * @file switchstring.cpp
 * @author xiao2macf
 * @brief 
 * @version 0.1
 * @date 2023-03-20
 * 
 * @copyright Copyright (c) 2023
 * http://www.manongjc.com/detail/60-wuozsovziirlfaz.html
 */
#include <iostream>
#include <string>

using namespace std;

constexpr size_t hash_str(const char *string_piece,size_t hashNum=0){
    return *string_piece ? hash_str(string_piece+1,(hashNum*131)+*string_piece) : hashNum;
}

size_t hash_str(const string& str){
    return hash_str(str.c_str(), 0);
}

int main() {

    size_t a = hash_str("123");
    size_t b = hash_str("233");
    cout << "a = " << a << endl;
    string str = "hello";

    switch(hash_str(str)) {
        case hash_str("hello0"):
           cout << "str = hello0" << endl;
            break;
        case hash_str("hello1"):
            cout << "str = hello1" << endl;
            break;
        case hash_str("hello2"):
            cout << "str = hello2" << endl;
            break;
        case hash_str("hello3"):
            cout << "str = hello3" << endl;
            break;
        case hash_str("hello"):
        cout << "str = hello" << endl;
            break;
        default:
            break;
    }

    return 0;
}