#include "window.h"
#include <QLineEdit>
#include <QValidator>
#include <QApplication>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    // Create a central widget to hold the grid layout
    QWidget *centralWidget = new QWidget(this);
    
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background-color: white;");
    centralWidget->setStyleSheet("border: 2px solid black;");
    centralWidget->setContentsMargins(0, 0, 0, 0);


    // Create a grid layout for the central widget
    gridlayout = new QGridLayout(centralWidget);
    gridlayout->setSpacing(0); // Adjust spacing as needed

    // Add buttons to the grid layout
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
        }
    }


    // Set the grid layout as the layout of the central widget
    centralWidget->setLayout(gridlayout);
}
