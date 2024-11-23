#include "../../src/stack/01_valid_parentheses.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class ValidParenthesesTest : public testing::Test {
protected:
  ValidParentheses validParentheses;
  std::string s;
};

class ValidParenthesesTestProperty : public ValidParenthesesTest {
protected:
  std::vector<char> parentheses = {'(', ')', '{', '}', '[', ']'};
  std::vector<std::string> parenthesesPairs = {"()", "{}", "[]"};

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
