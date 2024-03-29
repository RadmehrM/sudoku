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


public:
    int** userBoard;
    int** board;
    bool GameIsCompleted = false;

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

    bool isGameComplete();

    bool isRowComplete(int row);

    bool isColumnComplete(int col);

    bool isSubgridComplete(int startRow, int startCol);

    void remove_missing_digs();

    void printSudoku();

    void regenerateBoard();

    void regenerateBoard(std::string diff);

    bool solveSudoku();

    bool findUnassignedLocation(int &row, int &col);

    int** getBoard();



};

#endif // BOARD_H
