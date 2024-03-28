#ifndef HINTSWINDOW_H
#define HINTSWINDOW_H

#include <QWidget>
#include <QTextEdit>

class HintsWindow : public QWidget {
    Q_OBJECT
public:
    explicit HintsWindow(QWidget *parent = nullptr);

private slots:
    void showHint();

private:
    QTextEdit *textEdit;
    std::string getHint();
};

#endif // HINTSWINDOW_H
