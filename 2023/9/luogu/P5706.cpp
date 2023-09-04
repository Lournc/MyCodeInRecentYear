#include <iostream>
using namespace std;
int main()
{
    double t, n;
    cin >> t >> n;
    printf("%.3lf\n%d", t / n, int(n * 2));
    return 0;
}