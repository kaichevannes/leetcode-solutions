#include "../../src/hashmap/01_ransom_note.h"
#include <gtest/gtest.h>

class RansomNoteTest : public testing::Test {
protected:
  RansomNote ransomNote;
  std::string ransom;
  std::string magazine;
};

TEST_F(RansomNoteTest, Unit_oneLengthRansomIsMagazine) {
  ransom = "a";
  magazine = "a";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_oneLengthInvalid) {
  ransom = "a";
  magazine = "b";
  EXPECT_FALSE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_ransomOrderedSubsetOfMagazine) {
  ransom = "abc";
  magazine = "abcdefg";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_ransomOutOfOrderSubsetOfMagazine) {
  ransom = "cba";
  magazine = "abcdefg";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_ransomSubsetOfOutOfOrderMagazine) {
  ransom = "abc";
  magazine = "gfedcba";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_duplicateLettersValid) {
  ransom = "gggggg";
  magazine = "agbgcgdgegfg";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_duplicateLettersInvalid) {
  ransom = "ggggggg";
  magazine = "agbgcgdgegfg";
  EXPECT_FALSE(ransomNote.canConstruct(ransom, magazine));
}

TEST_F(RansomNoteTest, Unit_sortedRansomAndMagazineDontLineUp) {
  ransom = "ac";
  magazine = "abc";
  EXPECT_TRUE(ransomNote.canConstruct(ransom, magazine));
}

