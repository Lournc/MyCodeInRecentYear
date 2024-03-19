#include <iostream>
using namespace std;
int arr[100000];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    arr[i] -= a;
  }
  return 0;
}