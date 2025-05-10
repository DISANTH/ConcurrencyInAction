#include <iostream>
#include <vector>
#include <future>

using namespace std;

template<>
class packaged_task<std::string(double,int)>
{
public:
    template<typename Callable>
    explicit packaged_task(Callable&& f);
    std::future<std::string> get_future();
    void operator()(double,int);
};


std::string getData(double dbl, int in)
{
    cout << "getData called with dbl : " << dbl << " in :: " << in << endl;
    cout << "task thread id is :: " << std::this_thread::get_id() <<  endl;
}

int main()
{
    cout << "main function thread id :: " << std::this_thread::get_id() << endl;
    packaged_task<std::string(double,int)> task(getData);
    task(1.12,1);
    return 0;
}