#include <iostream>



class mycallback {
public:

    virtual void refresh() = 0;
	
	virtual void complete() = 0;
	
	virtual void start() = 0;

protected:
    ~mycallback() {
        std::cout << "~mycallback" << std::endl;
    }
};

class ascallback : public mycallback {
public:

    virtual void refresh() override {

    }
	
	virtual void complete() override{
        
        delete this;
	}
	
	virtual void start() override {

    };

};

class threadcallback : public mycallback {
public:

    virtual void refresh() override {

    }
	
	virtual void complete() override{
        
        delete this;
	}
	
	virtual void start() override {

    };

    virtual void run() {
        isFinished = false;
        start();
        while (!isFinished) {
             refresh();
        }
        complete();
       
    }

protected:
    bool isFinished;

};

class mytask{

public:

	void setListener(mycallback* cb) {
		cb_ = cb;
	}

	void shutdown() {
		cb_->complete();
	}

public:
    mycallback* cb_;

};

int main() {

	std::cout << "enter app!" << std::endl;
	mytask task;
    mycallback* cb = new ascallback;

    std::cout << "cb=" << cb << std::endl;
	task.setListener(cb);
	task.shutdown();
    std::cout << "cb=" << cb << std::endl;
	std::cout << "exit app!" << std::endl;
	return 0;
}
/* output
cb=0x632550
~mycallback
cb=0x632550
exit app!
*/