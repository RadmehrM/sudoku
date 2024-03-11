#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QVector>
#include "board.h"

namespace Ui {
  class Window;
}
 
class Window : public QMainWindow {
  Q_OBJECT

public:
  explicit Window(QWidget *parent = nullptr);

private slots:
  void setLineEditValue(int N, int M, const QString &value);
  void validateInput();
  void updateBoard();

private:
  QGridLayout *gridlayout;
  QPushButton *fillGridButton;  // Button to fill the grid with a solved puzzle
  QPushButton *newGameButton;   // Button to generate a new puzzle
  Board *sudokuBoard; 

  void checkConflict(int row, int col, int value, QLineEdit* sender, QVector<QLineEdit*>& conflictCells);
  void createButtons();
  void createLayout();
};

#endif

