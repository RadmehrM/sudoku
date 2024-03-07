#include "window.h"
#include "board.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
  // Create the button, make "this" the parent
  m_button = new QPushButton("My Button", this);
  // set size and location of the button
  m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
 
  // Connect button signal to appropriate slot
  connect(m_button, &QPushButton::released, this, &Window::handleButton);
}

void Window::handleButton() {
  // Empty implementation or the actual functionality you want to trigger on button press.
}
 
// void Window::handleButton()
// {
//   // change the text
//   m_button->setText("Example");
//   // resize button
//   m_button->resize(100,100);
// }