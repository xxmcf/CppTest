#include <iostream>
#include <string>

using namespace std;

struct A
{
    int val;
    A() {}
    A(int v) : val(v) {
        cout << "construct: val=" << val << endl;
    }
    ~A() {
        cout << "destroy: val=" << val << endl;
    }
};


int main() {
    A *p = new A[10];

    for (int i =0; i < 10; i++) {
        p[i].val = i;
    }
    printf("p[0]=0x%08x\n", &p[0]);
    printf("p=0x%08x\n", p);

    delete []p;

    return 0;
}

/**
destroy: val=9
destroy: val=8
destroy: val=7
destroy: val=6
destroy: val=5
destroy: val=4
destroy: val=3
destroy: val=2
destroy: val=1
destroy: val=0
 * 
 */