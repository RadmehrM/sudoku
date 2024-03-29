#include "board.h"
#include <vector>

using namespace std;

/**
 * @brief Checks if a specific number is used in a box.
 * 
 * This function can be used to check whether a number can be inputted into a 3x3 box as a valid move.
 * 
 * @param row The row index of the box.
 * @param col The column index of the box.
 * @param num The number to be checked.
 * @return true if the number is not used in the box, false otherwise.
 */
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

/**
 * @brief Generates a random number between 1 and n.
 * 
 * @param n The upper limit for the random number (inclusive).
 * @return A random number between 1 and n.
 */
int randomGenerator(int n) {
    return (int)floor((float)(rand() / double(RAND_MAX) * n + 1));
}

/**
 * @brief Checks if it's safe to place a number in the given position.
 * 
 * @param i The row index.
 * @param j The column index.
 * @param num The number to be placed.
 * @return true if it's safe to place the number, false otherwise.
 */
bool Board::CheckIfSafe(int i, int j, int num) {
    return (
        unUsedInRow(i, num) && unUsedInCol(j, num)
        && unUsedInBox(i - i % num_of_rows, j - j % num_of_rows, num));
}

/**
 * @brief Checks if a number is unused in the given row.
 * 
 * @param i The row index.
 * @param num The number to be checked.
 * @return true if the number is not used in the row, false otherwise.
 */
bool Board::unUsedInRow(int i, int num) {
    for (int j = 0; j < N; j++) {
        if (board[i][j] == num) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Checks if a number is unused in the given column.
 * 
 * @param j The column index.
 * @param num The number to be checked.
 * @return true if the number is not used in the column, false otherwise.
 */
bool Board::unUsedInCol(int j, int num) {
    for (int i = 0; i < N; i++) {
        if (board[i][j] == num) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Constructs a Board object with the specified number of rows and missing digits.
 * 
 * @param rows The number of rows in the board.
 * @param M The number of missing digits.
 */
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

/**
 * @brief Fills the board with a valid Sudoku puzzle.
 */
void Board::fillBoard() {
    fillDiagonal();
    fillRemaining(0, num_of_rows);
    remove_missing_digs();
}

/**
 * @brief Fills the diagonal blocks of the board with random numbers.
 */
void Board::fillDiagonal() {
    for (int i = 0; i < N; i = i + num_of_rows) {
        fillBox(i, i);
    }
}

/**
 * @brief Fills a 3x3 box of the board with random numbers.
 * 
 * @param row The starting row index of the box.
 * @param col The starting column index of the box.
 */
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

/**
 * @brief Fills the remaining cells of the board recursively.
 * 
 * @param i The current row index.
 * @param j The current column index.
 * @return true if the board is filled, false otherwise.
 */
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

/**
 * @brief Removes randomly selected digits from the board.
 */
void Board::remove_missing_digs() {
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

/**
 * @brief Prints the Sudoku board.
 */
void Board::printSudoku() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << to_string(board[i][j]) + " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief Resets the Sudoku board to its initial state.
 */
void Board::resetBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
}

/**
 * @brief Regenerates the Sudoku board with new values.
 */
void Board::regenerateBoard() {
    // Reset the board first
    resetBoard();

    // Now fill the board again with new values
    fillDiagonal();
    fillRemaining(0, num_of_rows);
    remove_missing_digs();
}

void Board::regenerateBoard(std::string diff) {
    if (diff == "Easy") {
        missing_dig = 10;
    }
    if (diff == "Medium") {
        missing_dig = 20;
    }
    if (diff == "Hard") {
        missing_dig = 40;
    }

    resetBoard();

    // Now fill the board again with new values
    fillDiagonal();
    fillRemaining(0, num_of_rows);
    remove_missing_digs();
}

/**
 * @brief Solves the Sudoku puzzle.
 * 
 * @return true if the puzzle is solved, false otherwise.
 */
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

/**
 * @brief Finds an unassigned location on the board.
 * 
 * @param row Reference to store the row index of the unassigned location.
 * @param col Reference to store the column index of the unassigned location.
 * @return true if an unassigned location is found, false otherwise.
 */
bool Board::findUnassignedLocation(int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (board[row][col] == 0)
                return true;
    return false;
}

bool Board::isGameComplete() {
    std::cout << "Checking if game is complete..." << std::endl;
    GameIsCompleted=true;

    for (int i = 0; i < N; i++) {
        if (!isRowComplete(i) || !isColumnComplete(i)) {
            GameIsCompleted = false;
        }
    }
    for (int row = 0; row < N; row += num_of_rows) {
        for (int col = 0; col < N; col += num_of_rows) {
            if (!isSubgridComplete(row, col)) {
                GameIsCompleted = false;
            }
        }
    }

    return GameIsCompleted;
;
}

bool Board::isRowComplete(int row) {
    std::vector<bool> seen(N + 1, false);
    for (int col = 0; col < N; col++) {
        int num = board[row][col];
        if (num == 0 || seen[num]) {
            return false;
        }
        seen[num] = true;
    }
    return true;
}

bool Board::isColumnComplete(int col) {
    std::vector<bool> seen(N + 1, false);
    for (int row = 0; row < N; row++) {
        int num = board[row][col];
        if (num == 0 || seen[num]) {
            return false;
        }
        seen[num] = true;
    }
    return true;
}

bool Board::isSubgridComplete(int startRow, int startCol) {
    std::vector<bool> seen(N + 1, false);
    for (int row = 0; row < num_of_rows; row++) {
        for (int col = 0; col < num_of_rows; col++) {
            int num = board[startRow + row][startCol + col];
            if (num == 0 || seen[num]) {
                return false;
            }
            seen[num] = true;
        }
    }
    return true;
}

/**
 * @brief Retrieves the Sudoku board.
 * 
 * @return A pointer to the 2D array representing the Sudoku board.
 */
int** Board::getBoard() {
    return board;
}




