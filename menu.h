#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include "board.h"


class Menu : public QWidget {
    Q_OBJECT
public:
    Menu(QWidget *parent = nullptr);
    int getDifficulty();


private slots:
    void startGame();
    void changeDifficulty();
    void exit();

private:
    int currentDifficultyIndex = 0; // Use a class member instead of a global variable
    const std::vector<std::string> difficulties = {"Easy", "Medium", "Hard"};
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;

signals:
    void difficultyChanged(int newDifficulty);
    void beginGame();
};


#endif // MENU_H