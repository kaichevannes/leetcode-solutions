#include "../../src/two_pointers/01_valid_palindrome.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class ValidPalindromeTest : public testing::Test {
protected:
  ValidPalindrome validPalindrome;
};

TEST_F(ValidPalindromeTest, EmptyString) {
  EXPECT_TRUE(validPalindrome.isPalindrome(""));
};

TEST_F(ValidPalindromeTest, TwoLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("ss"));
}

TEST_F(ValidPalindromeTest, NumberPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("00"));
}

TEST_F(ValidPalindromeTest, TwoLengthDifferentCasePaldindome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("bB"));
}

TEST_F(ValidPalindromeTest, TwoLengthNotPalindrome) {

  EXPECT_FALSE(validPalindrome.isPalindrome("ql"));
}

TEST_F(ValidPalindromeTest, PalindromeWithSpaces) {

  EXPECT_TRUE(validPalindrome.isPalindrome("ab cde fggfe dcb a"));
}

TEST_F(ValidPalindromeTest, PalindromeWithPunctuation) {
  EXPECT_TRUE(validPalindrome.isPalindrome("A man, a plan, a canal: Panama"));
}

TEST_F(ValidPalindromeTest, NotPalindromeWithPunctuation) {
  EXPECT_FALSE(validPalindrome.isPalindrome("Sentence; normal sentence."));
}

TEST_F(ValidPalindromeTest, SingleLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("Y"));
}

TEST_F(ValidPalindromeTest, LetterAndNumberPalindrome) {
  EXPECT_FALSE(validPalindrome.isPalindrome("0P"));
}

TEST_F(ValidPalindromeTest, FourLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("abba"));
}

TEST_F(ValidPalindromeTest, FourLengthHalfPalindrome) {
  EXPECT_FALSE(validPalindrome.isPalindrome("abca"));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTest, ReverseStringGivesSameValue, ()) {
  std::string input = *rc::gen::string<std::string>();
  std::string reverseInput(input.rbegin(), input.rend());
  RC_ASSERT(validPalindrome.isPalindrome(input) == validPalindrome.isPalindrome(reverseInput));
}
