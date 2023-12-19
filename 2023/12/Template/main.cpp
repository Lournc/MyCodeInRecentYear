#include "unique_ptr.hpp"
#include <iostream>

int main(){
    koarz::unique_ptr<int> ptr1(new int(10));
    koarz::unique_ptr<int> ptr2(new int(20));
    std::cout << *ptr1 << ' ' << *ptr2 << std::endl;
    ptr1.reset(new int(30));
    std::cout << *ptr1 << ' ' << *ptr2 << std::endl;
    return 0;
}