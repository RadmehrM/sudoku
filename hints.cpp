/**
 * @brief Hints Class
 * 
 * This class is used to help configure the hints component in the user interface.
 * 
 * @author Daniel Gomes
 * @author Zain Raza
 * @author Radmehr Mehdipour
 * @author Sreethan Vuppala
 * @author Aidan Freeman
 */

#include "hints.h"
#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLayout>

/**
 * @brief Constructs the HintsWindow widget.
 * 
 * Initializes the HintsWindow with a text edit field for displaying hints.
 * The text edit is set to read-only and is configured with an appropriate font size.
 * 
 * @param parent The parent widget which owns this HintsWindow instance.
 */
Hints::Hints(QWidget *parent) : QWidget(parent) {
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    QFont font = textEdit->font();  // Get the current font
    font.setPointSize(14);  // Set the font size to 12 points
    

    textEdit->setFont(font);  // Apply the font to the textEdit widget

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(textEdit);

    this->setLayout(layout);
    this->setFixedSize(300, 600); // Set a default size for the hints window
}


/**
 * @brief Displays a hint to the user.
 * 
 * This method is called to display the hints window with a new hint
 * each time the 'Hint' button is clicked. It cycles through a static list
 * of hints and displays them one by one.
 */
void Hints::showHint() {
    show();
    textEdit->setText(getHint().c_str());
}

QTextEdit *textEdit;

/**
 * @brief Retrieves a hint from a predefined list of hints.
 * 
 * This method cycles through a static list of hints for the Sudoku game,
 * returning each hint in sequence. It wraps around to the beginning of the list
 * once all hints have been shown.
 * 
 * @returns A string containing the next hint to be displayed.
 */
std::string Hints::getHint() {
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