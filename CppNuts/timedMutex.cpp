#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
std::timed_mutex tmu;

int myAmount = 0;

void increment(int i)
{
    if(tmu.try_lock_for(std::chrono::seconds(3)))
    {
        cout << " increment get mutex " << std::this_thread::get_id() << " i :: " << i << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        myAmount += i;
        tmu.unlock();
        cout << "myAmount :: " << myAmount << endl;
    }
    else{
        cout << "Timed mutex not available with in 1 sec from thread :: " << std::this_thread::get_id() << " i :: " << i << endl; 
    }
}

int main()
{
    std::thread t1([](int x){
        for(int i = 0; i < 10; i++)
        {
            increment(x);
        }
    },1);
    std::thread t2([](int x){
        for(int i = 0; i < 10; i++)
        {
            increment(x);
        }
    },2);
    t1.join();
    t2.join();
    return 0;
}