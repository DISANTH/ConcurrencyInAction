#include <iostream>
#include <functional>

using namespace std;

class DATA
{
    public:
        int data;
};

void changeVal(int x)
{
    x = 10;
}
int main()
{
    int a = 100;
    std::reference_wrapper<int> ref = std::ref(a);
    cout << a << endl;
    return 0;
}