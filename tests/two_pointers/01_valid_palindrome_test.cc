#include "../../src/two_pointers/01_valid_palindrome.h"
#include "rapidcheck/gen/Arbitrary.h"
#include "rapidcheck/gen/Transform.h"
#include <gtest/gtest.h>
#include <random>
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

rc::Gen<std::string> genEvenPalindrome() {
  return rc::gen::map<std::string>([](std::string firstHalf) {
    std::string secondHalf(firstHalf.rbegin(), firstHalf.rend());
    return firstHalf + secondHalf;
  });
}

rc::Gen<std::string> genOddPalindrome() {
  std::string middleLetter = {*rc::gen::character<char>()};
  return rc::gen::map(genEvenPalindrome(),
                      [middleLetter](std::string palindrome) {
                        int middleIndex = palindrome.size() / 2;
                        palindrome.insert(middleIndex, middleLetter);
                        return palindrome;
                      });
}

rc::Gen<std::string> genNonPalindrome() {
  rc::Gen<char> genAlphaNumChar = rc::gen::suchThat(
      rc::gen::character<char>(), [](char c) { return std::isalnum(c); });
  rc::Gen<std::string> genAlphaNumString =
      rc::gen::container<std::string>(genAlphaNumChar);
  rc::Gen<std::string> genNonPalindromeAlphaNumString =
      rc::gen::withSize([=](int size) {
        if (size < 2) {
          size = 2;
        }
        return rc::gen::mapcat(
            rc::gen::container<std::string>(size, genAlphaNumChar),
            [](std::string str) {
              return rc::gen::map(
                  rc::gen::inRange<int>(0, str.size() / 2), [str](int index) {
                    std::string nonPalindrome = str;
                    int indexToChange = str.size() - index - 1;
                    if (!std::isalnum(nonPalindrome[index] + 1)) {
                      nonPalindrome[indexToChange] = 'a';
                    } else {
                      nonPalindrome[indexToChange] = nonPalindrome[index] + 1;
                    }
                    return nonPalindrome;
                  });
            });
      });

  rc::Gen<char> genSpecialChar =
      rc::gen::suchThat(rc::gen::inRange<char>(33, 127),
                        [](char c) { return c != '\\' && !std::isalnum(c); });
  rc::Gen<std::string> genSpecialString =
      rc::gen::container<std::string>(genSpecialChar);

  return rc::gen::mapcat(
      genNonPalindromeAlphaNumString, [=](std::string palindrome) {
        return rc::gen::map(genSpecialString, [palindrome](
                                                  std::string specialChars) {
          std::string finalPalindrome = palindrome;
          for (char specialChar : specialChars) {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> dist(0, palindrome.size() - 1);
            finalPalindrome.insert(finalPalindrome.begin() + dist(rng),
                                   specialChar);
          }
          return finalPalindrome;
        });
      });
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTest, ReverseStringGivesSameValue, ()) {
  std::string input = *rc::gen::string<std::string>();
  std::string reverseInput(input.rbegin(), input.rend());
  RC_ASSERT(validPalindrome.isPalindrome(input) ==
            validPalindrome.isPalindrome(reverseInput));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTest, EvenPalindromes, ()) {
  RC_ASSERT(validPalindrome.isPalindrome(*genEvenPalindrome()));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTest, OddPalindromes, ()) {
  RC_ASSERT(validPalindrome.isPalindrome(*genOddPalindrome()));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTest, NonPalindromes, ()) {
  RC_ASSERT_FALSE(validPalindrome.isPalindrome(*genNonPalindrome()));
}
