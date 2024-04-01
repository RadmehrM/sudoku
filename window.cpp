
#include "window.h"
#include <QLineEdit>
#include <QValidator>
#include <QApplication>
#include <QVector>
#include <QTimer>
#include <QMessageBox>
#include <iostream>
#include "hints.h"
#include <QPalette>
#include <QStringList>
#include <QSet>
#include <QString>
#include <unordered_set>

// Winning Animation Imports //
#include <QWidget>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QFont>


using namespace std;

/**
 * @brief Constructs a Window object.
 * 
 * This constructor initializes the main window of the Sudoku application.
 * It sets up the layout, creates the Sudoku board, fills the board, and connects signals and slots.
 * 
 * @param parent The parent widget.
 */
Window::Window(QWidget *parent) : QMainWindow(parent), score(0), scores(), gameDurations() {
    // Create a central widget to hold the grid and buttons layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget); // Main layout is horizontal
    QVBoxLayout *optionsLayout = new QVBoxLayout();
    QHBoxLayout *boxesOnlyLayout = new QHBoxLayout();

    // Create the grid layout for the Sudoku board
    gridlayout = new QGridLayout();
    gridlayout->setSpacing(0); // Adjust spacing as needed

    // Create the board instance
    sudokuBoard = new Board(9, 10); // Board class must have a constructor

    // Fill the board and print sudoku before creating LineEdits
    sudokuBoard->fillBoard();
    sudokuBoard->printSudoku();

    // Add QLineEdit widgets to the grid layout
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            lineEdit = new QLineEdit();
            lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            lineEdit->setMinimumSize(75, 75);
            lineEdit->setFont(QFont("Arial", 20));
            lineEdit->setAlignment(Qt::AlignCenter);
            lineEdit->setMaxLength(1);
            lineEdit->setValidator(new QIntValidator(1, 9, this));

            // Customize the QLineEdit style
            QString lineEditStyle = "border: 1px solid black;";
            if ((row + 1) % 3 == 0 && row != 8) lineEditStyle.append("border-bottom: 3px solid black;");
            if ((col + 1) % 3 == 0 && col != 8) lineEditStyle.append("border-right: 3px solid black;");
        
            gridlayout->addWidget(lineEdit, row, col);
            
            // Set the value of the LineEdit to the corresponding value in the board
            int value = sudokuBoard->getBoard()[row][col];
            lineEdit->setText(value != 0 ? QString::number(value) : "");
            lineEdit->setReadOnly(sudokuBoard->isLocked(row, col)); // Pre-filled cells are read-only
            if(sudokuBoard->isLocked(row, col)) {
                lineEdit->setStyleSheet(lineEditStyle + " color: black;");
            } else {
                lineEdit->setStyleSheet(lineEditStyle + " color: blue;");
            }
            
            connect(lineEdit, &QLineEdit::textEdited, this, [this] {
                validateInput();
                // sudokuBoard->printSudoku();
            });


        }
    }

    

    // Add the grid layout to the main layout
    mainLayout->addLayout(gridlayout);


    // Timer label for the UI
    timerLabel = new QLabel("Time: 0 sec", this);
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("QLabel { color : black; background-color:white; }");
    timerLabel->setFixedSize(145, 45); // Adjust size as needed

    updateTimer = new QTimer(this); // Create the update timer
    connect(updateTimer, &QTimer::timeout, this, &Window::updateTimerDisplay);
    updateTimer->start(1000); // Update the timer display every second

    // Set up game timer
    gameTimer = new QElapsedTimer();
    gameTimer->start();

    //Set Up Hints:
    hintsWindow = new HintsWindow(this); // Initialize the hints window
    hintsWindow->setStyleSheet("background-color: transparent; border: solid 1px black");


    // Create buttons and add them to a vertical layout
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QPushButton *fillGridButton = new QPushButton("Fill Grid");
    QPushButton *newGameButton = new QPushButton("New Game");
    QPushButton *viewLogbookButton = new QPushButton("View Logbook");
    QPushButton *hint = new QPushButton("Hint");
    QPushButton *exitButton = new QPushButton("Exit Game");
    pencilModeButton.setText("Pencil Mode Off");
    difficultyButton.setText("Difficulty: Easy");
    
    // hints->resize(200, hints->height());
    fillGridButton->setFixedSize(145,45);
    difficultyButton.setFixedSize(145,45); 
    newGameButton->setFixedSize(145,45);
    viewLogbookButton->setFixedSize(145,45);
    hint->setFixedSize(145,45);
    pencilModeButton.setFixedSize(145,45) ;
    exitButton->setFixedSize(145,45); 

    pencilModeOn = false;

    scoreLabel = new QLabel("Score: 0", this); // Initialize the QLabel with 'this' as the parent
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel { background-color : transparent; color : black; }");
    scoreLabel->setFixedSize(145,45);
    
    // Connect buttons to their respective slots
    connect(fillGridButton, &QPushButton::clicked, this, [this] { 
        sudokuBoard->solveSudoku(); 
        updateBoard();
        showWinningAnimation();
        });

    connect(&difficultyButton, &QPushButton::clicked, this, &Window::changeDifficulty);

    connect(newGameButton, &QPushButton::clicked, this, [this] {
        qint64 currentGameDuration = gameTimer->elapsed();
        gameDurations.push_back(currentGameDuration); // Save the duration of the current game
        gameTimer->restart(); // Restart the timer for the new game
        gameDifficulties.push_back(currentDifficultyIndex);
        scores.push_back(score); // Save the current score
        score = 0; // Reset the score for the new game
        scoreLabel->setText("Score: " + QString::number(score)); // Update the score label

        sudokuBoard->regenerateBoard(); // Create a new game
        updateBoard();
    });
    connect(viewLogbookButton, &QPushButton::clicked, this, [this] { 
        showLogbook();
        updateBoard();
    });

    connect(hint, &QPushButton::clicked, hintsWindow, &HintsWindow::showHint);
    connect(&pencilModeButton, &QPushButton::clicked, this, &Window::togglePencilMode);
    connect(exitButton, &QPushButton::clicked, this, [this] {
        QApplication::quit();
    });
    

    buttonLayout->addWidget(timerLabel);
    buttonLayout->addWidget(&difficultyButton);
    buttonLayout->addWidget(fillGridButton);
    buttonLayout->addWidget(newGameButton);
    buttonLayout->addWidget(viewLogbookButton);
    buttonLayout->addWidget(&pencilModeButton);
    buttonLayout->addWidget(hint);
    buttonLayout->addWidget(exitButton);
    //buttonLayout->addWidget(hintsWindow);
    buttonLayout->addStretch(); // Push buttons to the top

    fillGridButton->setStyleSheet("QPushButton { color: white; background-color: green; border: 2px solid black; font-weight: bold;}");
    difficultyButton.setStyleSheet("QPushButton { color: white; background-color: darkMagenta; border: 2px solid black; font-weight: bold;}");
    newGameButton->setStyleSheet("QPushButton { color: white; background-color: blue; border: 2px solid black; font-weight: bold;}");
    viewLogbookButton->setStyleSheet("QPushButton { color: white; background-color: red; border: 2px solid black; font-weight: bold;}");
    hint->setStyleSheet("QPushButton { color: white; background-color: orange; border: 2px solid black; font-weight: bold;}");
    pencilModeButton.setStyleSheet("QPushButton { color: white; background-color: lightCoral; border: 2px solid black; font-weight: bold;}");
    exitButton->setStyleSheet("QPushButton { color: white; background-color: darkRed; border: 2px solid black; font-weight: bold;}");

    // Add the button layout to the main layout
    boxesOnlyLayout->addLayout(buttonLayout);
    boxesOnlyLayout->addWidget(scoreLabel, 0, Qt::AlignRight | Qt::AlignTop);
    optionsLayout->addLayout(boxesOnlyLayout);
    optionsLayout->addWidget(hintsWindow);
    mainLayout->addLayout(optionsLayout);
    
    // Set the main layout as the layout for the central widget
    centralWidget->setLayout(mainLayout);

    // Set style for the central widget
    centralWidget->setStyleSheet("border: 2px solid black;");

    stackedWidget = new QStackedWidget(this);
    Menu *menu = new Menu(stackedWidget);
    menu->resize(850,800);
    menu->setStyleSheet("color: black;");
    menu->show();
    connect(menu, &Menu::difficultyChanged, this, &Window::onDifficultyChanged);
    connect(menu, &Menu::beginGame, this, &Window::beginGame);

    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(centralWidget);
    setCentralWidget(stackedWidget);

    // To show the menu:
    stackedWidget->setCurrentWidget(menu);

}

