#include <gtest/gtest.h>
#include "../../src/two_pointers/01_valid_palindrome.h"

class ValidPalindromeTest : public testing::Test {
protected:
  ValidPalindrome validPalindrome;
};

TEST_F(ValidPalindromeTest, Unit_emptyString) {
  EXPECT_TRUE(validPalindrome.isPalindrome(""));
};

TEST_F(ValidPalindromeTest, Unit_twoLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("ss"));
}

TEST_F(ValidPalindromeTest, Unit_numberPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("00"));
}

TEST_F(ValidPalindromeTest, Unit_twoLengthDifferentCasePaldindome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("bB"));
}

TEST_F(ValidPalindromeTest, Unit_twoLengthNotPalindrome) {

  EXPECT_FALSE(validPalindrome.isPalindrome("ql"));
}

TEST_F(ValidPalindromeTest, Unit_palindromeWithSpaces) {

  EXPECT_TRUE(validPalindrome.isPalindrome("ab cde fggfe dcb a"));
}

TEST_F(ValidPalindromeTest, Unit_palindromeWithPunctuation) {
  EXPECT_TRUE(validPalindrome.isPalindrome("A man, a plan, a canal: Panama"));
}

TEST_F(ValidPalindromeTest, Unit_notPalindromeWithPunctuation) {
  EXPECT_FALSE(validPalindrome.isPalindrome("Sentence; normal sentence."));
}

TEST_F(ValidPalindromeTest, Unit_singleLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("Y"));
}

TEST_F(ValidPalindromeTest, Unit_letterAndNumberPalindrome) {
  EXPECT_FALSE(validPalindrome.isPalindrome("0P"));
}

TEST_F(ValidPalindromeTest, Unit_fourLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("abba"));
}

TEST_F(ValidPalindromeTest, Unit_fourLengthHalfPalindrome) {
  EXPECT_FALSE(validPalindrome.isPalindrome("abca"));
}
