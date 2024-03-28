#include "hints.h"
#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QShortcut>

//Create the main window when the hint page opens
HintsWindow::HintsWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 150);
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    //An additional message for the user 
    textEdit ->append("Press the 'h' key to receive a new hint");
    setStyleSheet("background-color: none;");
    QShortcut *shortcut = new QShortcut(QKeySequence("h"), this);
    connect(shortcut, &QShortcut::activated, this, &HintsWindow::showHint);

    this->setStyleSheet("border: solid 2px black;");
    //hide();
}

//Show the hint for the user
void HintsWindow::showHint() {
    show();
    textEdit->append(getHint().c_str());
    }

QTextEdit *textEdit;
//String of all the hint being used for the game 
std::string HintsWindow::getHint() {
    static std::vector<std::string> hints = {
        "Look for numbers that can only go in one spot.",
        "Count the number of the same value in a row, column or sub-section blocks.",
        "Focus on a specific row, column or sub-section block to complete it.",
        "Check if any rows, columns, or blocks are missing a specific number.",
        "Focus on the numbers that appear most frequently.",
        "Consider the numbers that are already present and what numbers are missing."
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
