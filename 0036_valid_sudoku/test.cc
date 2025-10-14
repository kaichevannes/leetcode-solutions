#include "solution.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class Test0036 : public testing::Test {
protected:
  Solution solution;
  std::vector<std::vector<char>> board;
};

TEST_F(Test0036, EmptyBoard) {
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
  EXPECT_TRUE(solution.isValidSudoku(board));
};

TEST_F(Test0036, DiagonalBoard) {
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
  EXPECT_TRUE(solution.isValidSudoku(board));
}

TEST_F(Test0036, InvalidRow) {
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
  EXPECT_FALSE(solution.isValidSudoku(board));
}

TEST_F(Test0036, MultipleInvalidRows) {
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
  EXPECT_FALSE(solution.isValidSudoku(board));
}

TEST_F(Test0036, InvalidColumn) {
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
  EXPECT_FALSE(solution.isValidSudoku(board));
}

TEST_F(Test0036, MultipleInvalidColumns) {
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
  EXPECT_FALSE(solution.isValidSudoku(board));
}

TEST_F(Test0036, InvalidSubBox) {
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
  EXPECT_FALSE(solution.isValidSudoku(board));
}

TEST_F(Test0036, MultipleInvalidSubBoxes) {
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
  EXPECT_FALSE(solution.isValidSudoku(board));
}

TEST_F(Test0036, ValidSudoku) {
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
  EXPECT_TRUE(solution.isValidSudoku(board));
}

class TestProperty0036 : public Test0036 {
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

RC_GTEST_FIXTURE_PROP(TestProperty0036, ValidAfterIncrementingNonEmptyCells,
                      ()) {
  auto board = defaultBoard();
  RC_PRE(solution.isValidSudoku(board));

  auto incrementCellValue = [](char c) -> char {
    if (c == '.') {
      return '.';
    }
    return c == '9' ? '1' : c + 1;
  };

  for (std::vector<char> &row : board) {
    std::transform(row.begin(), row.end(), row.begin(), incrementCellValue);
  }

  RC_ASSERT(solution.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(TestProperty0036, ValidAfterFlippingLeftToRight, ()) {
  auto board = defaultBoard();
  RC_PRE(solution.isValidSudoku(board));

  for (std::vector<char> &row : board) {
    std::reverse(row.begin(), row.end());
  }

  RC_ASSERT(solution.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(TestProperty0036, ValidAfterFlippingTopToBottom, ()) {
  auto board = defaultBoard();
  RC_PRE(solution.isValidSudoku(board));

  std::reverse(board.begin(), board.end());

  RC_ASSERT(solution.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(TestProperty0036,
                      ValidAfterShufflingRowsInEachThreeRowBlock, ()) {
  auto board = defaultBoard();
  RC_PRE(solution.isValidSudoku(board));

  for (int band = 0; band < 3; band++) {
    auto rng = std::mt19937{std::random_device{}()};
    std::shuffle(board.begin() + band * 3, board.begin() + (band + 1) * 3, rng);
  }

  RC_ASSERT(solution.isValidSudoku(board));
}

RC_GTEST_FIXTURE_PROP(TestProperty0036, InvalidWhenMoreThanNineOfTheSameNumber,
                      ()) {
  char value = *rc::gen::elementOf(nonEmptyCellValues);
  auto board =
      *genBoard(rc::gen::oneOf<char>(rc::gen::just('.'), rc::gen::just(value)));

  int totalNonEmptyElements = 0;
  for (std::vector<char> row : board) {
    totalNonEmptyElements +=
        std::accumulate(row.begin(), row.end(), 0, [](int sum, char c) {
          return sum + (c == '.' ? 0 : 1);
        });
  }
  RC_PRE(totalNonEmptyElements > 9);

  RC_ASSERT(!solution.isValidSudoku(board));
}
