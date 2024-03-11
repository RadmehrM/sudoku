#include "window.h"
#include <QPushButton>

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
            QPushButton *button = new QPushButton(QString::number(row * 9 + col + 1));
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            button->setMinimumSize(100,100);
            button->setStyleSheet("border: 1px solid black onset;");
            gridlayout->addWidget(button, row, col);
        }
    }

    // Set the grid layout as the layout of the central widget
    centralWidget->setLayout(gridlayout);
    
}
