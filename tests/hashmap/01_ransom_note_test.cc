#include "../../src/hashmap/01_ransom_note.h"
#include <gtest/gtest.h>

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

