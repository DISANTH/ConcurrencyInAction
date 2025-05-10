#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

template <typename T>
class threadSafeQueue
{
private:
    mutable std::mutex mu;
    std::condition_variable cv;
    std::queue<T> _queue;

public:
    void push(T &data)
    {
        {
            lock_guard<std::mutex> lk(mu);
            _queue.push(data);
        }

        cv.notify_one();
    }

    void try_pop(T &container)
    {
    }

    bool empty() const
    {
        lock_guard<std::mutex> lk(mu);
        return _queue.empty();
    }

    void wait_and_pop(T &container)
    {
        unique_lock<std::mutex> ulk(mu);
        cv.wait(ulk, [this]()
                { return !_queue.empty(); });

        container = _queue.front();
        _queue.pop();
        ulk.unlock();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        unique_lock<std::mutex> ulk(mu);

        cv.wait(ulk, [this]()
                { !_queue.empty(); });
        
        shared_ptr<T> res(std::make_shared<T>(_queue.front()));
        _queue.pop();
        ulk.unlock();
        return res;
    }

    std::shared_ptr<T> try_pop()
    {
        unique_lock<std::mutex> ulk(mu);
        if(_queue.empty())
        {
            return shared_ptr<T>();
        }
        shared_ptr<T> res(std::make_shared<T>(_queue.front()));
        _queue.pop();
        ulk.unlock();
        return res;
    }
};
static int dataCount = 0;
bool isLastChunk = false;
bool more_data_to_be_processed()
{

    dataCount++;
    if (dataCount > 1000)
    {
        cout << "It is isLastChunk" << endl;
        isLastChunk = true;
        return false;
    }
    else
    {
        return true;
    }
}

threadSafeQueue<int> tSafeQueue;

void data_preparation_thread()
{
    while (more_data_to_be_processed())
    {
        int data = dataCount;
        cout << "Data prepared ==> data :: " << data << endl;
        tSafeQueue.push(data);
    }
}

void data_processing_thread()
{
    while (1)
    {
        int data;
        tSafeQueue.wait_and_pop(data);

        cout << "Data Processed :: " << data << " and isLastChunk :: " << isLastChunk << endl;

        if (isLastChunk && tSafeQueue.empty())
        {
            break;
        }
    }
}

int main()
{
    std::thread dataPrepThread(data_preparation_thread);
    std::thread dataProcessThread(data_processing_thread);

    dataPrepThread.join();
    dataProcessThread.join();
    return 0;
}