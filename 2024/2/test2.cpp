#include <iostream>

int main () {
    int a;
    int &b = a;
    std::cout << &a << ' ' << &b;
}