/**
 * @brief Sets the value of a QLineEdit widget at the specified position.
 * 
 * This function updates the text of the QLineEdit widget at the specified row and column
 * in the grid layout with the provided value.
 * 
 * @param row The row index of the QLineEdit widget.
 * @param col The column index of the QLineEdit widget.
 * @param value The value to set in the QLineEdit.
 */
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

void Window::incrementScore(int value) {
  score += value; // Increase the score
  scoreLabel->setText("Score: " + QString::number(score)); // Update the score label
}

void Window::decrementScore(int value) {
  score -= value; // Increase the score
  scoreLabel->setText("Score: " + QString::number(score)); // Update the score label
}

/**
 * @brief Validates the input in a QLineEdit widget.
 * 
 * This function is called when the text in a QLineEdit widget is edited.
 * It validates the input according to Sudoku rules and highlights conflicting cells.
 */
void Window::validateInput()
{
    QLineEdit *senderLineEdit = qobject_cast<QLineEdit *>(sender());
    if (!senderLineEdit || senderLineEdit->text().isEmpty())
    {
        return; // Exit if the sender is not a QLineEdit or is empty
    }

    int senderIndex = gridlayout->indexOf(senderLineEdit);
    int senderRow = senderIndex / 9;
    int senderColumn = senderIndex % 9;

    if (pencilModeOn)
    {
        int pencilMark = senderLineEdit->text().toInt();
        // cout << "Pencil Mark: " << pencilMark << endl;
        if (pencilMark < 1 || pencilMark > 999999999)
        {
            cout << "Backspace, delete etc clicked " << pencilMark << endl; 
            // qDebug() << "Invalid pencil mark.";
            senderLineEdit->clear(); // Clear invalid input
            return;
        }

        QString currentText = senderLineEdit->text();
 
        if(currentText.length() == 1) {
            senderLineEdit->setMaxLength(2);
            senderLineEdit->setFont(QFont("Arial", 20));
            senderLineEdit->setText(currentText);
            return; 
        }

        QString updatedText = QString::fromStdString(cleanPencilInput(currentText.toStdString()));

        if(updatedText.length() == 1) {
            senderLineEdit->setMaxLength(2);
            senderLineEdit->setFont(QFont("Arial", 20));
            senderLineEdit->setText(updatedText);

        } else {

            senderLineEdit->setMaxLength(updatedText.length() + 1);
            senderLineEdit->setFont(QFont("Arial", 10));
            senderLineEdit->setText(updatedText);
        } 

        return; // Exit to skip normal validation logic
    }

    // Determine the position of the sender QLineEdit in the grid
    senderIndex = gridlayout->indexOf(senderLineEdit);
    senderRow = senderIndex / 9;
    senderColumn = senderIndex % 9;

    // Convert the input to a number
    bool ok;
    int inputValue = senderLineEdit->text().toInt(&ok);
    if (!ok || inputValue == 0) {
        cerr << "Invalid input." << endl;
        senderLineEdit->clear();
        return; // Invalid input, exit the function
    }

    senderLineEdit->setFont(QFont("Arial", 20));
    // Initialize variables to store conflicting cells
    QVector<QLineEdit*> conflictCells;

    // Check the entire row and column for conflicts
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
            cell->setStyleSheet("background-color: red;");
        }
        
        // Highlight the senderLineEdit in red to indicate the wrong input
        senderLineEdit->setStyleSheet("background-color: red; color: blue;");

        // Set a timer to remove the highlight from the conflicting cells after 1 second
        QTimer::singleShot(1000, [conflictCells, senderLineEdit]{
            for (QLineEdit* cell : conflictCells) {
                cell->setStyleSheet("border: 1px solid black; color: black;");
            }
            // Also, clear the input from the sender QLineEdit and reset its style
            senderLineEdit->clear();
            senderLineEdit->setStyleSheet("border: 1px solid black; color: blue;");
        });

        cerr << "The number " << inputValue << " is already in the row, column, or subsection." << endl;
    } else {
        // The number is not conflicting and is valid, lock the cell.
        //senderLineEdit->setReadOnly(true);
        if(!sudokuBoard->isScored(senderRow, senderColumn)) {
            incrementScore(100);
            sudokuBoard->setScored(senderRow, senderColumn);
        }
    }

    QTimer::singleShot(1000, this, [this]() {
        updateCellBorder(); // This function is called after a delay of 1000 milliseconds (1 second)
    });

    // After each valid move, check if the game is complete
    if (isGridFull()) {
        std::cout << "Game complete, showing animation." << std::endl;
        // Trigger the winning animation
        showWinningAnimation();
    }
    else {
        std::cout << "Game not complete, continue playing." << std::endl;
    }
}

