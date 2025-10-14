#include "solution.h"
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

class Test0141 : public testing::Test {
protected:
  Solution solution;
};

TEST_F(Test0141, FalseForSingleNode) {
  ListNode head = ListNode(0);
  EXPECT_FALSE(solution.hasCycle(&head));
}

TEST_F(Test0141, TrueForSmallestCycle) {
  ListNode head(0);
  ListNode second(1);
  head.next = &second;
  second.next = &head;
  EXPECT_TRUE(solution.hasCycle(&head));
}

namespace rc {
class TestProperty0141 : public Test0141 {
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
    return gen::mapcat(genTerminatingLinkedList(), [](ListNode *head) {
      ListNode *current = head;
      std::vector<ListNode *> nodes;
      while (current != NULL) {
        nodes.push_back(current);
        current = current->next;
      }
      return gen::map(gen::inRange<int>(0, nodes.size()), [nodes](int target) {
        nodes.back()->next = nodes[target];
        return nodes.front();
      });
    });
  }
};

RC_GTEST_FIXTURE_PROP(TestProperty0141, FalseInTermiantingLinkedList, ()) {
  ListNode *head = *genTerminatingLinkedList();
  RC_ASSERT_FALSE(solution.hasCycle(head));
}

RC_GTEST_FIXTURE_PROP(TestProperty0141, TrueWhenListHasCycle, ()) {
  ListNode *head = *genCyclicLinkedList();
  RC_ASSERT(solution.hasCycle(head));
}

} // namespace rc
