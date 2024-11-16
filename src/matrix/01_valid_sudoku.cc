#include "01_valid_sudoku.h"
#include <unordered_set>

struct Cell {
  int row, col;
};

int boxIndex(Cell cell) {
  int threeRowBlock = (cell.row / 3);
  int threeRowCol = (cell.col / 3);
  int boxesPerRow = 3;
  return threeRowBlock * boxesPerRow + threeRowCol;
}

class SeenIn {
public:
  void insert(int number, Cell cell) {
    row[cell.row].insert(number);
    col[cell.col].insert(number);
    box[boxIndex(cell)].insert(number);
  }

  bool exists(int number, Cell cell) {
    return !(row[cell.row].count(number) ||
             col[cell.col].count(number) ||
             box[boxIndex(cell)].count(number));
  }

private:
  std::unordered_set<char> row[9];
  std::unordered_set<char> col[9];
  std::unordered_set<char> box[9];
};

bool emptyCell(Cell cell, std::vector<std::vector<char>> &board) {
  return board[cell.row][cell.col] == '.';
}

bool validCell(Cell cell, std::vector<std::vector<char>> &board,
               SeenIn &seenIn) {
  char number = board[cell.row][cell.col];

  if (seenIn.exists(number, cell)) {
    seenIn.insert(number, cell);
    return true;
  }

  return false;
}

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  SeenIn seenIn;

  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board.size(); col++) {
      if (emptyCell(Cell{row, col}, board)) {
        continue;
      }
      if (!validCell(Cell{row, col}, board, seenIn)) {
        return false;
      }
    }
  }
  return true;
}
