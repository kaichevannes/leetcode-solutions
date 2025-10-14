#include "solution.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class Test0020 : public testing::Test {
protected:
  Solution solution;
  std::string s;
};

TEST_F(Test0020, TrueForEmptyString) { EXPECT_TRUE(solution.isValid("")); }

TEST_F(Test0020, FalseForSingleParentheses) {
  EXPECT_FALSE(solution.isValid("{"));
}

TEST_F(Test0020, TrueForPairOfParentheses) {
  EXPECT_TRUE(solution.isValid("()"));
}

TEST_F(Test0020, FalseForUnclosingParentheses) {
  EXPECT_FALSE(solution.isValid("[]{"));
}

TEST_F(Test0020, TrueForChainOfSelfContainedParentheses) {
  EXPECT_TRUE(solution.isValid("()[]{}"));
}

class TestProperty0020 : public Test0020 {
protected:
  std::vector<char> parentheses = {'(', ')', '{', '}', '[', ']'};
  std::vector<std::string> parenthesesPairs = {"()", "{}", "[]"};
  std::vector<std::string> openParentheses = {"(", "{", "["};

  rc::Gen<std::string> genDefaultS() {
    return rc::gen::container<std::string>(rc::gen::elementOf(parentheses));
  }
};

RC_GTEST_FIXTURE_PROP(TestProperty0020,
                      ResultDoesntChangeAfterAddingMatchingParenthesesPair,
                      ()) {
  s = *genDefaultS();
  std::string parenthesesPair = *rc::gen::elementOf(parenthesesPairs);

  RC_ASSERT(solution.isValid(s) == solution.isValid(s + parenthesesPair));
}

RC_GTEST_FIXTURE_PROP(TestProperty0020, FalseWhenAddingIncompleteParentheses,
                      ()) {
  s = *genDefaultS();

  RC_ASSERT_FALSE(solution.isValid(s + *rc::gen::elementOf(openParentheses)));
}
