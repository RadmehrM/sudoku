#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "board.h"

namespace Ui {
  class Window;
}
 
class Window : public QMainWindow
{
  Q_OBJECT
public:
  explicit Window(QWidget *parent = nullptr);
private slots:
  void setLineEditValue(int N, int M, const QString &value);
private:
  QGridLayout *gridlayout;
};
#endif

