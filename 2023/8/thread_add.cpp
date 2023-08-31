#include <thread>
#include <iostream>
#include <string>
#include <mutex>
using namespace std;
int num{};
mutex m1;
void output(int i)
{
    m1.lock();
    for (int a = 0; a < 100; a++)
        num++;
    m1.unlock();
}

int main()
{
    thread t[10];
    for (int i = 0; i < 10; i++)
    {
        t[i] = thread(output, i);
    }
    for (int i = 0; i < 10; i++)
    {
        t[i].join();
    }
    cout << num;
    return 0;
}