/**
 * @brief Checks for conflicts in the Sudoku board.
 * 
 * This function checks for conflicts caused by adding a specific value to a cell.
 * It checks the row, column, and 3x3 subsection of the cell for conflicts.
 * 
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @param value The value to check for conflicts.
 * @param sender The sender QLineEdit widget.
 * @param conflictCells Vector to store conflicting cells.
 */
void Window::checkConflict(int row, int col, int value, QLineEdit* sender, QVector<QLineEdit*>& conflictCells) {
    QLineEdit *cell = qobject_cast<QLineEdit*>(gridlayout->itemAtPosition(row, col)->widget());
    if (cell && cell != sender && cell->text().toInt() == value) {
        conflictCells.push_back(cell);
    }
}

/**
 * @brief Updates the Sudoku board displayed on the window.
 * 
 * This function updates the Sudoku board displayed on the window
 * based on the values stored in the sudokuBoard object.
 */
void Window::updateBoard() {
    // Iterate over the board
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // Get the QLineEdit widget at position (row, col)
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(gridlayout->itemAtPosition(row, col)->widget());
            if (lineEdit) {
                // Get the value from the sudokuBoard
                int value = sudokuBoard->getBoard()[row][col];
                // Update the text of the QLineEdit
                lineEdit->setText(value != 0 ? QString::number(value) : "");
                // Set read-only property for pre-filled cells
                lineEdit->setReadOnly(sudokuBoard->isLocked(row, col));
                QString lineEditStyle = "border: 1px solid black;";
                if ((row + 1) % 3 == 0 && row != 8) lineEditStyle.append("border-bottom: 3px solid black;");
                if ((col + 1) % 3 == 0 && col != 8) lineEditStyle.append("border-right: 3px solid black;");
                lineEdit->setFont(QFont("Arial", 20));

                if(sudokuBoard->isLocked(row, col)) {
                    lineEdit->setStyleSheet(lineEditStyle + " color: black;");
                } else {
                    lineEdit->setStyleSheet(lineEditStyle + " color: blue;");
                }
            }
        }
    }
}

