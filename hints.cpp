#include "hints.h"
#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLayout>

HintsWindow::HintsWindow(QWidget *parent) : QWidget(parent) {
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    QFont font = textEdit->font();  // Get the current font
    font.setPointSize(14); 
    

    textEdit->setFont(font);  // Apply the font to the textEdit widget

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(textEdit);

    this->setLayout(layout);
    this->setFixedSize(300, 600); // Set a default size for the hints window
}


//Show the hint for the user
void HintsWindow::showHint() {
    show();
    textEdit->setText(getHint().c_str());
    }

QTextEdit *textEdit;
//String of all the hint being used for the game 
std::string HintsWindow::getHint() {
    static std::vector<std::string> hints = {
        "Look for numbers that can only go in one spot.\n",
        "Count the number of the same value in a row, column or sub-section blocks.\n",
        "Focus on a specific row, column or sub-section block to complete it.\n",
        "Check if any rows, columns, or blocks are missing a specific number.\n",
        "Focus on the numbers that appear most frequently.\n",
        "Consider the numbers that are already present and what numbers are missing.\n"
    };

    static int hintIndex = 0;
    std::string hint = hints[hintIndex];
    hintIndex = (hintIndex + 1) % hints.size();
    return hint;
};
//Main function
// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//     MainWindow window;
//     //window.show();
//     return app.exec();
// }
