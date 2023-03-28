#include <iostream>
#include <string>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

typedef struct {
    string content1;
    string content2;
    string content3;
}Msg;

Msg* g_pMsg = nullptr;;
vector<string> g_vec;

string get_string() {
    string s = "hello";
    return s.c_str();
}

const string get_const_string() {
    string s = "const hello";
    return s;
}

string get_dump_string() {
    string s = "dump hello";
    printf("dump: %08x \n", s.data());
    return std::move(s);
}

void run() {
    string s1 = get_string();
    string s2 = get_string();
    string s3 = get_string();

    g_pMsg->content1 = s1.c_str();
    g_pMsg->content2 = s2.c_str();
    g_pMsg->content3 = s3.c_str();

    cout << g_pMsg->content1 << endl;
    cout << g_pMsg->content2 << endl;
    cout << g_pMsg->content3 << endl;

    for (string& str : g_vec) {
        printf("%08x, ", str.data());
    }
    printf("\n");
}

int main() {

    string s1 = "123123";
    string s2 = s1;
    string s3 = s1.c_str();
    const char* d1 = s1.data();
    const char* d2 = s2.data();
    const char* d3 = s3.data();

    printf("%08x, %08x, %08x\n", d1, d2, d3);

    string s4, s5;
    s4 = s1;
    s5 = s1.c_str();
    const char* d4 = s4.data();
    const char* d5 = s5.data();

    printf("%08x, %08x\n", d4, d5);

    string s6(s1);
    string s7(s1.c_str());
    const char* d6 = s6.data();
    const char* d7 = s7.data();

    printf("%08x, %08x\n", d6, d7);

    string* s8 = new string();
    string s9 = "123456";

    g_vec.push_back(*s8);
    g_vec.push_back(s9);
    g_vec.push_back(s7);

    const char* d8 = s8->data();
    const char* d9 = s9.data();

    printf("%08x, %08x\n", d8, d9, d7);

    delete s8; s8 = nullptr;

    for (string& str : g_vec) {
        printf("%08x, ", str.data());
    }
    printf("\n");

    const string s10 = get_const_string();
    const char* d10 = s10.data();
    printf("%08x\n", d10);
    cout << s10 << endl;

    string s11;
    {
        s11 = get_dump_string();
        const char* d11 = s11.data();
        printf("%08x\n", d11);
    }
    cout << s11 << endl;

    string s12 = "654321";
    string s13(s12);
    const char* d12 = s12.data();
    const char* d13 = s13.data();

    printf("%08x, %08x\n", d12, d13);
    s12.append("hel");
    printf("%08x, %08x\n", s12.data(), s13.data());
    {
        cout << s12 << endl;
        cout << s13 << endl;
    }

    //g_pMsg = (Msg *)malloc(sizeof(Msg));
    g_pMsg = new Msg;

    thread th(&run);
    th.join();
    cout << "press any key to exit..." << endl;
    getchar();
    return 0;
}

/** windows
 * 0062fdc0, 0062fda0, 0062fd80
0062fd60, 0062fd40
0062fd20, 0062fd00
 * 
 */

/** linux
00d20098, 00d20098, 00d200c8
00d20098, 00d200f8
00d20098, 00d20128
cb9d13f8, 00d20178
cb9d13f8, 00d20178, 00d20128, 
00d20218
const hello
dump: 00d20248 00d20248
dump hello
hello
hello
hello
press any key to exit...

 * 
 */