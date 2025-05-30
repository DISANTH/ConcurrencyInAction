template<typename T>
class my_lock_guard
{    
    public:
        my_lock_guard(T &mu_): mu(mu_)
        {
            mu.lock();
        }

        ~my_lock_guard()
        {
            mu.unlock();
        }
    private:
        T &mu;
        my_lock_guard(const my_lock_guard&) = delete;
        my_lock_guard& operator=(const my_lock_guard&) = delete;
};

int main()
{
    return 0;
}