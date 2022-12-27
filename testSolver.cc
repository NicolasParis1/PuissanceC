#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
extern "C" {
#include "minmax.h"
#include "Game.h"
}

TEST(testSolver, heuristic_empty_board) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }

    score = heuristic(&board);
    expected_score = 0;

    ASSERT_EQ(score,expected_score);
}

TEST(testSolver, heuristic_no_alignement) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;

    score = heuristic(&board);
    expected_score = 200;

    ASSERT_EQ(score,expected_score);
}

TEST(testSolver, heuristic_aligmenent2_vertical) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;
    board[3+3][4] = 1;

    score = heuristic(&board);
    expected_score = 40000;

    ASSERT_EQ(score,expected_score);
}

TEST(testSolver, heuristic_aligmenent2_horizontal) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;
    board[3+4][3] = 1;

    score = heuristic(&board);
    expected_score = 40000;

    ASSERT_EQ(score,expected_score);
}
