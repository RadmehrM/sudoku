#ifndef DETECTOR_H
#define DETECTOR_H

#include <vector>

class Detector {
private:
    bool isCorrect;

public:
    // Constructor
    Detector();

    // Check the entire board for errors
    bool checkErrors();

    // Check all rows for errors
    bool checkRows();

    // Check all columns for errors
    bool checkColumns();

    // Check all 3x3 boxes for errors
    bool checkBoxes();

    // Mark errors on the board and return a board with marked errors
    std::vector<std::vector<bool>> markErrors(const std::vector<std::vector<int>>& board);

    // Evaluate a move (not specified in UML what it evaluates, using int as placeholder)
    int evaluateMove();
};

#endif // DETECTOR_H
