#include "01_valid_parentheses.h"
#include <stack>
#include <unordered_map>

bool ValidParentheses::isValid(std::string s) {
  if (s.empty())
    return true;

  std::unordered_map<char, char> openingParenthesisFor = {
      {')', '('}, {'}', '{'}, {']', '['}};

  std::stack<char> parens;

  for (char c : s) {
    if (parens.size() > 0 && openingParenthesisFor[c] == parens.top()) {
      parens.pop();
    } else {
      parens.push(c);
    }
  }

  return parens.empty();
}
