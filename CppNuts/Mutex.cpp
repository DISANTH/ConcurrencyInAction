#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int myAmount = 0;
mutex mu;

template<typename T>
class my_lock_guard
{
    
    public:
        my_lock_guard(T &mu_): mu(mu_)
        {
            mu.lock();
        }

        ~my_lock_guard()
        {
            mu.unlock();
        }
    private:
        T &mu;
        my_lock_guard(const my_lock_guard&) = delete;
        my_lock_guard& operator=(const my_lock_guard&) = delete;
};

void addMoney()
{
    my_lock_guard<std::mutex> tg(mu);
    for(int i = 0 ; i < 100000; i++)
    {
        ++myAmount;
    }
}


void tryAddMoney()
{
    for(int i = 0 ; i < 100000; i++)
    {
        if(mu.try_lock())
        {
            ++myAmount;
            mu.unlock();
        }            
    }
}

int main()
{
    std::thread t1(tryAddMoney);
    std::thread t2(tryAddMoney);

    t1.join();
    t2.join();

    cout << "myAmount :: " << myAmount << endl;

    return 0;
}