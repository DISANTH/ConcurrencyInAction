#include<iostream>
#include <thread>
#include <chrono>
#include <future>

typedef unsigned long long ull;

using namespace std;

void countOdd(std::promise<ull> && oddProm, ull start, ull end)
{
    ull result;
    for(int i = start; i < end; i++)
    {
        if(i & 1)
        {
            result++;
        }
    }
    oddProm.set_value(result);
}

int main()
{
    std::promise<ull> oddProm;
    ull start = 0, end = 1900000000;
    std::future<ull> oddFuture = oddProm.get_future();
    
    std::thread t1(countOdd,std::move(oddProm), start, end);

    cout << "waiting for the result" << endl;
    cout << "result ready result :: " << oddFuture.get() << endl;
    cout << "Completed!!" << endl;
    t1.join();
    return 0;
}