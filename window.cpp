#include "window.h"
#include <QLineEdit>
#include <QValidator>
#include <QApplication>
#include <iostream>

using namespace std;

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    int N = 9;
    int K = 20; // Number of blank boxes
    Board* sudoku = new Board(N, K); // Assuming Board class has a constructor

    // Create a central widget to hold the grid layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background-color: white;");
    centralWidget->setStyleSheet("border: 2px solid black;");
    centralWidget->setContentsMargins(0, 0, 0, 0);

    // Create a grid layout for the central widget
    gridlayout = new QGridLayout(centralWidget);
    gridlayout->setMargin(0);
    gridlayout->setSpacing(0); // Adjust spacing as needed

    // Fill the board and print sudoku before creating LineEdits
    sudoku->fillBoard();
    sudoku->printSudoku();

    // Add QLineEdit widgets to the grid layout
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QLineEdit *lineEdit = new QLineEdit();
            lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            lineEdit->setMinimumSize(75, 75); // Adjust size as needed
            lineEdit->setFont(QFont("Arial", 20)); // Adjust font size as needed
            lineEdit->setAlignment(Qt::AlignCenter);
            lineEdit->setMaxLength(1); // Only allow one character
            lineEdit->setValidator(new QIntValidator(1, 9, this)); // Only allow numbers 1-9

            // Customize the QLineEdit style. Change the thickness of the border as you like.
            QString lineEditStyle = "border: 1px solid black;";

            // For every third row and column, increase the border size to visually separate 3x3 grids
            if ((row + 1) % 3 == 0 && row != 8) {
                lineEditStyle.append("border-bottom: 3px solid black;");
            }
            if ((col + 1) % 3 == 0 && col != 8) {
                lineEditStyle.append("border-right: 3px solid black;");
            }

            lineEdit->setStyleSheet(lineEditStyle);
            gridlayout->addWidget(lineEdit, row, col);

            // Assuming board is filled with initial values from the Board constructor
            // Set the value of the LineEdit to the corresponding value in the board
            int temp = sudoku->board[row][col];
            setLineEditValue(row, col, QString::number(temp));
        }
    }

    // Set the grid layout as the layout of the central widget
    centralWidget->setLayout(gridlayout);
}

void Window::setLineEditValue(int row, int col, const QString &value) {
    // Get the item (widget) at the specified row and column in the grid layout
    QLayoutItem *layoutItem = gridlayout->itemAtPosition(row, col);
    if (layoutItem) {
        QWidget *widget = layoutItem->widget();
        if (widget) {
            // Check if the widget is a QLineEdit
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget);
            if (lineEdit) {
                // Set the new value for the QLineEdit
                lineEdit->setText(value);
                return; // Exit function early if everything is successful
            }
        }
    }
    // Print an error message or handle the case where the widget is not found
    cerr << "Failed to set value at position (" << row << ", " << col << ")" << endl;
}