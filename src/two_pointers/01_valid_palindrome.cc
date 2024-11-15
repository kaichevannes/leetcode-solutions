#include "01_valid_palindrome.h"
#include <cctype>
#include <iterator>
#include <regex>

std::string filterAlphaNumericCharacters(std::string);
bool tailRecursiveIsPalindrome(std::string&, int, bool);

bool ValidPalindrome::isPalindrome(std::string s) {
  std::transform(begin(s), end(s), begin(s),
                 [](char c) { return std::tolower(c); });
  std::string alphaNumericString = filterAlphaNumericCharacters(s);
  return tailRecursiveIsPalindrome(alphaNumericString, 0, true);
}

std::string filterAlphaNumericCharacters(std::string s) {
  std::string result;
  std::copy_if(begin(s), end(s), std::back_inserter(result),
               [](char c) { return std::isalnum(c); });
  return result;
}

bool tailRecursiveIsPalindrome(std::string &s, int currentIndexInS,
                               bool accumulator) {
  bool checkedAllPairsOrOneLetterRemaining = currentIndexInS == s.length() / 2;
  
  if (checkedAllPairsOrOneLetterRemaining) {
    return accumulator;
  }

  int lastIndexInS = s.length() - 1;
  bool iHasMatchingLetter =
      s[currentIndexInS] == s[lastIndexInS - currentIndexInS];

  return tailRecursiveIsPalindrome(s, currentIndexInS + 1,
                                   accumulator && iHasMatchingLetter);
}
