#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
extern "C" {
#include "minmax.h"
#include "Game.h"
}

TEST(testHeuristic, heuristic_empty_board) {
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

TEST(testHeuristic, heuristic_no_alignement) {
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

TEST(testHeuristic, heuristic_aligmenent2_vertical) {
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
    expected_score = 30000;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent3_vertical) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;
    board[3+3][4] = 1;
    board[3+3][5] = 1;

    score = heuristic(&board);
    expected_score = 900000;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent4_vertical) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;
    board[3+3][4] = 1;
    board[3+3][5] = 1;
    board[3+3][6] = 1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}


TEST(testHeuristic, heuristic_aligmenent2_horizontal) {
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

TEST(testHeuristic, heuristic_aligmenent3_horizontal_side) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+0][3] = 1;
    board[3+1][3] = 1;
    board[3+2][3] = 1;

    score = heuristic(&board);
    expected_score = 900000;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent3_horizontal_middle) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+2][3] = 1;
    board[3+3][3] = 1;
    board[3+4][3] = 1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent4_horizontal) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+0][3] = 1;
    board[3+1][3] = 1;
    board[3+2][3] = 1;
    board[3+3][3] = 1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent4_diagonal_up) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+0][3] = 1;
    board[3+1][3+1] = 1;
    board[3+2][3+2] = 1;
    board[3+3][3+3] = 1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent4_diagonal_down) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;
    board[3+2][3+1] = 1;
    board[3+1][3+2] = 1;
    board[3+0][3+3] = 1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent3_diagonal_down_side) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3] = 1;
    board[3+2][3+1] = 1;
    board[3+1][3+2] = 1;
    board[3+0][3+2] = -1;   //support

    score = heuristic(&board);
    expected_score = 900000-40; //-40 because of the support

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent3_diagonal_up_side) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3][3] = 1;
    board[3+1][3+1] = 1;
    board[3+2][3+2] = 1;
    board[3+3][3+2] = -1;

    score = heuristic(&board);
    expected_score = 900000-200;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent3_diagonal_down_middle) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+3][3+1] = 1;
    board[3+2][3+2] = 1;
    board[3+1][3+3] = 1;
    board[3+0][3+3] = -1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_aligmenent3_diagonal_up_middle) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+1][3+1] = 1;
    board[3+2][3+2] = 1;
    board[3+3][3+3] = 1;
    board[3+4][3+3] = -1;

    score = heuristic(&board);
    expected_score = 999999999;

    ASSERT_EQ(score,expected_score);
}

TEST(testHeuristic, heuristic_custom0) {
    int score, expected_score;

    int board[WIDTH+6][HEIGHT+6];
    for (int x = 0; x < WIDTH+6; ++x) {
        for (int y = 0; y < HEIGHT+6; ++y) {
            board[x][y] = 0;
        }
    }
    board[3+1][3+0] = 1;
    board[3+2][3+0] = -1;
    board[3+3][3+0] = 1;
    board[3+5][3+0] = 1;
    board[3+6][3+0] = -1;

    board[3+1][3+1] = 1;
    board[3+2][3+1] = 1;
    board[3+3][3+1] = 1;
    board[3+5][3+1] = -1;

    board[3+1][3+2] = -1;
    board[3+2][3+2] = 1;
    board[3+3][3+2] = -1;
    board[3+5][3+2] = -1;

    board[3+3][3+3] = 1;
    board[3+5][3+3] = -1;

    //board[3+5][3+4] = -1;

    score = heuristic(&board);
    expected_score = 19680;

    ASSERT_EQ(score,expected_score);
}