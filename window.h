#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>

namespace Ui {
  class Window;
}
 
class Window : public QMainWindow
{
  Q_OBJECT
public:
  explicit Window(QWidget *parent = nullptr);
private slots:
  // void handleButton();
private:
  QGridLayout *gridlayout;
};
#endif
