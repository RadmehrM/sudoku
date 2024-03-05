#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <vector>

class Button {
private:
    std::string name;
    bool isPressed;

public:
    // Constructor
    Button(const std::string& name);

    // Method to display help tab
    void showHelpTab();

    // Method to display about tab
    void showAboutTab();

    // Method to display metrics tab
    void showMetricsTab();

    // Method to display options
    void showOptions();

    // Method to show hints; takes a 2D int array as the board
    int showHints(const std::vector<std::vector<int>>& board);

    // Method to show or hide the timer
    bool showTimer();
};

#endif // BUTTON_H
