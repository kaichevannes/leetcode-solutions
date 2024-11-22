#include "../../src/hashmap/01_ransom_note.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class RansomNoteTest : public testing::Test {
protected:
  RansomNote ransomNote;
  std::string ransom;
  std::string magazine;
};

TEST_F(RansomNoteTest, oneLengthRansomIsMagazine) {
  ransom = "a";
  magazine = "a";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, oneLengthInvalid) {
  ransom = "a";
  magazine = "b";
  EXPECT_FALSE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, ransomOrderedSubsetOfMagazine) {
  ransom = "abc";
  magazine = "abcdefg";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, ransomOutOfOrderSubsetOfMagazine) {
  ransom = "cba";
  magazine = "abcdefg";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, ransomSubsetOfOutOfOrderMagazine) {
  ransom = "abc";
  magazine = "gfedcba";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, duplicateLettersValid) {
  ransom = "gggggg";
  magazine = "agbgcgdgegfg";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, duplicateLettersInvalid) {
  ransom = "ggggggg";
  magazine = "agbgcgdgegfg";
  EXPECT_FALSE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, sortedRansomAndMagazineDontLineUp) {
  ransom = "ac";
  magazine = "abc";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

class RansomNoteTestProperty : public RansomNoteTest {
protected:
  std::mt19937 rng{std::random_device{}()};

  rc::Gen<std::string> genLowerCaseString() {
    return rc::gen::suchThat(
        rc::gen::container<std::string>(genLowerCaseEnglishLetter()),
        [](std::string str) {
          return str.size() >= 1 && str.size() <= 100000;
        });
  }

private:
  rc::Gen<char> genLowerCaseEnglishLetter() {
    return rc::gen::inRange<char>(97, 122);
  }
};

RC_GTEST_FIXTURE_PROP(RansomNoteTestProperty,
                      FalseWhenMagazineSmallerThanRansom, ()) {
  ransom = *genLowerCaseString();
  magazine = *genLowerCaseString();
  RC_PRE(magazine.size() < ransom.size());

  RC_ASSERT_FALSE(ransomNote.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(RansomNoteTestProperty, TrueWhenRansomIsMagazine, ()) {
  ransom = *genLowerCaseString();
  magazine = ransom;

  RC_ASSERT(ransomNote.canConstruct(ransom, magazine));
  RC_ASSERT(ransomNote.canConstruct(magazine, ransom));
}

RC_GTEST_FIXTURE_PROP(RansomNoteTestProperty, TrueWhenMagazineSupersetOfRansom,
                      ()) {
  ransom = *genLowerCaseString();
  magazine = ransom + *genLowerCaseString();

  std::shuffle(magazine.begin(), magazine.end(), rng);

  RC_ASSERT(ransomNote.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(RansomNoteTestProperty, TrueAfterShufflingMagazine, ()) {
  ransom = *genLowerCaseString();
  magazine = *genLowerCaseString();
  RC_PRE(ransomNote.canConstruct(ransom, magazine));

  std::shuffle(magazine.begin(), magazine.end(), rng);

  RC_ASSERT(ransomNote.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(RansomNoteTestProperty, TrueAfterShufflingRansom, ()) {
  ransom = *genLowerCaseString();
  magazine = *genLowerCaseString();
  RC_PRE(ransomNote.canConstruct(ransom, magazine));

  std::shuffle(ransom.begin(), ransom.end(), rng);

  RC_ASSERT(ransomNote.canConstruct(ransom, magazine));
}

RC_GTEST_FIXTURE_PROP(RansomNoteTestProperty, TrueAfterShufflingRansomAndMagazine, ()) {
  ransom = *genLowerCaseString();
  magazine = *genLowerCaseString();
  RC_PRE(ransomNote.canConstruct(ransom, magazine));

  std::shuffle(ransom.begin(), ransom.end(), rng);
  std::shuffle(magazine.begin(), magazine.end(), rng);

  RC_ASSERT(ransomNote.canConstruct(ransom, magazine));
}
