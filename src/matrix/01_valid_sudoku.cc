#include "01_valid_sudoku.h"
#include <set>

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  std::set<char> seenInRow[9], seenInCol[9], seenInBox[9];

  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board.size(); col++) {
      char number = board[row][col];

      bool emptySquare = number == '.';
      if (emptySquare) continue;

      int box = (row / 3) * 3 + (col / 3);
      if (seenInRow[row].count(number) || seenInCol[col].count(number) || seenInBox[box].count(number)) {
        return false;
      }

      seenInRow[row].insert(number);
      seenInCol[col].insert(number);
      seenInBox[box].insert(number);
    }
  }

  return true;
}
