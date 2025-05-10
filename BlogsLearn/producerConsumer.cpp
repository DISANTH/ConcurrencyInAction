#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

mutex mu;
condition_variable con_variable;
constexpr int MAX_BUFF_SIZE = 11;

queue<int> dataQueue;

void producer(int value)
{
    unique_lock<std::mutex> ulk(mu);
    con_variable.wait(ulk,[](){return dataQueue.size() < MAX_BUFF_SIZE;});
    dataQueue.push(value);
    cout << "Produced value : " << value << endl;
    ulk.unlock();
    con_variable.notify_one();
}

void consumer()
{
    unique_lock<std::mutex> ulk(mu);
    con_variable.wait(ulk,[](){return dataQueue.size() > 0;});
    int data = dataQueue.front();
    dataQueue.pop();
    cout << "Consumed Data :: " << data <<  endl;
    ulk.unlock();
    con_variable.notify_one();
}

int main()
{
    thread producerThread([](){
        for(int i = 0; i < 300; i++)
        {
            producer(i);
        }
    });

    this_thread::sleep_for(chrono::seconds(10));

    thread consumerThread([](){
        for(int i = 0; i < 300; i++)
        {
            consumer();
        }
    });

    producerThread.join();
    consumerThread.join();
    return 0;
}