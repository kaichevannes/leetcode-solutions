#include "01_valid_parentheses.h"
#include <stack>
#include <unordered_map>

bool ValidParentheses::isValid(std::string s) {
  if (s.empty())
    return true;

  std::unordered_map<char, char> openingParenthesisFor = {
      {')', '('}, {'}', '{'}, {']', '['}};
  std::stack<char> unmatchedParentheses;

  auto closesOpenedParenthesis = [&](char c) {
    return openingParenthesisFor[c] == unmatchedParentheses.top();
  };

  for (char c : s) {
    if (!unmatchedParentheses.empty() && closesOpenedParenthesis(c)) {
      unmatchedParentheses.pop();
    } else {
      unmatchedParentheses.push(c);
    }
  }

  return unmatchedParentheses.empty();
}
