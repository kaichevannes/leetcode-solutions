#include "../../src/TwoPointers/01_valid_palindrome.h"
#include <gtest/gtest.h>

class ValidPalindromeTest : public testing::Test {
protected:
  ValidPalindrome validPalindrome;
};

TEST_F(ValidPalindromeTest, emptyString) {
  EXPECT_TRUE(validPalindrome.isPalindrome(""));
};

TEST_F(ValidPalindromeTest, twoLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("ss"));
}

TEST_F(ValidPalindromeTest, numberPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("00"));
}

TEST_F(ValidPalindromeTest, twoLengthDifferentCasePaldindome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("bB"));
}

TEST_F(ValidPalindromeTest, twoLengthNotPalindrome) {

  EXPECT_FALSE(validPalindrome.isPalindrome("ql"));
}

TEST_F(ValidPalindromeTest, palindromeWithSpaces) {

  EXPECT_TRUE(validPalindrome.isPalindrome("ab cde fggfe dcb a"));
}

TEST_F(ValidPalindromeTest, palindromeWithPunctuation) {
  EXPECT_TRUE(validPalindrome.isPalindrome("A man, a plan, a canal: Panama"));
}

TEST_F(ValidPalindromeTest, notPalindromeWithPunctuation) {
  EXPECT_FALSE(validPalindrome.isPalindrome("Sentence; normal sentence."));
}

TEST_F(ValidPalindromeTest, singleLengthPalindrome) {
  EXPECT_TRUE(validPalindrome.isPalindrome("Y"));
}

TEST_F(ValidPalindromeTest, letterAndNumberPalindrome) {
  EXPECT_FALSE(validPalindrome.isPalindrome("0P"));
}
