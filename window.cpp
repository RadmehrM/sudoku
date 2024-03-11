#include "window.h"
#include <QLineEdit>
#include <QValidator>
#include <QApplication>
#include <QTimer>
#include <QVector>
#include <iostream>

using namespace std;

Window::Window(QWidget *parent) : QMainWindow(parent) {
    // Create a central widget to hold the grid and buttons layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget); // Main layout is horizontal

    // Create the grid layout for the Sudoku board
    gridlayout = new QGridLayout();
    gridlayout->setSpacing(0); // Adjust spacing as needed

    // Create the board instance
    sudokuBoard = new Board(9, 20); // Board class must have a constructor

    // Fill the board and print sudoku before creating LineEdits
    sudokuBoard->fillBoard();
    sudokuBoard->printSudoku();

    // Add QLineEdit widgets to the grid layout
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QLineEdit *lineEdit = new QLineEdit();
            lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            lineEdit->setMinimumSize(75, 75);
            lineEdit->setFont(QFont("Arial", 20));
            lineEdit->setAlignment(Qt::AlignCenter);
            lineEdit->setMaxLength(1);
            lineEdit->setValidator(new QIntValidator(1, 9, this));

            // for validating input
            connect(lineEdit, &QLineEdit::textEdited, this, &Window::validateInput);

            // Customize the QLineEdit style
            QString lineEditStyle = "border: 1px solid black;";
            if ((row + 1) % 3 == 0 && row != 8) lineEditStyle.append("border-bottom: 3px solid black;");
            if ((col + 1) % 3 == 0 && col != 8) lineEditStyle.append("border-right: 3px solid black;");
            lineEdit->setStyleSheet(lineEditStyle + " color: black;");

            gridlayout->addWidget(lineEdit, row, col);
            
            // Set the value of the LineEdit to the corresponding value in the board
            int value = sudokuBoard->getBoard()[row][col];
            lineEdit->setText(value != 0 ? QString::number(value) : "");
            lineEdit->setReadOnly(value != 0); // Pre-filled cells are read-only
        }
    }

    // Add the grid layout to the main layout
    mainLayout->addLayout(gridlayout);

    // Create buttons and add them to a vertical layout
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QPushButton *fillGridButton = new QPushButton("Fill Grid");
    QPushButton *newGameButton = new QPushButton("New Game");
    
    // Connect buttons to their respective slots
    connect(fillGridButton, &QPushButton::clicked, this, [this] { /* TODO: Implement fillGrid logic */ });
    connect(newGameButton, &QPushButton::clicked, this, [this] { /* TODO: Implement newGame logic */ });

    buttonLayout->addWidget(fillGridButton);
    buttonLayout->addWidget(newGameButton);
    buttonLayout->addStretch(); // Push buttons to the top

    fillGridButton->setStyleSheet("color: black;");
    newGameButton->setStyleSheet("color: black;");

    // Add the button layout to the main layout
    mainLayout->addLayout(buttonLayout);

    // Set the main layout as the layout for the central widget
    centralWidget->setLayout(mainLayout);

    // Set style for the central widget
    centralWidget->setStyleSheet("background-color: white; border: 2px solid black;");
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
                if (value == "0") {
                    lineEdit->setText("");
                } else {
                // Set the new value for the QLineEdit
                lineEdit->setText(value);
                }
                return; // Exit function early if everything is successful
            }
        }
    }
    // Print an error message or handle the case where the widget is not found
    cerr << "Failed to set value at position (" << row << ", " << col << ")" << endl;
}

void Window::validateInput() {
    QLineEdit *senderLineEdit = qobject_cast<QLineEdit*>(sender());
    if (!senderLineEdit) {
        return; // If for some reason the sender is not a QLineEdit, exit
    }

    // Determine the position of the sender QLineEdit in the grid
    const int senderIndex = gridlayout->indexOf(senderLineEdit);
    const int senderRow = senderIndex / 9;
    const int senderColumn = senderIndex % 9;

    // Convert the input to a number
    bool ok;
    int inputValue = senderLineEdit->text().toInt(&ok);
    if (!ok || inputValue == 0) {
        cerr << "Invalid input." << endl;
        return; // Invalid input, exit the function
    }

    // Initialize variables to store conflicting cells
    QVector<QLineEdit*> conflictCells;

    // Check if the input is already used in the 3x3 subsection, row, or column
    for (int i = 0; i < 9; ++i) {
        checkConflict(senderRow, i, inputValue, senderLineEdit, conflictCells);
        checkConflict(i, senderColumn, inputValue, senderLineEdit, conflictCells);
    }

    // Check the 3x3 subsection for conflicts
    int boxStartRow = senderRow - senderRow % 3;
    int boxStartCol = senderColumn - senderColumn % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            checkConflict(boxStartRow + i, boxStartCol + j, inputValue, senderLineEdit, conflictCells);
        }
    }

    if (!conflictCells.isEmpty()) {
        // Highlight the conflicting cells in red
        for (QLineEdit* cell : qAsConst(conflictCells)) {
            cell->setStyleSheet("background-color: red; color: black;");
        }
        
        // Highlight the senderLineEdit in red to indicate the wrong input
        senderLineEdit->setStyleSheet("background-color: red; color: black;");

        // Set a timer to remove the highlight from the conflicting cells after 1 second
        QTimer::singleShot(1000, [conflictCells, senderLineEdit]{
            for (QLineEdit* cell : conflictCells) {
                cell->setStyleSheet("border: 1px solid black; color: black;");
            }
            // Also, clear the input from the sender QLineEdit and reset its style
            senderLineEdit->clear();
            senderLineEdit->setStyleSheet("border: 1px solid black; color: black;");
        });

        cerr << "The number " << inputValue << " is already in the row, column, or subsection." << endl;
    }
}


void Window::checkConflict(int row, int col, int value, QLineEdit* sender, QVector<QLineEdit*>& conflictCells) {
    QLineEdit *cell = qobject_cast<QLineEdit*>(gridlayout->itemAtPosition(row, col)->widget());
    if (cell && cell != sender && cell->text().toInt() == value) {
        conflictCells.push_back(cell);
    }
}