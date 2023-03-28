#include <future>
#include <iostream>
#include <functional>

class AsyncObject
{
public:
    AsyncObject(std::function<int(int i)> func, int i) {
        func_ = std::move(func);
        param_ = i;
    }
    void asyc() {
        fut_ = std::async(func_, param_);
        std::thread th([&]{
            fut_.get();
            delete this;
        });
        th.detach();
    }

protected:
    ~AsyncObject() {
        std::cout << " ~AsyncObject " << std::endl;
    };
    std::future<int> fut_;
    std::function<int(int i)> func_;
    int param_;
};

void myasync(AsyncObject* ao) {
    ao->asyc();
}


int main() {

    {
       std::future<int> foo, bar;
        foo = std::async([]() { return 10; });
        bar = std::move(foo);
    
        if (foo.valid()) std::cout << "foo's value: " << foo.get() << '\n';
        else std::cout << "foo is not valid\n"; // foo is not valid
    
        if (bar.valid()) std::cout << "bar's value: " << bar.get() << '\n'; // 10
        
        //output
	    //foo is not valid 
    }
    {
        // share
        std::future<int> fut = std::async([]() { return 10; });
        std::shared_future<int> shfut = fut.share();
        
        //std::cout << "value: " << fut.get() << '\n';  //报错：std::future_error: No associated state
        // crash, 执行完fut.share()后，fut对象将变得无效
        std::cout << "fut valid: " << fut.valid() << '\n';// 0
        
        // shared futures can be accessed multiple times:
        std::cout << "value: " << shfut.get() << '\n'; // 10
        // 20, 对于std::shared_future对象，get函数可以被多次访问
        std::cout << "its double: " << shfut.get() * 2 << '\n'; 

        //output
        // fut valid: 0
        // value: 10
        // its double: 20
    }
    [](){
        // future from a packaged_task
        std::packaged_task<int()> task([] { return 7; }); // wrap the function
        std::future<int> f1 = task.get_future(); // get a future
        std::thread t(std::move(task)); // launch on a thread
        
        // future from an async()
        std::future<int> f2 = std::async(std::launch::async, [] { return 8; });
        
        std::cout << "Waiting..." <<  std::flush;
        f1.wait();
        f2.wait();
        std::cout << "Done!\nResults are: " << f1.get()
            << ' ' << f2.get() << ' ' << '\n';
        t.join();
    }();

    auto initiazer = [](std::promise<int> * promObj) {
        std::cout << "Inside Thread" << std::endl;
        promObj->set_value(35);
    };

    [&]()
    {
        std::promise<int> promiseObj;
        std::future<int> futureObj = promiseObj.get_future();
        std::thread th(initiazer, &promiseObj);
        std::cout << "value: " << futureObj.get() << std::endl;
        th.join();
        
        // If std::promise object is destroyed before setting the value 
        // the calling get() function on associated std::future object will throw exception.
        
        // A part from this, if you want your thread to return multiple values 
        // at different point of time then
        
        // just pass multiple std::promise objects in thread 
        // and fetch multiple return values from thier associated multiple std::future objects.

    }();
    std::future<int> fut;
    std::packaged_task<int()> task;
    /*
    {
        // fut = std::async(std::launch::async, []() { 
        //     std::cout << "0000000000" << std::endl;
        //     std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        //     std::cout << "1111111111" << std::endl;
        //     return 0;
        // });

         // future from a packaged_task
        std::packaged_task<int()> task1([] { 
            std::cout << "0000000000" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << "1111111111" << std::endl;
            return 0;
         }); // wrap the function
        task = std::move(task1);
        //fut = task.get_future(); // get a future
        std::thread t(std::move(task)); // launch on a thread
        t.detach();

        std::cout << "before exit future!" << std::endl;
       
    }*/
    {
        int a = 9;
        std::cout << "enter myasync!" << std::endl;
        myasync(new AsyncObject([&](int) {
            std::cout << "0000000000" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << "1111111111" << a << std::endl;
            return 0;
        }, 8));
        std::cout << "before exit myasync!" << std::endl;
         //getchar();
    }
    std::cout << "before exit app!" << std::endl;
     getchar();
    std::cout << "exit app!" << std::endl;

    //output
    // enter myasync!
    // 0000000000
    // before exit myasync!
    // 1111111111
    // ~AsyncObject 

    //output
    // before exit future!
    // before exit app!
    // 0000000000
    // 1111111111

    // exit app!
}
