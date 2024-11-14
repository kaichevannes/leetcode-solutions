#include "01_valid_palindrome.h"
#include <cctype>
#include <iterator>
#include <regex>

bool recurseEnds(std::string, int, bool);

bool ValidPalindrome::isPalindrome(std::string s) {
  std::transform(begin(s), end(s), begin(s),
                 [](char c) { return std::tolower(c); });
  std::string alphaNumericString;
  std::copy_if(begin(s), end(s), std::back_inserter(alphaNumericString),
               [](char c) { return std::isalnum(c); });
  return recurseEnds(alphaNumericString, 0, true);
}

bool recurseEnds(std::string s, int i, bool acc) {
  if (i == s.length() / 2) {
    return acc;
  }

  bool isPalindrome = s[i] == s[s.length() - i - 1];

  return recurseEnds(s, i+1, acc && isPalindrome);
}
