/**
 * @brief Main Class
 * 
 * This class is used to run the Sudoku game.
 * 
 * @author Daniel Gomes
 * @author Zain Raza
 * @author Radmehr Mehdipour
 * @author Sreethan Vuppala
 * @author Aidan Freeman
 */

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
 