#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main() {

    //test1
    {
        string s1 = "s1";
        printf("s1 src : %0x08\n", s1.data());
        string s2 = std::move(s1);
        printf("s1 : %0x08\n", s1.data());
        printf("s2 : %0x08\n", s2.data());
        cout << "s1 = " << s1 << endl;
        cout << "s2 = " << s2 << endl; 
    }

     //test2
    {
        string s3 = "s3";
        string s4;
        printf("s3 src : %0x08\n", s3.data());
        printf("s4 src : %0x08\n", s4.data());
        s4 = std::move(s3);
        printf("s3 : %0x08\n", s3.data());
        printf("s4 : %0x08\n", s4.data());

        cout << "s3 = " << s3 << endl;
        cout << "s4 = " << s4 << endl; 
    }


    return 0;
}

/*
s1 src : 62fdd008
s1 : 62fdd008
s2 : 62fdf008
s1 = hello
s2 = s1

s3 src : 62fdd008
s4 src : 62fdf008
s3 : 62fdd008
s4 : 62fdf008
s3 =
s4 = s3
*/