#include "solution.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class Test0383 : public testing::Test {
protected:
  Solution solution;
  std::string ransom;
  std::string magazine;
};

TEST_F(Test0383, oneLengthRansomIsMagazine) {
  ransom = "a";
  magazine = "a";
  EXPECT_TRUE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, oneLengthInvalid) {
  ransom = "a";
  magazine = "b";
  EXPECT_FALSE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, ransomOrderedSubsetOfMagazine) {
  ransom = "abc";
  magazine = "abcdefg";
  EXPECT_TRUE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, ransomOutOfOrderSubsetOfMagazine) {
  ransom = "cba";
  magazine = "abcdefg";
  EXPECT_TRUE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, ransomSubsetOfOutOfOrderMagazine) {
  ransom = "abc";
  magazine = "gfedcba";
  EXPECT_TRUE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, duplicateLettersValid) {
  ransom = "gggggg";
  magazine = "agbgcgdgegfg";
  EXPECT_TRUE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, duplicateLettersInvalid) {
  ransom = "ggggggg";
  magazine = "agbgcgdgegfg";
  EXPECT_FALSE(solution.canConstruct(ransom, magazine));
}

TEST_F(Test0383, sortedRansomAndMagazineDontLineUp) {
  ransom = "ac";
  magazine = "abc";
  EXPECT_TRUE(solution.canConstruct(ransom, magazine));
}

class TestProperty0383 : public Test0383 {
protected:
  std::mt19937 rng{std::random_device{}()};

  rc::Gen<std::string> genMagazineFromRansom(std::string ransom) {
    return rc::gen::map(genLowerCaseString(),
                        [this, ransom](std::string additionalLetters) {
                          std::string magazine = ransom + additionalLetters;
                          std::shuffle(magazine.begin(), magazine.end(), rng);
                          return magazine;
                        });
  }

  rc::Gen<std::string> genLowerCaseString() {
    return rc::gen::withSize([this](int size) {
      size = std::max(std::min(size, 100000), 1);
      return rc::gen::container<std::string>(size, genLowerCaseEnglishLetter());
    });
  }

private:
  rc::Gen<char> genLowerCaseEnglishLetter() {
    return rc::gen::inRange<char>('a', 'z');
  }
};

RC_GTEST_FIXTURE_PROP(TestProperty0383, FalseWhenMagazineSmallerThanRansom,
                      ()) {
  ransom = *genLowerCaseString();
  magazine = ransom.substr(0, ransom.size() - 1);
  RC_PRE(magazine.size() < ransom.size());

  RC_ASSERT_FALSE(solution.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(TestProperty0383, TrueWhenRansomIsMagazine, ()) {
  ransom = *genLowerCaseString();
  magazine = ransom;

  RC_ASSERT(solution.canConstruct(ransom, magazine));
  RC_ASSERT(solution.canConstruct(magazine, ransom));
}

RC_GTEST_FIXTURE_PROP(TestProperty0383, TrueWhenMagazineSupersetOfRansom, ()) {
  ransom = *genLowerCaseString();
  magazine = *genMagazineFromRansom(ransom);

  RC_ASSERT(solution.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(TestProperty0383, TrueAfterShufflingMagazine, ()) {
  ransom = *genLowerCaseString();
  magazine = *genMagazineFromRansom(ransom);
  RC_PRE(solution.canConstruct(ransom, magazine));

  std::shuffle(magazine.begin(), magazine.end(), rng);

  RC_ASSERT(solution.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(TestProperty0383, TrueAfterShufflingRansom, ()) {
  ransom = *genLowerCaseString();
  magazine = *genMagazineFromRansom(ransom);
  RC_PRE(solution.canConstruct(ransom, magazine));

  std::shuffle(ransom.begin(), ransom.end(), rng);

  RC_ASSERT(solution.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(TestProperty0383, TrueAfterShufflingRansomAndMagazine,
                      ()) {
  ransom = *genLowerCaseString();
  magazine = *genMagazineFromRansom(ransom);
  RC_PRE(solution.canConstruct(ransom, magazine));

  std::shuffle(ransom.begin(), ransom.end(), rng);
  std::shuffle(magazine.begin(), magazine.end(), rng);

  RC_ASSERT(solution.canConstruct(ransom, magazine));
}
