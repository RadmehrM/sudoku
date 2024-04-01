#include "window.h"
#include <QApplication>
#include <QStyleFactory>
 
int main(int argc, char *argv[]) 
{
  QApplication app(argc, argv);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  Window window;
  window.resize(800,800);
  window.setWindowTitle("Sudoku");
  
  window.show();
  return app.exec();
}
 