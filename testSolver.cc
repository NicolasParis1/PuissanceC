#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern "C" {
#include "solver.h"
}

TEST(testSolver, Negamax) {
    string line;
    ifstream myfile ("/home/nicolas/Documents/Cours/3A/Dev info/PuissanceC/Test_L3_R1");
    int n_test=1;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) ) {
            int position[42];
            for (int i = 0; i < 42; ++i) {
                position[i] = -1;
            }
            int j=0;
            int expected_score;

            std::string delimiter = " ";
            std::string gauche = line.substr(0, line.find(delimiter));

            for(int i=0;i<gauche.length();i++){
                position[i] = gauche[i] - '0' - 1;
                j=i;
            }

            line.erase(0, j + 2);

            if (line[0] == '-')
                expected_score = line[1] - 50;
            else
                expected_score = line[0] - 48;

            int score = negamax_start(position);

            ASSERT_EQ(expected_score, score);
            std::cout << "test " << n_test <<" passed ! score : "<< score << std::endl;
            n_test++;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
/*
    int position[43];
    for (int i = 0; i < 43; ++i) {
        position[i] = -1;
    }

    char str[42] = "2252576253462244111563365343671351441";
    int i =0;
    while(str[i]!='\0') {
        position[i] = str[i]-48;
        i++;
    }

    for (int j = 0; j < 43; ++j) {
        printf("%d",position[j]);
    }

    int score = negamax(position,0);

    ASSERT_EQ(score,)
    */
}
