#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)  {
        QVBoxLayout *layout = new QVBoxLayout(this);


        QSpacerItem *verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacerTop);

        QLabel *titleLabel = new QLabel("Sudoku", this);
        titleLabel->setAlignment(Qt::AlignCenter); // Center the title
        titleLabel->setFont(QFont("Arial", 25, QFont::Bold)); // Set the font to make it look more like a title
        // Assuming you have a layout for your content
        titleLabel->setStyleSheet("QLabel { padding: 20px; color:black }");
        layout->addWidget(titleLabel); 


        button1 = new QPushButton("Start Game", this);
        button1->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button1, 0, Qt::AlignHCenter); // Align the button horizontally in the center
        connect(button1, &QPushButton::clicked, this, &Menu::startGame);


        button2 = new QPushButton("Difficulty: " + QString::fromStdString(difficulties[currentDifficultyIndex]), this);
        button2->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button2, 0, Qt::AlignHCenter); // Align the button horizontally in the center
        connect(button2, &QPushButton::clicked, this, &Menu::changeDifficulty);



        button3 = new QPushButton("Exit", this);
        button3->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button3, 0, Qt::AlignHCenter); // Align the button horizontally in the center
        connect(button3, &QPushButton::clicked, this, &Menu::exit);


        // Add another spacer at the bottom
        QSpacerItem *verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacerBottom);

        setLayout(layout);

};

void Menu::startGame() {
        this->hide();
        emit beginGame();
}

void Menu::exit() {
        QApplication::quit();
}

void Menu::changeDifficulty() {
    currentDifficultyIndex = (currentDifficultyIndex + 1) % difficulties.size();
    button2->setText("Difficulty: " + QString::fromStdString(difficulties[currentDifficultyIndex]));
    emit difficultyChanged(currentDifficultyIndex);
}


int Menu::getDifficulty() {
        return currentDifficultyIndex;
}
