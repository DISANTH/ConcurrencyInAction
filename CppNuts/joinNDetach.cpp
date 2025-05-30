#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void run(int x)
{
    while(x --> 0)
    {
        cout << "Disanth" << endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

int main()
{
    thread t1(run,10);
    t1.detach();
    if(t1.joinable())
        t1.join();
    cout << "From main Function " <<  endl;
    return 0;
}