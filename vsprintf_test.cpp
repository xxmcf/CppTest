/**
 * @file vsprintf_test.cpp
 * @author xiao2macf
 * @brief Use vsprintf to implement StringFormat
 *        ×Ö·û´®¸ñÊ½»¯
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include <iostream>
#include <stdarg.h> //va_start
#include <assert.h> //assert
#include <string.h> //strlen
using namespace std;

string StringFormat(const char *fmt, ...)
{
    va_list argptr;
    va_start(argptr, fmt);
    int len = vsnprintf(nullptr, 0, fmt, argptr);
    assert(len != 0);
    string str(len, '\0');
    int cnt = vsprintf((char*)str.data(), fmt, argptr);
    va_end(argptr);
    return std::move(str);
}

int main() {

    cout << StringFormat("Hello World! Hello %d", 100)  << endl;

    string str = "Hello World! Hello 100";
    // cout << __FUNCTION__ << "# str.size()=" << str.size() << ", str.length()=" << str.length() << endl;
    // cout << __FUNCTION__ << "# str=" << str << endl;
    // cout << __FUNCTION__ << "# strlen(str.c_str())=" << strlen(str.c_str()) << endl;
    // cout << __FUNCTION__ << "# str.max_size()=" << str.max_size() << endl;
    // cout << __FUNCTION__ << "# sizeof(str)=" << sizeof(str) << endl;
    
    return 0;
}

/**
Hello World! Hello 100
main# str.size()=22, str.length()=22
main# str=Hello World! Hello 100
main# strlen(str.c_str())=22
main# str.max_size()=9223372036854775807
main# sizeof(str)=32
 * 
 */
 
// string StringFormat(const char *fmt, ...)
// {
//     va_list argptr;
//     va_start(argptr, fmt);
//     va_list args2;
//     va_copy(args2, argptr);
//     cout << fmt << endl;
//     int len = vsnprintf(nullptr, 0, fmt, argptr);
//     cout << len << endl;
//     assert(len != 0);
//     string str(len, '\0');

//     int cnt = vsprintf((char*)str.data(), fmt, argptr);
//     va_end(argptr);

//     cout << __FUNCTION__ << "# len=" << len << ", cnt=" << cnt << ", str.size()=" << str.size() << ", str.length()=" << str.length() << endl;
//     cout << __FUNCTION__ << "# str=" << str << endl;
//     cout << __FUNCTION__ << "# strlen(str.c_str())=" << strlen(str.c_str()) << endl;
//     cout << __FUNCTION__ << "# str.capacity()=" << str.capacity() << endl;
//     return std::move(str);
// }