void Window::showLogbook() {
    QString logbookContent;
    for(int i = 0; i < scores.size(); ++i) {
        qint64 durationSeconds = gameDurations[i] / 1000; // Convert milliseconds to seconds
        logbookContent += "Game " + QString::number(i + 1) + ": Score: " + QString::number(scores[i]) +
                          ", Time: " + QString::number(durationSeconds) + " seconds" +
                          ", Difficulty: " + QString::fromStdString(difficulties[gameDifficulties[i]]) + "\n";
    }

    if(logbookContent.isEmpty()) {
        logbookContent = "No games completed yet.";
    }

    QMessageBox::information(this, "Logbook", logbookContent);
}

void Window::changeDifficulty() {
    currentDifficultyIndex = (currentDifficultyIndex + 1) % difficulties.size();
    gameTimer->restart();
    score = 0;
    scoreLabel->setText("Score: " + QString::number(score));
    difficultyButton.setText("Difficulty: " + QString::fromStdString(difficulties[currentDifficultyIndex]));
    Window::onDifficultyChanged(currentDifficultyIndex);
}

void Window::onDifficultyChanged(int newDifficulty) {
    // Delete the existing board if necessary
    if (sudokuBoard) {
        delete sudokuBoard;
        sudokuBoard = nullptr;
    }

    // Reinitialize the board based on the new difficulty
    if (newDifficulty == 0) sudokuBoard = new Board(9, 10);
    else if (newDifficulty == 1) sudokuBoard = new Board(9, 20);
    else if (newDifficulty == 2) sudokuBoard = new Board(9, 40);

    // Assume regenerateBoard() fills the board and resets it for the new difficulty
    sudokuBoard->regenerateBoard();
    
    // Update UI elements to reflect the new board
    updateBoard();
}

