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

int boxIndex(Cell cell) {
  int threeRowBlock = (cell.row / 3);
  int threeRowCol = (cell.col / 3);
  int boxesPerRow = 3;
  return threeRowBlock * boxesPerRow + threeRowCol;
}

void seen(char number, Cell cell, SeenIn &seenIn) {
  seenIn.row[cell.row].insert(number);
  seenIn.col[cell.col].insert(number);
  seenIn.box[boxIndex(cell)].insert(number);
}

bool emptyCell(Cell cell, std::vector<std::vector<char>> &board) {
  return board[cell.row][cell.col] == '.';
}

bool validNumber(char number, Cell cell, SeenIn &seenIn) {
  return !(seenIn.row[cell.row].count(number) ||
           seenIn.col[cell.col].count(number) ||
           seenIn.box[boxIndex(cell)].count(number));
}

bool validCell(Cell cell, std::vector<std::vector<char>> &board,
               SeenIn &seenIn) {
  char number = board[cell.row][cell.col];

  if (validNumber(number, cell, seenIn)) {
    seen(number, cell, seenIn);
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
