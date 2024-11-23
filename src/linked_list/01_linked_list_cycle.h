#ifndef LINKED_LIST_CYCLE_H
#define LINKED_LIST_CYCLE_H

#include <cstddef>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x): val(x), next(NULL) {};
};

class LinkedListCycle {
public:
  bool hasCycle(ListNode*);
};

#endif
