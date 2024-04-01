#ifndef BOARD_H
#define BOARD_H

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Board {
private:
    
    int N;
    int num_of_rows;
    int missing_dig;
    bool pencilMarks[9][9][9];
    bool locked[9][9];
    bool scored[9][9];

public:
    int** userBoard;
    int** board;
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

    void regenerateBoard(std::string diff);

    bool solveSudoku();

    bool findUnassignedLocation(int &row, int &col);

    int** getBoard();

    void initPencilMarks();

    void addPencilMark(int row, int col, int mark);

    void removePencilMark(int row, int col, int mark);

    bool hasPencilMark(int row, int col, int mark);

    bool isLocked(int row, int col); 

    bool isScored(int row, int col); 

    void setScored(int row, int col); 
};

#endif // BOARD_H