#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    int rows;
    int columns;

public:
    // Default constructor
    Board();

    // Member function to reset the board
    void resetBoard();

    // Member function to fill the board
    void fillBoard();

    // Destructor
    ~Board();
};

#endif // BOARD_H
