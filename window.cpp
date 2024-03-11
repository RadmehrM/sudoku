#include "window.h"
#include <QPushButton>
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
    gridlayout->setMargin(0);
    gridlayout->setSpacing(0); // Adjust spacing as needed

    // Add buttons to the grid layout
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QPushButton *button = new QPushButton("");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(75, 75); // Adjust size as needed

            // Customize the button style. Change the thickness of the border as you like.
            QString buttonStyle = "border: 1px solid black;";

            // For every third row and column, increase the border size to visually separate 3x3 grids
            if ((row + 1) % 3 == 0 && row != 8) {
                buttonStyle.append("border-bottom: 3px solid black;");
            }
            if ((col + 1) % 3 == 0 && col != 8) {
                buttonStyle.append("border-right: 3px solid black;");
            }

            button->setStyleSheet(buttonStyle);
            gridlayout->addWidget(button, row, col);
        }
    }

    // Set the grid layout as the layout of the central widget
    centralWidget->setLayout(gridlayout);
    
}
