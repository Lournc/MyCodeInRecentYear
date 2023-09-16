#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    const double pi = 3.14;
    int h, r;
    cin >> h >> r;
    cout << ceil(20000 / pi / r / r / h);
    return 0;
}