void Window::beginGame() {
    gameTimer->restart();
    stackedWidget->setCurrentWidget(centralWidget);

}

void Window::togglePencilMode()
{
    pencilModeOn = !pencilModeOn;
    updatePencilModeUI();
}

void Window::updatePencilModeUI()
{
    if (pencilModeOn)
    {
        pencilModeButton.setStyleSheet("QPushButton { color: white; background-color: lightGreen; border: 2px solid black; font-weight: bold;}");
        pencilModeButton.setText("Pencil Mode On");
        setLineEditSize(9);
    }
    else
    {
        pencilModeButton.setStyleSheet("QPushButton { color: white; background-color: lightCoral; border: 2px solid black; font-weight: bold;}");
        pencilModeButton.setText("Pencil Mode Off");
        setLineEditSize(1); 
    }
}

void Window::updateTimerDisplay() {
    qint64 timeElapsed = gameTimer->elapsed() / 1000; // Get the elapsed time in seconds
    timerLabel->setText("Time: " + QString::number(timeElapsed) + "sec");
}


void Window::showWinningAnimation() {
    // Create an overlay widget that will cover the entire window
    QWidget *overlayWidget = new QWidget(this);
    overlayWidget->setStyleSheet("background-color: rgba(255, 255, 255, 170);"); // semi-transparent white overlay
    overlayWidget->setGeometry(this->rect()); // Cover the entire window

    // Create a label for the congratulations message
    QLabel *congratsLabel = new QLabel("Congratulations! You've won!", overlayWidget);
    congratsLabel->setAlignment(Qt::AlignCenter);
    congratsLabel->setFont(QFont("Helvetica", 24, QFont::Bold));
    congratsLabel->setStyleSheet("color: #000000;");
    congratsLabel->setGeometry(overlayWidget->rect()); // Cover the overlay widget

    // Create an opacity effect for the fade-in
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(overlayWidget);
    overlayWidget->setGraphicsEffect(effect);
    overlayWidget->show();

    // Create an animation for the fade-in effect
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000); // 1 second duration
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    //QTimer::singleShot(5000, overlayWidget, &QWidget::deleteLater);

    // Create buttons for 'Exit' and 'Play Again'
    QPushButton *exitButton = new QPushButton("Exit", overlayWidget);
    QPushButton *playAgainButton = new QPushButton("Play Again", overlayWidget);

    // Set properties for 'Exit' button
    exitButton->setFont(QFont("Helvetica", 16, QFont::Bold));
    exitButton->setStyleSheet("QPushButton { color: white; background-color: red; }");
    exitButton->setGeometry(QRect(this->width()/2 - 100, this->height()/2 + 100, 200, 50));  // Adjust as necessary

    // Set properties for 'Play Again' button
    playAgainButton->setFont(QFont("Helvetica", 16, QFont::Bold));
    playAgainButton->setStyleSheet("QPushButton { color: white; background-color: green; }");
    playAgainButton->setGeometry(QRect(this->width()/2 - 100, this->height()/2 + 160, 200, 50));  // Adjust as necessary

    // Connect buttons to their slots
    connect(exitButton, &QPushButton::clicked, []() {
        QApplication::exit();
    });
    connect(playAgainButton, &QPushButton::clicked, [this, overlayWidget]() {
        overlayWidget->deleteLater();
        qint64 currentGameDuration = gameTimer->elapsed();
        gameDurations.push_back(currentGameDuration); // Save the duration of the current game
        gameTimer->restart(); // Restart the timer for the new game
        gameDifficulties.push_back(currentDifficultyIndex);
        scores.push_back(score); // Save the current score
        score = 0; // Reset the score for the new game
        scoreLabel->setText("Score: " + QString::number(score)); // Update the score label

        sudokuBoard->regenerateBoard(); // Create a new game
        updateBoard();


    });

    // Ensure buttons are on top of the overlay and visible
    exitButton->raise();
    playAgainButton->raise();
    exitButton->show();
    playAgainButton->show();

}

