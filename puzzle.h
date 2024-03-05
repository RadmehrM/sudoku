#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <vector>

class Puzzle {
private:
    std::vector<std::vector<int>> puzzleBoard;
    std::string difficulty;
    std::vector<int> timer;
    std::string gameType;

public:
    // Set the difficulty of the puzzle
    std::string setDifficulty();

    // Set the game type
    void setGameType(const std::string& type);

    // Create a new puzzle
    void createPuzzle();

    // Create a standard Sudoku puzzle
    std::vector<std::vector<int>> createSudoku(const std::string& difficultyLevel);

    // Create a Killer Sudoku puzzle
    std::vector<std::vector<int>> createKillerSudoku(const std::string& difficultyLevel);
};

#endif // PUZZLE_H
