#include "shared_ptr.hpp"
#include "unique_ptr.hpp"
#include <iostream>

int main() {
  koarz::unique_ptr<int> ptr1(new int(10));
  koarz::unique_ptr<int> ptr2(new int(20));
  std::cout << *ptr1 << ' ' << *ptr2 << std::endl;
  ptr1.reset(new int(30));
  std::cout << *ptr1 << ' ' << *ptr2 << std::endl;
  koarz::unique_ptr<int> null_ptr1;
  koarz::shared_ptr<int> ptr3(new int(10));
  std::cout << *ptr3 << " ptr_cout: " << ptr3.get_count() << std::endl;
  {
    koarz::shared_ptr<int> ptr4(ptr3);
    *ptr4 = 50;
    std::cout << *ptr4 << " ptr_cout: " << ptr4.get_count() << std::endl;
  }
  std::cout << *ptr3 << " ptr_cout: " << ptr3.get_count() << std::endl;
  koarz::shared_ptr<int> null_ptr2;
  return 0;
}