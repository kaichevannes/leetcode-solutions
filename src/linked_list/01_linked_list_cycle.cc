#include "01_linked_list_cycle.h"
#include <unordered_set>

bool LinkedListCycle::hasCycle(ListNode *head) {
  std::unordered_set<ListNode*> seen;
  ListNode* current = head;

  while (current != NULL) {
    if (seen.count(current)) return true;
    seen.insert(current);
    current = current->next;
  }
  return false;
}
