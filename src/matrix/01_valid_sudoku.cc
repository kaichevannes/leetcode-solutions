#include "01_valid_sudoku.h"
#include <unordered_set>

class SudokuValidator {
private:
  std::vector<std::vector<char>> board;
  std::unordered_set<char> seenInRow[9], seenInCol[9], seenInBox[9];

public:
  SudokuValidator(std::vector<std::vector<char>> &existingBoard)
      : board(existingBoard) {}

  bool validSquare(int row, int col) {
    char number = board[row][col];

    if (emptySquare(number))
      return true;

    if (!isValidNumberPlacement(number, row, col)) {
      return false;
    }

    seen(number, row, col);
    return true;
  }

private:
  bool emptySquare(char squareValue) { return squareValue == '.'; }

  int boxIndex(int row, int col) {
    int threeRowBlock = (row / 3);
    int threeRowCol = (col / 3);
    int boxesPerRow = 3;
    return threeRowBlock * boxesPerRow + threeRowCol;
  }

  bool isValidNumberPlacement(char number, int row, int col) {
    if (seenInRow[row].count(number) || seenInCol[col].count(number) ||
        seenInBox[boxIndex(row, col)].count(number)) {
      return false;
    }
    return true;
  }

  void seen(char number, int row, int col) {
    seenInRow[row].insert(number);
    seenInCol[col].insert(number);
    seenInBox[boxIndex(row, col)].insert(number);
  }
};

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  SudokuValidator validator(board);

  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board.size(); col++) {
      if (!validator.validSquare(row, col)) {
        return false;
      }
    }
  }

  return true;
}
