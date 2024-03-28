#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QVector>
#include <QLabel>
#include <QElapsedTimer>
#include "board.h"
#include "menu.h"
#include "hints.h"


namespace Ui {
  class Window;
}
 
class Window : public QMainWindow {
  Q_OBJECT

public:
  explicit Window(QWidget *parent = nullptr);
  QStackedWidget *stackedWidget;


public slots:
    void onDifficultyChanged(int newDifficulty);
    void beginGame();


private slots:
  void setLineEditValue(int N, int M, const QString &value);
  void validateInput();
  void updateBoard();

private:
  int score; // Holds the current score
  QVector<int> scores; // Vector to hold scores of completed games
  QElapsedTimer *gameTimer;

  QGridLayout *gridlayout;
  QPushButton *fillGridButton;  // Button to fill the grid with a solved puzzle
  QPushButton *newGameButton;   // Button to generate a new puzzle
  Board *sudokuBoard; 
  QLabel *scoreLabel;
  QPushButton *viewLogbookButton;
  QWidget *centralWidget;
  HintsWindow *hintsWindow;
  
  void checkConflict(int row, int col, int value, QLineEdit* sender, QVector<QLineEdit*>& conflictCells);
  void createButtons();
  void createLayout();
  void showLogbook(); 
  void incrementScore(int value); // Helper function to increment the score
};

#endif

