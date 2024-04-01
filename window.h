
#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QVector>
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>
#include "board.h"
#include "menu.h"
#include "hints.h"
#include <QStringList>
#include <QSet>
#include <QString>

 
class Window : public QMainWindow {
  Q_OBJECT

public:
  explicit Window(QWidget *parent = nullptr);
  QStackedWidget *stackedWidget;
  bool GameWon=false;


public slots:
    void onDifficultyChanged(int newDifficulty);
    void beginGame();


private slots:
  void setLineEditValue(int N, int M, const QString &value);
  void validateInput();
  void updateBoard();
  void updateTimerDisplay();
  void updateCellBorder();
  bool isGridFull();
  void togglePencilMode();
  void setLineEditSize(int size); 


private:
  int currentDifficultyIndex = 0; 
  const std::vector<std::string> difficulties = {"Easy", "Medium", "Hard"};
  int score; // Holds the current score
  QVector<int> scores; // Vector to hold scores of completed games
  
  QElapsedTimer *gameTimer;
  QVector<qint64> gameDurations; 
  QVector<int> gameDifficulties; 

  QGridLayout *gridlayout;
  QPushButton *fillGridButton;  // Button to fill the grid with a solved puzzle
  QPushButton *newGameButton;   // Button to generate a new puzzle
  QPushButton difficultyButton; 
  QPushButton pencilModeButton;
  Board *sudokuBoard; 
  QLabel *scoreLabel;
  QPushButton *viewLogbookButton;
  QWidget *centralWidget;
  Hints *hintsWindow;
  QLineEdit *lineEdit;
  QTextEdit *textEdit; 
  QLabel *timerLabel; // Label to display the timer
  QTimer *updateTimer; // Timer to trigger the display update
  bool pencilModeOn;
  int difficulty; 
  
  void checkConflict(int row, int col, int value, QLineEdit* sender, QVector<QLineEdit*>& conflictCells);
  void createButtons();
  void showWinningAnimation();
  void createLayout();
  void showLogbook(); 
  void incrementScore(int value); // Helper function to increment the score
  void decrementScore(int value); 
  void updatePencilModeUI();
  std::string cleanPencilInput(std::string inputData);
  bool lastDigitPresent(std::string inputData); 
  void changeDifficulty();

};

#endif  // WINDOW_H
