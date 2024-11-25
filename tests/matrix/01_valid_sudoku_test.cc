#include "matrix/01_valid_sudoku.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class ValidSudokuTest : public testing::Test {
protected:
  ValidSudoku validSudoku;
  std::vector<std::vector<char>> board;
};

TEST_F(ValidSudokuTest, EmptyBoard) {
  board = {
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
  };
  EXPECT_TRUE(validSudoku.isValidSudoku(board));
};

TEST_F(ValidSudokuTest, DiagonalBoard) {
  board = {
      {'1', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '2', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '3', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '4', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '5', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '6', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '7', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '8', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '9'},
  };
  EXPECT_TRUE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, InvalidRow) {
  board = {
      {'1', '.', '.', '1', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
  };
  EXPECT_FALSE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, MultipleInvalidRows) {
  board = {
      {'1', '.', '.', '1', '.', '.', '1', '.', '.'},
      {'.', '2', '2', '.', '2', '.', '.', '2', '.'},
      {'3', '3', '3', '.', '.', '3', '3', '.', '.'},
      {'.', '4', '.', '.', '.', '.', '.', '.', '4'},
      {'5', '.', '.', '.', '5', '.', '.', '.', '5'},
      {'.', '.', '.', '.', '.', '.', '6', '6', '.'},
      {'.', '.', '7', '7', '.', '.', '7', '7', '.'},
      {'8', '.', '.', '.', '.', '.', '.', '.', '8'},
      {'9', '9', '9', '9', '9', '9', '9', '9', '9'},
  };
  EXPECT_FALSE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, InvalidColumn) {
  board = {
      {'1', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'1', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
  };
  EXPECT_FALSE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, MultipleInvalidColumns) {
  board = {
      {'1', '2', '.', '4', '.', '6', '7', '.', '9'},
      {'.', '2', '3', '.', '5', '.', '.', '8', '9'},
      {'.', '.', '3', '4', '.', '.', '.', '8', '9'},
      {'1', '.', '3', '.', '.', '6', '.', '8', '9'},
      {'.', '.', '.', '.', '5', '.', '.', '8', '9'},
      {'.', '2', '3', '4', '5', '.', '.', '8', '9'},
      {'1', '.', '.', '4', '.', '.', '.', '8', '9'},
      {'.', '.', '.', '.', '.', '.', '.', '8', '9'},
      {'.', '2', '3', '4', '5', '6', '7', '.', '9'},
  };
  EXPECT_FALSE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, InvalidSubBox) {
  board = {
      {'.', '.', '.', '.', '.', '.', '.', '1', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '1'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
  };
  EXPECT_FALSE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, MultipleInvalidSubBoxes) {
  board = {
      {'1', '.', '.', '1', '2', '3', '8', '.', '.'},
      {'.', '1', '.', '3', '.', '.', '7', '8', '.'},
      {'.', '.', '1', '.', '.', '.', '.', '.', '.'},
      {'2', '4', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '3', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '4', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '6', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '6', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '6', '.', '.', '.'},
  };
  EXPECT_FALSE(validSudoku.isValidSudoku(board));
}

TEST_F(ValidSudokuTest, ValidSudoku) {
  board = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
  };
  EXPECT_TRUE(validSudoku.isValidSudoku(board));
}

class ValidSudokuTestProperty : public ValidSudokuTest {
protected:
  std::vector<char> nonEmptyCellValues{'1', '2', '3', '4', '5',
                                       '6', '7', '8', '9'};

  std::vector<std::vector<char>> defaultBoard() {
    return *genBoard(genCellChar());
  }

  rc::Gen<std::vector<std::vector<char>>>
  genBoard(const rc::Gen<char> &cellChar) {
    return rc::gen::container<std::vector<std::vector<char>>>(
        9, rc::gen::container<std::vector<char>>(9, cellChar));
  }

private:
  rc::Gen<char> genCellChar() {
    return rc::gen::weightedOneOf<char>(
        {{5, rc::gen::just<char>('.')},
         {1, rc::gen::elementOf(nonEmptyCellValues)}});
  }
};

RC_GTEST_FIXTURE_PROP(ValidSudokuTestProperty,
                      ValidAfterIncrementingNonEmptyCells, ()) {
  auto board = defaultBoard();
  RC_PRE(validSudoku.isValidSudoku(board));

  auto incrementCellValue = [](char c) -> char {
    if (c == '.') {
      return '.';
    }
    return c == '9' ? '1' : c + 1;
  };

  for (std::vector<char> &row : board) {
    std::transform(row.begin(), row.end(), row.begin(), incrementCellValue);
  }

  RC_ASSERT(validSudoku.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(ValidSudokuTestProperty, ValidAfterFlippingLeftToRight,
                      ()) {
  auto board = defaultBoard();
  RC_PRE(validSudoku.isValidSudoku(board));

  for (std::vector<char> &row : board) {
    std::reverse(row.begin(), row.end());
  }

  RC_ASSERT(validSudoku.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(ValidSudokuTestProperty, ValidAfterFlippingTopToBottom,
                      ()) {
  auto board = defaultBoard();
  RC_PRE(validSudoku.isValidSudoku(board));

  std::reverse(board.begin(), board.end());

  RC_ASSERT(validSudoku.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(ValidSudokuTestProperty,
                      ValidAfterShufflingRowsInEachThreeRowBlock, ()) {
  auto board = defaultBoard();
  RC_PRE(validSudoku.isValidSudoku(board));

  for (int band = 0; band < 3; band++) {
    auto rng = std::mt19937{std::random_device{}()};
    std::shuffle(board.begin() + band * 3, board.begin() + (band + 1) * 3, rng);
  }

  RC_ASSERT(validSudoku.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(ValidSudokuTestProperty,
                      InvalidWhenMoreThanNineOfTheSameNumber, ()) {
  char value = *rc::gen::elementOf(nonEmptyCellValues);
  auto board =
      *genBoard(rc::gen::oneOf<char>(rc::gen::just('.'),
      rc::gen::just(value)));

  int totalNonEmptyElements = 0;
  for (std::vector<char> row : board) {
    totalNonEmptyElements +=
        std::accumulate(row.begin(), row.end(), 0, [](int sum, char c) {
          return sum + (c == '.' ? 0 : 1);
        });
  }
  RC_PRE(totalNonEmptyElements > 9);

  RC_ASSERT(!validSudoku.isValidSudoku(board));
}
