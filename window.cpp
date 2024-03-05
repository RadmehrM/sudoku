#include <string>

class Window {
private:
    bool isPencil;

public:
    // Constructor is not defined in the UML diagram.
    // Assuming default constructor here.
    Window() : isPencil(false) {}

    // Method to display a message
    void displayMessage(const std::string& message) {
        // Implementation goes here
    }

    // Method to write notes, functionality not specified in UML
    void writeNotes() {
        // Implementation goes here
    }

    // Method to display an error message, functionality not specified in UML
    std::string displayErrorMessage() {
        // Implementation goes here
        // This function should probably not return a string but rather modify the window directly.
        // Return type has been kept as string to match the UML diagram.
    }

    // Method to display a win message, functionality not specified in UML
    std::string displayWinMessage() {
        // Implementation goes here
        // This function should probably not return a string but rather modify the window directly.
        // Return type has been kept as string to match the UML diagram.
    }

    // Destructor is not defined in the UML diagram.
    // Assuming default destructor here.
    ~Window() {}
};
