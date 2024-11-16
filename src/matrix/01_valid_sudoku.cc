#include "01_valid_sudoku.h"
#include <unordered_set>

struct Cell {
  int row, col;
};

class SeenIn {
public:
  SeenIn(std::vector<std::vector<char>> &existingBoard)
      : board(existingBoard) {}

  void insert(Cell cell) {
    row[cell.row].insert(number(cell));
    col[cell.col].insert(number(cell));
    box[boxIndex(cell)].insert(number(cell));
  }

  bool exists(Cell cell) {
    return !(row[cell.row].count(number(cell)) ||
             col[cell.col].count(number(cell)) ||
             box[boxIndex(cell)].count(number(cell)));
  }

private:
  std::unordered_set<char> row[9];
  std::unordered_set<char> col[9];
  std::unordered_set<char> box[9];
  std::vector<std::vector<char>> board;

  int number(Cell cell) { return board[cell.row][cell.col]; }

  int boxIndex(Cell cell) {
    int threeRowBlock = (cell.row / 3);
    int threeRowCol = (cell.col / 3);
    int boxesPerRow = 3;
    return threeRowBlock * boxesPerRow + threeRowCol;
  }
};

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  SeenIn seenIn(board);

  auto emptyCell = [&](Cell cell) { return board[cell.row][cell.col] == '.'; };

  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board.size(); col++) {
      if (emptyCell({row, col})) {
        continue;
      }

      if (!seenIn.exists({row, col})) {
        return false;
      }

      seenIn.insert({row, col});
    }
  }
  return true;
}
