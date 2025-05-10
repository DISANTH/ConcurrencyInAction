#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;


bool flag;
std::mutex m;
std::condition_variable cv;
bool processed = false;
bool ready = false;
string data;

// void wait_for_flag()
// {
//     std::unique_lock<std::mutex> lk(m);
//     while(!flag)
//     {
//         lk.unlock();                                                  
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Very difficult to set the right sleep time
//         lk.lock();                                                    
//     }
// }

/*
    Best Approach is with waiting for an conditionn with condition variable
*/

/* An Example from cpp reference */

void worker_thread(int x, double y)
{
    cout << "x :: " << x << " : y :: "  << y << endl;
    unique_lock<std::mutex> ulk(m);

    cv.wait(ulk,[](){return ready;});

    cout << "Data processed from worker thread" << endl;

    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    processed = true;

    std::cout << "Worked thread Data processing done" << endl;

    ulk.unlock();
    cv.notify_one();
}

int cppReferenceCV_exapmle()
{
    std::thread worker(worker_thread, 1, 0.5);

    data += "Example Data";

    {
        lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
    // wait for the worker

    {
        unique_lock<std::mutex> ulk(m);
        cv.wait(ulk,[](){return processed;});
    }

    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
    return 0;
}

int main()
{
    cppReferenceCV_exapmle();
    return 0;
}