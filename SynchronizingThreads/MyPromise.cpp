#include <iostream>
#include <thread>
#include <future>

using namespace std;

typedef unsigned long long ULL;

template<typename T>
class MyPromise
{
    private:
        future<T> &fut;
    public:

        MyPromise(): fut(future<T>())
        {

        }

        MyPromise(const MyPromise&) = delete;
        MyPromise& operator(const MyPromise&) = delete;

        MyPromise(MyPromise&& other): fut(std::move(other.fut))
        {
        }

        void set_value(T value)
        {
            
        }

        void get()
        {
            fut.get();
        }
}

void calculateIncrement(MyPromise<ULL> promise, ULL )
{
    promise
}

int main()
{
    MyPromise<ULL> promise;
    thread t(calculateIncrement, std::move(promise),)
    return 0;
}