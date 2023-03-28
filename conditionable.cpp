#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>
#include <iostream>
#include <stdio.h>

std::mutex mutex;
std::condition_variable cv;
std::vector<int> vec;

void Consume()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::unique_lock<std::mutex> lock(mutex);
    // while (vec.empty())// 加入此while判断条件，这样可以防止虚假唤醒的问题， 也可以防止唤醒丢失
    // {
    //     cv.wait(lock);
    // }
    cv.wait(lock, []() { // 使用lamda表达式，这样可以防止虚假唤醒的问题， 也可以防止唤醒丢失
        std::cout << "wait ... "
                     "\n";
        return !vec.empty();
    });
    std::cout << "consume " << vec.size() << "\n";
}

void Produce()
{
    std::unique_lock<std::mutex> lock(mutex); //使用锁可以防止唤醒丢失
    vec.push_back(1);
    cv.notify_all();
    std::cout << "produce \n";
}

int main()
{

    std::thread t(Consume);
    t.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Produce();
    std::cout << "press any key to exit...\n";
    getchar();
    return 0;
}

/*output
wait ...
produce
press any key to exit...
wait ...
consume 1
*/