#include <iostream>
#include <thread>

using namespace std;

void callBasicFunction()
{

}

// Functor

class LongRunningOperation
{
    public:
        void operator()(int x)
        {
            cout << "LongRunningOperation called with x :: " << x << " threadID :: " << std::this_thread::get_id() << endl;
        }
};

void functorExample()
{
    std::thread t1(LongRunningOperation(),10);
    t1.join();
}


class LongRunningOperation2
{
    public:
        void run(int x)
        {
            cout << "LongRunningOperation2::run called with x :: " << x << " threadID :: " << std::this_thread::get_id() << endl;
        }
};

void callingMethodInClass()
{
    LongRunningOperation2 op2;
    std::thread t1(&LongRunningOperation2::run,op2,10);
    t1.join();
}

void lambdaFunctionsExample()
{
    auto lamda1 = [](int x){
        cout << "Called Lamda Function with Arguments x :: " << x << endl;
    };
    thread t1(lamda1,101);
    t1.join();

    thread t2([](int x){
        cout << "Called Lamda2 Function with Arguments x :: " << x << endl;
    }, 102);
    t2.join();
}

int main()
{
    cout << "Main thread id :: " << std::this_thread::get_id() << endl;
    //functorExample();
    //callingMethodInClass();
    lambdaFunctionsExample();
    return 0;
}