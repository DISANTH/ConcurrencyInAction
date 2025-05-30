#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;
bool isNextOneEven{false};
mutex mu;
std::binary_semaphore oddSemaphore{1},evenSemaphore{0};

/*
// Code using semaphore's
void printOddNumbers(int limit)
{
    for(int i = 1; i <= limit; i += 2)
    {
        oddSemaphore.acquire();
        cout << i << " ";
        evenSemaphore.release();
    }
}

void printEvenNumbers(int limit)
{
     for(int i = 2; i <= limit; i += 2)
    {
        evenSemaphore.acquire();
        cout << i << " ";
        oddSemaphore.release();
    }
}
*/

void printOddNumbers(unsigned long long limit)
{
    for(int i = 1; i <= limit; i += 2)
    {
        unique_lock<mutex> ulk(mu);
        cv.wait(ulk,[](){return !isNextOneEven;});        
        cout << i << " ";        
        isNextOneEven = true;
        ulk.unlock();
        cv.notify_one();
    }
}

void printEvenNumbers(unsigned long long limit)
{
    for(int i = 2; i <= limit; i += 2)
    {
        unique_lock<mutex> ulk(mu);
        cv.wait(ulk,[](){return isNextOneEven;});        
        cout << i << " ";
        isNextOneEven = false;
        ulk.unlock();
        cv.notify_one();
    }
}

int main()
{
    unsigned long long limit;
    cin >> limit;
    thread evenThread(printOddNumbers,10000);
    thread oddThread(printEvenNumbers,10000);

    evenThread.join();
    oddThread.join();
    return 0;
}
