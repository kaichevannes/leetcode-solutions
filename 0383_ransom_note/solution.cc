#include "solution.h"

bool Solution::canConstruct(std::string ransomNote, std::string magazine) {
  for (char c : ransomNote) {
    if (magazine.find(c) == std::string::npos)
      return false;
    magazine.erase(magazine.find(c), 1);
  }
  return true;
}
