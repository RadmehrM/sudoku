#include "window.h"
#include <QApplication>
 
int main(int argc, char *argv[]) 
{
  QApplication app(argc, argv);
  Window window;
  window.resize(900,900);
  window.setWindowTitle("Sudoku");
  
  window.show();
  //window.showMaximized();
  return app.exec();
}
 