#include "../../src/linked_list/01_linked_list_cycle.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

void PrintTo(const ListNode* node, std::ostream* os) {
  *os << "Node(" << node->val << ")";
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
  Gen<ListNode> genEndNode() {
    return gen::construct<ListNode>(gen::arbitrary<int>());
  }

  Gen<ListNode> genTerminatingLinkedList() {
    return gen::mapcat(genEndNode(), [this](ListNode node) {
      return gen::weightedOneOf<ListNode>(
          {{8, genTerminatingLinkedList()}, {2, gen::just(node)}});
    });
  }
};

RC_GTEST_FIXTURE_PROP(LinkedListCycleTestProperty, Test, ()) {
  ListNode head = *genTerminatingLinkedList();
  RC_ASSERT(linkedListCycle.hasCycle(&head));
}

} // namespace rc
