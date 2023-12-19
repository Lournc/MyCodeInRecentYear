#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    std::random_device rd;  // 将用于获得随机数引擎的种子
    std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
    std::uniform_real_distribution<> dis(1, 20);
    vector<double> n(10);
    cout << dis(gen) << endl;
    for (auto i = n.begin(); i != n.end(); i++)
        *i = dis(gen);
    for (double v : n)
        cout << setw(10) << std::setprecision(8) << v << ' ';
    return 0;
}