#include <iostream>
#include <string>
#include <thread>
#include <functional>

using namespace std;

void bar_i() { cout << "hello" << endl; }

int main()
{
    //printf("ehllo");
   printf("bar_i=0x%08x, &bar_i=0x%08x", bar_i, &bar_i);
    return 0;
}
