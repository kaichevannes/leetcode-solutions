#include "01_valid_parentheses.h"
#include <stack>
#include <unordered_map>

bool ValidParentheses::isValid(std::string s) {
  if (s.empty())
    return true;

  std::unordered_map<char, char> openingParenthesisFor = {
      {')', '('}, {'}', '{'}, {']', '['}};

  std::stack<char> parens;

  for (int i = 0; i < s.size(); i++) {
    if (parens.size() > 0 && openingParenthesisFor[s[i]] == parens.top()) {
      parens.pop();
    } else {
      parens.push(s[i]);
    }
  }

  return parens.empty();
}
