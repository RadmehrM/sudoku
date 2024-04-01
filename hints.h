#ifndef HINTS_H
#define HINTS_H

#include <QWidget>
#include <QTextEdit>

class Hints : public QWidget {
    Q_OBJECT
public:
    explicit Hints(QWidget *parent = nullptr);

public slots:
    void showHint();

private:
    QTextEdit *textEdit;
    std::string getHint();
};

#endif // HINTS_H
