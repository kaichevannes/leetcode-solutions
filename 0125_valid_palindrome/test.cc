#include "solution.h"
#include <gtest/gtest.h>
#include <random>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class Test0125 : public testing::Test {
protected:
  Solution solution;
};

TEST_F(Test0125, EmptyString) { EXPECT_TRUE(solution.isPalindrome("")); };

TEST_F(Test0125, TwoLengthPalindrome) {
  EXPECT_TRUE(solution.isPalindrome("ss"));
}

TEST_F(Test0125, NumberPalindrome) { EXPECT_TRUE(solution.isPalindrome("00")); }

TEST_F(Test0125, TwoLengthDifferentCasePaldindome) {
  EXPECT_TRUE(solution.isPalindrome("bB"));
}

TEST_F(Test0125, TwoLengthNotPalindrome) {

  EXPECT_FALSE(solution.isPalindrome("ql"));
}

TEST_F(Test0125, PalindromeWithSpaces) {

  EXPECT_TRUE(solution.isPalindrome("ab cde fggfe dcb a"));
}

TEST_F(Test0125, PalindromeWithPunctuation) {
  EXPECT_TRUE(solution.isPalindrome("A man, a plan, a canal: Panama"));
}

TEST_F(Test0125, NotPalindromeWithPunctuation) {
  EXPECT_FALSE(solution.isPalindrome("Sentence; normal sentence."));
}

TEST_F(Test0125, SingleLengthPalindrome) {
  EXPECT_TRUE(solution.isPalindrome("Y"));
}

TEST_F(Test0125, LetterAndNumberPalindrome) {
  EXPECT_FALSE(solution.isPalindrome("0P"));
}

TEST_F(Test0125, FourLengthPalindrome) {
  EXPECT_TRUE(solution.isPalindrome("abba"));
}

TEST_F(Test0125, FourLengthHalfPalindrome) {
  EXPECT_FALSE(solution.isPalindrome("abca"));
}

class TestProperty0125 : public Test0125 {
protected:
  TestProperty0125() : rng(std::random_device{}()) {}

  rc::Gen<std::string> genEvenPalindrome() {
    return rc::gen::map<std::string>(
        [this](std::string str) { return str + reverse(str); });
  }

  rc::Gen<std::string> genOddPalindrome() {
    return rc::gen::mapcat(genEvenPalindrome(), [this](std::string str) {
      return rc::gen::map<char>([str, this](char middleLetter) {
        return str + middleLetter + reverse(str);
      });
    });
  }

  rc::Gen<std::string> genNonPalindrome() {
    return rc::gen::mapcat(genNonPalindromeAlphaNum(),
                           [this](std::string palindrome) {
                             return interleaveSpecialChars(palindrome);
                           });
  }

private:
  std::mt19937 rng;

  int calcMiddleIndex(const std::string &str) { return str.size() / 2; }

  std::string reverse(const std::string &str) {
    return std::string(str.rbegin(), str.rend());
  }

  rc::Gen<char> genAlphaNumChar() {
    return rc::gen::suchThat(rc::gen::character<char>(),
                             [](char c) { return std::isalnum(c); });
  }

  rc::Gen<std::string> genAlphaNumString(int length) {
    return rc::gen::container<std::string>(length, genAlphaNumChar());
  }

  rc::Gen<char> genSpecialChar() {
    auto isEscapeSequenceChar = [](char c) { return c == '\\'; };
    return rc::gen::suchThat(rc::gen::inRange<char>(33, 127), [&](char c) {
      return !isEscapeSequenceChar(c) && !std::isalnum(c);
    });
  }

  rc::Gen<std::string> genSpecialString() {
    return rc::gen::container<std::string>(genSpecialChar());
  }

  rc::Gen<std::string> genNonPalindromeAlphaNum() {
    return rc::gen::withSize([this](int size) {
      size = std::max(2, size);
      return rc::gen::map(genAlphaNumString(size),
                          [this](std::string alphaNumericString) {
                            return unPalindrome(alphaNumericString);
                          });
    });
  }

  rc::Gen<std::string> interleaveSpecialChars(const std::string &palindrome) {
    return rc::gen::map(genSpecialString(),
                        [palindrome, this](const std::string &specialChars) {
                          return applySpecialCharInterleaving(palindrome,
                                                              specialChars);
                        });
  }

  std::string applySpecialCharInterleaving(std::string str,
                                           const std::string &specialChars) {
    for (char specialChar : specialChars) {
      str.insert(str.begin() + getRandomIndex(str), specialChar);
    }
    return str;
  }

  int getRandomIndex(const std::string &str) {
    std::uniform_int_distribution<int> dist(0, str.size() - 1);
    return dist(rng);
  }

  std::string unPalindrome(std::string alphaNumStr) {
    int lastCharIndex = alphaNumStr.size() - 1;
    auto makeLastCharDifferentFromFirstChar =
        [lastCharIndex](std::string &str) { str[lastCharIndex] = str[0] + 1; };

    makeLastCharDifferentFromFirstChar(alphaNumStr);
    if (!std::isalnum(alphaNumStr[lastCharIndex])) {
      alphaNumStr[lastCharIndex] = 'a';
    }
    return alphaNumStr;
  }
};

RC_GTEST_FIXTURE_PROP(TestProperty0125, ReverseStringGivesSameValue, ()) {
  std::string input = *rc::gen::string<std::string>();
  std::string reverseInput(input.rbegin(), input.rend());
  RC_ASSERT(solution.isPalindrome(input) ==
            solution.isPalindrome(reverseInput));
}

RC_GTEST_FIXTURE_PROP(TestProperty0125, EvenPalindromes, ()) {
  RC_ASSERT(solution.isPalindrome(*genEvenPalindrome()));
}

RC_GTEST_FIXTURE_PROP(TestProperty0125, OddPalindromes, ()) {
  RC_ASSERT(solution.isPalindrome(*genOddPalindrome()));
}

RC_GTEST_FIXTURE_PROP(TestProperty0125, NonPalindromes, ()) {
  RC_ASSERT_FALSE(solution.isPalindrome(*genNonPalindrome()));
}
