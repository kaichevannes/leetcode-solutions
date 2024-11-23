#include "../../src/linked_list/01_linked_list_cycle.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

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

// namespace rc {
//
// template <> struct Arbitrary<ListNode> {
//   static Gen<ListNode> arbitrary() {
//     return gen::build<ListNode>(gen::set(&ListNode::val),
//                                 gen::set(&ListNode::next, gen::just(-1)));
//   }
// };
// } // namespace rc
//
// class LinkedListCycleTestProperty : public LinkedListCycleTest {
// protected:
//
// };

// RC_GTEST_FIXTURE_PROP(LinkedListCycleTestProperty, )
