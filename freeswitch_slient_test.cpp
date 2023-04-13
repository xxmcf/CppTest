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
using namespace std;

void print_buf(const char* buf, int len) {
    if (!buf || !len) return;
    printf("%02X", (unsigned char)buf[0]);
    for (int i = 1; i < len; i++) {
        printf(" %02X", (unsigned char)buf[i]);
        if ((i+1) % 16 == 0) {
            printf("\n");
        }
    }
}

int main() {

done:
    cout << "0" << endl;

error:
    cout << "1" << endl;
    
    return 0;
}


