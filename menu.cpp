/**
 * @brief Menu Class
 * 
 * This class is used to create the main menu splash screen
 * 
 * @author Daniel Gomes
 * @author Zain Raza
 * @author Radmehr Mehdipour
 * @author Sreethan Vuppala
 * @author Aidan Freeman
 */

#include "menu.h"

/**
 * @brief Constructs a Menu widget.
 * 
 * This constructor sets up the menu interface for the Sudoku game.
 * It adds a title, start game button, difficulty selection button, and an exit button to the layout.
 * The menu provides options to start the game, change difficulty, and exit the application.
 * 
 * @param parent The parent widget which owns this Menu instance.
 */
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

/**
 * @brief Starts the game.
 * 
 * This slot is triggered when the 'Start Game' button is clicked.
 * It hides the menu and emits the beginGame signal to notify the main window
 * to start the game.
 */
void Menu::startGame() {
        this->hide();
        emit beginGame();
}

/**
 * @brief Exits the application.
 * 
 * This slot is triggered when the 'Exit' button is clicked.
 * It terminates the application.
 */
void Menu::exit() {
        QApplication::quit();
}

/**
 * @brief Changes the difficulty of the game.
 * 
 * This slot is triggered when the difficulty selection button is clicked.
 * It cycles through the available difficulties and updates the button text.
 * It emits the difficultyChanged signal to notify the main window about
 * the change in difficulty.
 */
void Menu::changeDifficulty() {
    currentDifficultyIndex = (currentDifficultyIndex + 1) % difficulties.size();
    button2->setText("Difficulty: " + QString::fromStdString(difficulties[currentDifficultyIndex]));
    emit difficultyChanged(currentDifficultyIndex);
}

/**
 * @brief Retrieves the current difficulty setting.
 * 
 * This function provides access to the current difficulty index.
 * 
 * @returns The current difficulty index as an integer.
 */
int Menu::getDifficulty() {
        return currentDifficultyIndex;
}
