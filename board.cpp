#include "board.h"

using namespace std;

//Helper Functions//

// The function checks if a specific number is used in a box
// This can be used to check whether a number can be inputted into a 3x3 box as a valid move
bool Board::unUsedInBox(int row, int col, int num) {
    for (int i = 0; i < num_of_rows; i++) {
            for (int j = 0; j < num_of_rows; j++) {
                if (board[row + i][col + j] == num) {
                    return false;
                }
            }
        }
        return true;
}

// This function can generate a random number between 1 and 9 for the puzzle generator
int randomGenerator(int n) {
    return (int)floor((float)(rand() / double(RAND_MAX) * n + 1));
}

bool Board::CheckIfSafe(int i, int j, int num)
    {
        return (
            unUsedInRow(i, num) && unUsedInCol(j, num)
            && unUsedInBox(i - i % num_of_rows, j - j % num_of_rows, num));
    }

bool Board::unUsedInRow(int i, int num)
    {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
        return true;
    }
    // check in the row for existence
    bool Board::unUsedInCol(int j, int num)
    {
        for (int i = 0; i < N; i++) {
            if (board[i][j] == num) {
                return false;
            }
        }
        return true;
    }

//


Board::Board(int rows, int M) {
    N = rows;
    missing_dig = M;

    double num_of_rowsD = sqrt(N);
    num_of_rows = (int)num_of_rowsD;
    board = new int*[N];


    for (int i = 0; i < N; i++) {
        board[i] = new int[N];
        memset(board[i], 0, N * sizeof(int));
    }

    userBoard = board;
    
}


void Board::fillBoard() {
    fillDiagonal();
    fillRemaining( 0, num_of_rows);
    remove_missing_digs();
}

void Board::fillDiagonal() {
    for (int i = 0; i < N; i = i+ num_of_rows) {

        fillBox(i,i);

    }
}


void Board::fillBox(int row, int col) {
    int num;
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < num_of_rows; j++) {
                do {
                    num = randomGenerator(N);
                } while (!unUsedInBox(row, col, num));
                board[row + i][col + j] = num;
        }
    }
}

bool Board::fillRemaining(int i, int j) {
        // System.out.println(i+" "+j);
        if (j >= N && i < N - 1) {
            i = i + 1;
            j = 0;
        }
        if (i >= N && j >= N) {
            return true;
        }
        if (i < num_of_rows) {
            if (j < num_of_rows) {
                j = num_of_rows;
            }
        }
        else if (i < N - num_of_rows) {
            if (j == (int)(i / num_of_rows) * num_of_rows) {
                j = j + num_of_rows;
            }
        }
        else {
            if (j == N - num_of_rows) {
                i = i + 1;
                j = 0;
                if (i >= N) {
                    return true;
                }
            }
        }
        for (int num = 1; num <= N; num++) {
            if (CheckIfSafe(i, j, num)) {
                board[i][j] = num;
                if (fillRemaining(i, j + 1)) {
                    return true;
                }
                board[i][j] = 0;
            }
        }
        return false;
    }


    void Board::remove_missing_digs(){
        int count = missing_dig;
        while (count != 0) {
            int cellId = randomGenerator(N * N) - 1;
            // System.out.println(cellId);
            // extract coordinates i and j
            int i = (cellId / N);
            int j = cellId % N;
            if (j != 0) {
                j = j - 1;
            }
            // System.out.println(i+" "+j);
            if (board[i][j] != 0) {
                count--;
                board[i][j] = 0;
            }
        }
    }


    void Board::printSudoku(){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << to_string(board[i][j]) + " ";
            }
            cout << endl;
        }
        cout << endl;

    }

    void Board::resetBoard() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                board[i][j] = 0;
        }
    }
    }

    void Board::regenerateBoard() {
    // Reset the board first
    resetBoard();

    // Now fill the board again with new values
    fillDiagonal();
    fillRemaining(0, num_of_rows);
    remove_missing_digs();
    }

bool Board::solveSudoku() {
    int row, col;

    // If there is no unassigned location, we are done
    if (!findUnassignedLocation(row, col))
       return true; // success!

    // Consider digits 1 to N
    for (int num = 1; num <= N; num++) {
        // If looks promising
        if (CheckIfSafe(row, col, num)) {
            // Make tentative assignment
            board[row][col] = num;

            // Return, if success, yay!
            if (solveSudoku())
                return true;

            // Failure, unmake & try again
            board[row][col] = 0;
        }
    }
    return false; // This triggers backtracking
}

bool Board::findUnassignedLocation(int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (board[row][col] == 0)
                return true;
    return false;
}

int** Board::getBoard() {
    return board;
}





    
int main() {
    int N = 9;
    int K = 20; //number of blank boxes
    Board* sudoku = new Board(N, K);

    sudoku->userBoard = new int*[N];

    for (int i = 0; i < N; i++) {
    sudoku->userBoard[i] = new int[N];
    for(int j = 0; j < N; j++) {
        sudoku->userBoard[i][j] = sudoku->board[i][j];
    }
    }
    
    sudoku->fillBoard();
    sudoku->printSudoku();
    cout << to_string(sudoku->userBoard[0][0]) << endl;
    if (sudoku->solveSudoku())
        cout << to_string(sudoku->userBoard[0][0]) << endl;
        sudoku->printSudoku(); // If the puzzle is solvable, print the solution

    return 0;
}

