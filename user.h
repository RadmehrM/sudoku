#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::vector<int> Statistics; // Assuming 'Statistics' is a vector of integers
    std::string displayName;
    int puzzlesCompleted;

public:
    // Constructor
    User();

    // Method to display user statistics; takes an array of integers
    void showStatistics(const std::vector<int>& stats);

    // Method to create an account
    void createAccount();

    // Method for user login
    void login();

    // Method for user logout
    void logout();

    // Method to find average time; takes an array of integers representing times
    std::vector<int> findAverageTime(const std::vector<int>& times);

    // Destructor
    ~User();
};

#endif // USER_H
