#ifndef BOARD_H
#define BOARD_H

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Board {
private:
    int** board;
    int N;

    int num_of_rows;
    int missing_dig;


public:
    int** userBoard;
    // Default constructor
    Board(int N, int missing_dig);

    // Member function to reset the board
    void resetBoard();

    // Member function to fill the board
    void fillBoard();

    void fillDiagonal();

    void fillBox(int i, int j);

    bool fillRemaining(int i, int j);

    bool unUsedInBox(int i, int j, int num);

    bool unUsedInRow(int i, int num);

    bool unUsedInCol(int j, int num);

    bool CheckIfSafe(int i, int j, int num);

    void remove_missing_digs();

    void printSudoku();

    void regenerateBoard();

    bool solveSudoku();

    bool findUnassignedLocation(int &row, int &col);

    int** getBoard();



    // Destructor
    ~Board();
};

#endif // BOARD_H
