#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *helper(ListNode *l1, ListNode *l2, bool add = false) {
  if (l1 == l2) {
    if (add) {
      return new ListNode(1);
    }
    return nullptr;
  }
  if (l1 == nullptr) {
    int n = l2->val + add;
    if (n > 9) {
      return new ListNode(n % 10, helper(l1, l2->next, true));
    }
    return new ListNode(n, helper(l1, l2->next));
  }
  if (l2 == nullptr) {
    int n = l1->val + add;
    if (n > 9) {
      return new ListNode(n % 10, helper(l1->next, l2, true));
    }
    return new ListNode(n, helper(l1->next, l2));
  }
  int n = l1->val + l2->val + add;
  if (n > 9) {
    return new ListNode(n % 10, helper(l1->next, l2->next, true));
  }
  return new ListNode(n, helper(l1->next, l2->next));
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
  ListNode list;
  list.next = helper(l1, l2);
  return list.next;
}

int main() { return 0; }