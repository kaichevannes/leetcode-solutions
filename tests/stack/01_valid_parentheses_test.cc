#include "../../src/stack/01_valid_parentheses.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class ValidParenthesesTest : public testing::Test {
protected:
  ValidParentheses validParentheses;
  std::string s;
};

TEST_F(ValidParenthesesTest, TrueForEmptyString) {
  EXPECT_TRUE(validParentheses.isValid(""));
}

TEST_F(ValidParenthesesTest, FalseForSingleParentheses) {
  EXPECT_FALSE(validParentheses.isValid("{"));
}

TEST_F(ValidParenthesesTest, TrueForPairOfParentheses) {
  EXPECT_TRUE(validParentheses.isValid("()"));
}

TEST_F(ValidParenthesesTest, FalseForUnclosingParentheses) {
  EXPECT_FALSE(validParentheses.isValid("[]{"));
}

TEST_F(ValidParenthesesTest, TrueForChainOfSelfContainedParentheses) {
  EXPECT_TRUE(validParentheses.isValid("()[]{}"));
}

class ValidParenthesesTestProperty : public ValidParenthesesTest {
protected:
  std::vector<char> parentheses = {'(', ')', '{', '}', '[', ']'};
  std::vector<std::string> parenthesesPairs = {"()", "{}", "[]"};
  std::vector<std::string> openParentheses = {"(","{","["};

  rc::Gen<std::string> genDefaultS() {
    return rc::gen::container<std::string>(rc::gen::elementOf(parentheses));
  }
};

RC_GTEST_FIXTURE_PROP(ValidParenthesesTestProperty,
                      ResultDoesntChangeAfterAddingMatchingParenthesesPair,
                      ()) {
  s = *genDefaultS();
  std::string parenthesesPair = *rc::gen::elementOf(parenthesesPairs);

  RC_ASSERT(validParentheses.isValid(s) ==
            validParentheses.isValid(s + parenthesesPair));
}

RC_GTEST_FIXTURE_PROP(ValidParenthesesTestProperty,
                      FalseWhenAddingIncompleteParentheses, ()) {
  s = *genDefaultS();

  RC_ASSERT_FALSE(validParentheses.isValid(s + *rc::gen::elementOf(openParentheses)));
}
