#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Window {
private:
    bool isPencil;

public:
    // Constructor
    Window();

    // Method to display a message
    void displayMessage(const std::string& message);

    // Method to write notes, functionality not specified in UML
    void writeNotes();

    // Method to display an error message, functionality not specified in UML
    std::string displayErrorMessage();

    // Method to display a win message, functionality not specified in UML
    std::string displayWinMessage();

    // Destructor
    ~Window();
};

#endif // WINDOW_H
