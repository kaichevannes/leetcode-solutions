#include "01_ransom_note.h"
#include <algorithm>

bool RansomNote::canConstruct(std::string ransomNote, std::string magazine) {
  std::sort(ransomNote.begin(), ransomNote.end());
  std::sort(magazine.begin(), magazine.end());
  return (magazine.find(ransomNote) != std::string::npos);
}
