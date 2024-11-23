#include "../../src/linked_list/01_linked_list_cycle.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class LinkedListCycleTest : public testing::Test {
protected:
  LinkedListCycle linkedListCycle;
  ListNode head;
};

class LinkedListCycleTestProperty : public LinkedListCycleTest {
protected:

};
