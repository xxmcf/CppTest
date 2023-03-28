#include <thread>
#include <iostream>

using namespace std;

int main() {
    auto tf = [&](){
           thread::id tid = this_thread::get_id();
           cout << " tid=" << tid <<endl;
       };
     thread(tf).detach();
       this_thread::sleep_for(chrono::milliseconds(1000));
    return 0;
}
