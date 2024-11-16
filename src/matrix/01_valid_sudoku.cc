#include "01_valid_sudoku.h"
#include <unordered_set>

struct SeenIn {
  std::unordered_set<char> row[9];
  std::unordered_set<char> col[9];
  std::unordered_set<char> box[9];
};

struct Cell {
  int row, col;
};

int boxIndex(int row, int col) {
  int threeRowBlock = (row / 3);
  int threeRowCol = (col / 3);
  int boxesPerRow = 3;
  return threeRowBlock * boxesPerRow + threeRowCol;
}

void seen(char number, int row, int col, SeenIn &seenIn) {
  seenIn.row[row].insert(number);
  seenIn.col[col].insert(number);
  seenIn.box[boxIndex(row, col)].insert(number);
}

bool emptySquare(char squareValue) { return squareValue == '.'; }

bool isValidNumberPlacement(char number, int row, int col, SeenIn &seenIn) {
  if (seenIn.row[row].count(number) || seenIn.col[col].count(number) ||
      seenIn.box[boxIndex(row, col)].count(number)) {
    return false;
  }
  return true;
}

bool validCell(Cell cell, std::vector<std::vector<char>> &board,
                 SeenIn &seenIn) {
  char number = board[cell.row][cell.col];

  if (emptySquare(number))
    return true;

  if (!isValidNumberPlacement(number, cell.row, cell.col, seenIn)) {
    return false;
  }

  seen(number, cell.row, cell.col, seenIn);
  return true;
}

bool ValidSudoku::isValidSudoku(std::vector<std::vector<char>> &board) {
  SeenIn seenIn;

  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board.size(); col++) {
      if (!validCell(Cell{row, col}, board, seenIn)) {
        return false;
      }
    }
  }
  return true;
}
