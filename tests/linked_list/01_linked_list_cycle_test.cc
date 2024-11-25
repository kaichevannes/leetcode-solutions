#include "linked_list/01_linked_list_cycle.h"
#include "rapidcheck/gen/Numeric.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

std::ostream &operator<<(std::ostream &os, const ListNode *node) {
  if (node == NULL) {
    os << "NULL";
    return os;
  }
  os << "Node(" << node->val << ") -> " << node->next;
  return os;
}

class LinkedListCycleTest : public testing::Test {
protected:
  LinkedListCycle linkedListCycle;
};

TEST_F(LinkedListCycleTest, FalseForSingleNode) {
  ListNode head = ListNode(0);
  EXPECT_FALSE(linkedListCycle.hasCycle(&head));
}

TEST_F(LinkedListCycleTest, TrueForSmallestCycle) {
  ListNode head(0);
  ListNode second(1);
  head.next = &second;
  second.next = &head;
  EXPECT_TRUE(linkedListCycle.hasCycle(&head));
}

namespace rc {
class LinkedListCycleTestProperty : public LinkedListCycleTest {
protected:
  Gen<ListNode *> genEndNode() {
    return gen::map(gen::arbitrary<int>(),
                    [](int val) { return new ListNode(val); });
  }

  Gen<ListNode *> genTerminatingLinkedList() {
    return gen::apply(
        [](ListNode *node, ListNode *next) {
          node->next = next;
          return node;
        },
        genEndNode(),
        gen::weightedOneOf<ListNode *>(
            {{8, gen::lazy([this] { return genTerminatingLinkedList(); })},
             {2, gen::just(static_cast<ListNode *>(NULL))}}));
  }

  Gen<ListNode *> genCyclicLinkedList() {
    return gen::mapcat(genTerminatingLinkedList(), [](ListNode* head){
      ListNode *current = head;
      std::vector<ListNode*> nodes;
      while (current != NULL) {
        nodes.push_back(current);
        current = current->next;
      }
      return gen::map(gen::inRange<int>(0, nodes.size()), [nodes](int target){
        nodes.back()->next = nodes[target];
        return nodes.front();
      });
    });
  }
};

RC_GTEST_FIXTURE_PROP(LinkedListCycleTestProperty, FalseInTermiantingLinkedList, ()) {
  ListNode *head = *genTerminatingLinkedList();
  RC_ASSERT_FALSE(linkedListCycle.hasCycle(head));
}

RC_GTEST_FIXTURE_PROP(LinkedListCycleTestProperty, TrueWhenListHasCycle, ()) {
  ListNode *head = *genCyclicLinkedList();
  RC_ASSERT(linkedListCycle.hasCycle(head));
}

} // namespace rc
