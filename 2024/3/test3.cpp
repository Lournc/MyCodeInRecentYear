#include<iostream>
constexpr int add(int a, int b) {
    return a + b;
}
int main() {
    std::cout << add(500, 6000);
    std::cout << add(250, 1000);
    int a, b;
    std::cin >> a >> b;
    std::cout << add(a, b);
}