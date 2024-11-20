#include "../../src/two_pointers/01_valid_palindrome.h"
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

class ValidPalindromeTestProperty : public ValidPalindromeTest {
protected:
  rc::Gen<std::string> genEvenPalindrome() {
    return rc::gen::map<std::string>([](std::string firstHalf) {
      std::string secondHalf(firstHalf.rbegin(), firstHalf.rend());
      return firstHalf + secondHalf;
    });
  }

  rc::Gen<std::string> genOddPalindrome() {
    return rc::gen::mapcat(genEvenPalindrome(), [this](std::string palindrome) {
      return rc::gen::map<char>([this, palindrome](char middleLetter) {
        std::string oddPalindrome = palindrome;
        int middleIndex = calcMiddleIndex(oddPalindrome);
        oddPalindrome.insert(oddPalindrome.begin() + middleIndex, middleLetter);
        return oddPalindrome;
      });
    });
  }

  rc::Gen<std::string> genNonPalindrome() {
    return rc::gen::mapcat(
        genNonPalindromeAlphaNum(), [this](std::string palindrome) {
          return rc::gen::map(
              genSpecialString(), [palindrome](std::string specialChars) {
                std::string finalPalindrome = palindrome;
                for (char specialChar : specialChars) {
                  std::random_device rd;
                  std::mt19937 rng(rd());
                  std::uniform_int_distribution<int> dist(0, palindrome.size() -
                                                                 1);
                  finalPalindrome.insert(finalPalindrome.begin() + dist(rng),
                                         specialChar);
                }
                return finalPalindrome;
              });
        });
  }

private:
  int calcMiddleIndex(std::string str) { return str.size() / 2; }

  rc::Gen<char> genAlphaNumChar() {
    return rc::gen::suchThat(rc::gen::character<char>(),
                             [](char c) { return std::isalnum(c); });
  }

  rc::Gen<std::string> genAlphaNumString(int length) {
    return rc::gen::container<std::string>(length, genAlphaNumChar());
  }

  rc::Gen<char> genSpecialChar() {
    return rc::gen::suchThat(rc::gen::inRange<char>(33, 127), [](char c) {
      return c != '\\' && !std::isalnum(c);
    });
  }

  rc::Gen<std::string> genSpecialString() {
    return rc::gen::container<std::string>(genSpecialChar());
  }

  rc::Gen<std::string> genNonPalindromeAlphaNum() {
    return rc::gen::withSize([this](int size) {
      size = std::max(2, size);
      return rc::gen::map(genAlphaNumString(size), unPalindrome);
    });
  }

  static std::string unPalindrome(std::string str) {
    std::string nonPalindrome = str;
    nonPalindrome[str.size() - 1] = nonPalindrome[0] + 1;
    if (!std::isalnum(nonPalindrome[0] + 1)) {
      nonPalindrome[str.size() - 1] = 'a';
    }
    return nonPalindrome;
  }
};

RC_GTEST_FIXTURE_PROP(ValidPalindromeTestProperty, ReverseStringGivesSameValue,
                      ()) {
  std::string input = *rc::gen::string<std::string>();
  std::string reverseInput(input.rbegin(), input.rend());
  RC_ASSERT(validPalindrome.isPalindrome(input) ==
            validPalindrome.isPalindrome(reverseInput));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTestProperty, EvenPalindromes, ()) {
  RC_ASSERT(validPalindrome.isPalindrome(*genEvenPalindrome()));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTestProperty, OddPalindromes, ()) {
  RC_ASSERT(validPalindrome.isPalindrome(*genOddPalindrome()));
}

RC_GTEST_FIXTURE_PROP(ValidPalindromeTestProperty, NonPalindromes, ()) {
  RC_ASSERT_FALSE(validPalindrome.isPalindrome(*genNonPalindrome()));
}