void Window::updateCellBorder() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // Fetch the widget from the grid layout
            QLayoutItem* item = gridlayout->itemAtPosition(row, col);
            if (item != nullptr) {
                QWidget* widget = item->widget();
                if (widget != nullptr) {
                    // Cast the widget to QLineEdit
                    QLineEdit* lineEditCell = qobject_cast<QLineEdit*>(widget);
                    if (lineEditCell != nullptr) {
                        // Construct the style string
                        QString lineEditStyle = "border: 1px solid black;";
                        if ((row + 1) % 3 == 0 && row != 8) lineEditStyle.append("border-bottom: 3px solid black;");
                        if ((col + 1) % 3 == 0 && col != 8) lineEditStyle.append("border-right: 3px solid black;");
                        // Apply the style
                        if(sudokuBoard->isLocked(row,col)) {
                            lineEditCell->setStyleSheet(lineEditStyle + " color: black;");
                        } else {
                            lineEditCell->setStyleSheet(lineEditStyle + " color: blue;");
                        }

                    }
                }
            }
        }
    }
}

bool Window::isGridFull() {
    GameWon = true;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QLayoutItem *item = gridlayout->itemAtPosition(row, col);
            if (item) {
                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(item->widget());
                if (lineEdit) {
                    // Check if the cell is empty or contains an invalid number
                    bool ok;
                    int value = lineEdit->text().toInt(&ok);
                    if (!ok || value < 1 || value > 9) {
                        GameWon = false; // Found an empty or invalid cell
                    }
                }
            }
        }
    }
    return GameWon; // All cells are full with valid numbers
}

void Window::setLineEditSize(int size) {

    int maxValue = pow(10, size) - 1; 
    for(int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(gridlayout->itemAtPosition(row, col)->widget());
            lineEdit->setMaxLength(std::max(lineEdit->text().length() + 1, size)); 
            lineEdit->setValidator(new QIntValidator(1, maxValue, this));
        }
    }
}

std::string Window::cleanPencilInput(std::string inputData) {

    if(inputData.empty() || inputData.length() == 1) {
        return inputData; 
    }

    size_t pos = inputData.find("0");
    while (pos < inputData.length()) {
        inputData.erase(pos, 1);
        pos = inputData.find("0");
    }

    if(lastDigitPresent(inputData)) {
    
        // cout << "Before erase: " << inputData << endl; 
        char lastChar = inputData.back();
        size_t pos = inputData.find(lastChar);
        while (pos < inputData.length()) {
            inputData.erase(pos, 1);
            pos = inputData.find(lastChar);
        }
    }
    std::sort(inputData.begin(), inputData.end());
    return inputData;

}

bool Window::lastDigitPresent(std::string inputData) {

    if (inputData.empty()) {
        return false;
    }

    char lastChar = inputData.back(); 

    for (size_t i = 0; i < inputData.size() - 1; i++) {
        if (inputData[i] == lastChar) {
            return true;
        }
    }
    return false;

}
