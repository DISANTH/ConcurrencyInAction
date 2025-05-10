#include <iostream>
#include <future>
#include <chrono>

using namespace std;


int dataProcessThread()
{
    std::chrono::seconds dura( 5);

    cout << "Thread id dataProcessThread()" << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for( dura );
    return 100;
}


int main()
{

    /*
        Here you can set launch type for the function, that is the first argument to the std::async() method

        1. std::launch::deferred // Launch the function whereever wait or get called
        2. std::launch::async // Definately run on background thread
        3. std::launch::deferred || std::launch::aync ==> Implimentation choses and it is the default option
    
     */

     cout << "Thread id mainThread()" << std::this_thread::get_id() << endl;

    //cout << "Thread id dataProcessThread()" << std::this_thread::get_id() << endl;

    std::future<int> value = std::async(std::launch::deferred | std::launch::async, dataProcessThread);
   // value.wait();

   

    for(int i = 0; i < 10; i++)
    {
        cout <<"I can do whateven i wanted in between " << endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
    cout << "value returned from dataProcessThread:: " << value.get() << endl;
    return 0;
}