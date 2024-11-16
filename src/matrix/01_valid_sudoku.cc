#include "01_valid_sudoku.h"
#include <set>

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  for (std::vector<char> row : board) {
    std::set<char> foundChars;
    for (int j = 0; j < board.size(); j++) {
      char squareValue = row[j];
      if (squareValue != '.' && foundChars.count(squareValue)) {
        return false;
      }
      foundChars.insert(squareValue);
    }
  }

  for (int j = 0; j < board.size(); j++) {
    std::set<char> foundChars;
    for (int i = 0; i < board.size(); i++) {
      char squareValue = board[i][j];
      if (squareValue != '.' && foundChars.count(squareValue)) {
        return false;
      }
      foundChars.insert(squareValue);
    }
  }

  for (int horizontalOffset = 0; horizontalOffset < board.size();
       horizontalOffset += 3) {
    for (int verticalOffset = 0; verticalOffset < board.size();
         verticalOffset += 3) {
      std::set<char> foundChars;
      for (int i = horizontalOffset; i < horizontalOffset + 3; i++) {
        for (int j = verticalOffset; j < verticalOffset + 3; j++) {
          char squareValue = board[i][j];
          if (squareValue != '.' && foundChars.count(squareValue)) {
            return false;
          }
          foundChars.insert(squareValue);
        }
      }
    }
  }

  return true;
}
