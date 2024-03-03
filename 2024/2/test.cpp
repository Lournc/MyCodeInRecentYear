#include <iostream>

using namespace std;

struct A {
    int data;
    int& operator*() {
        return data;
    }
};
int main() {
    A a;
    *a = 10;
    std::cout << *a;
    *a = 20;
    std::cout << *a;
}