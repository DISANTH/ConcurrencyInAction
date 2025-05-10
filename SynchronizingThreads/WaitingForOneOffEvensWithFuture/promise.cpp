#include <iostream>
#include <thread>
#include <future>

using namespace std;

void hellowWorld()
{
    //cout << "x :: " << x << " y :: " << y << endl;
    cout << "helloWorld"  << endl;
}

int main()
{
    int x = 1, y  = 2;
    packaged_task<void()> task(hellowWorld);
    future<void> myFuture = task.get_future();
    //task();

    cout << "I can do whatever in middle " << endl;
    //myFuture.wait();
    cout << "Ok now result from the thread:: " << endl;
    return 0;
}