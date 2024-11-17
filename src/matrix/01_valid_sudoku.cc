#include "01_valid_sudoku.h"
#include <cassert>
#include <cctype>
#include <unordered_set>

constexpr int GRID_SIZE = 9;
constexpr int BOX_SIZE = 3;

struct Cell {
  int row, col;
};

class SudokuRuleChecker {
public:
  SudokuRuleChecker(std::vector<std::vector<char>> &existingBoard)
      : board(existingBoard) {}

  void addToValidationState(Cell cell) {
    seenInRow[cell.row].insert(number(cell));
    seenInCol[cell.col].insert(number(cell));
    seenInBox[boxIndex(cell)].insert(number(cell));
  }

  bool isAllowed(Cell cell) const {
    return !(seenInRow[cell.row].count(number(cell)) ||
             seenInCol[cell.col].count(number(cell)) ||
             seenInBox[boxIndex(cell)].count(number(cell)));
  }

private:
  std::unordered_set<char> seenInRow[GRID_SIZE], seenInCol[GRID_SIZE],
      seenInBox[GRID_SIZE];
  std::vector<std::vector<char>> board;

  int number(Cell cell) const {
    assert(std::isdigit(board[cell.row][cell.col]));
    return board[cell.row][cell.col] - '0';
  }

  int boxIndex(Cell cell) const {
    int threeRowBlockIndex = (cell.row / BOX_SIZE);
    int threeRowColIndex = (cell.col / BOX_SIZE);
    int boxesPerRow = BOX_SIZE;
    return threeRowBlockIndex * boxesPerRow + threeRowColIndex;
  }
};

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  assert(board.size() == GRID_SIZE && board[0].size() == GRID_SIZE);

  SudokuRuleChecker sudokuRuleChecker(board);

  auto emptyCell = [&](Cell cell) { return board[cell.row][cell.col] == '.'; };

  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board.size(); col++) {
      if (emptyCell(Cell{row, col})) {
        continue;
      }
      if (!sudokuRuleChecker.isAllowed(Cell{row, col})) {
        return false;
      }
      sudokuRuleChecker.addToValidationState(Cell{row, col});
    }
  }
  return true;
}
