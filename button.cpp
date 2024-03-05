#include <string>
#include <vector>

class Button {
private:
    std::string name;
    bool isPressed;

public:
    Button(const std::string& name) : name(name), isPressed(false) {}

    // Method to display help tab
    void showHelpTab() {
        // Implementation goes here
    }

    // Method to display about tab
    void showAboutTab() {
        // Implementation goes here
    }

    // Method to display metrics tab
    void showMetricsTab() {
        // Implementation goes here
    }

    // Method to display options
    void showOptions() {
        // Implementation goes here
    }

    // Method to show hints; takes a 2D int array as the board
    int showHints(const std::vector<std::vector<int>>& board) {
        // Implementation goes here
        // This method likely needs more detail on what the int return represents
    }

    // Method to show or hide the timer
    bool showTimer() {
        // Implementation goes here
        // Based on the method's name, a void return type might be more appropriate
    }
};
