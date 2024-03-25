<<<<<<< HEAD
#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)  {
        QVBoxLayout *layout = new QVBoxLayout(this);


        QSpacerItem *verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacerTop);

        QLabel *titleLabel = new QLabel("Screen Title", this);
        titleLabel->setAlignment(Qt::AlignCenter); // Center the title
        titleLabel->setFont(QFont("Arial", 25, QFont::Bold)); // Set the font to make it look more like a title
        // Assuming you have a layout for your content
        titleLabel->setStyleSheet("QLabel { padding: 20px; }");
        layout->addWidget(titleLabel); 


        QPushButton *button1 = new QPushButton("Start Game", this);
        button1->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button1, 0, Qt::AlignHCenter); // Align the button horizontally in the center

        QPushButton *button2 = new QPushButton("Set Difficulty", this);
        button2->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button2, 0, Qt::AlignHCenter); // Align the button horizontally in the center

        QPushButton *button3 = new QPushButton("Exit", this);
        button3->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button3, 0, Qt::AlignHCenter); // Align the button horizontally in the center

        // Add another spacer at the bottom
        QSpacerItem *verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacerBottom);

        setLayout(layout);
};
=======
#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)  {
        QVBoxLayout *layout = new QVBoxLayout(this);


        QSpacerItem *verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacerTop);

        QLabel *titleLabel = new QLabel("Screen Title", this);
        titleLabel->setAlignment(Qt::AlignCenter); // Center the title
        titleLabel->setFont(QFont("Arial", 25, QFont::Bold)); // Set the font to make it look more like a title
        // Assuming you have a layout for your content
        titleLabel->setStyleSheet("QLabel { padding: 20px; }");
        layout->addWidget(titleLabel); 


        QPushButton *button1 = new QPushButton("Start Game", this);
        button1->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button1, 0, Qt::AlignHCenter); // Align the button horizontally in the center

        QPushButton *button2 = new QPushButton("Set Difficulty", this);
        button2->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button2, 0, Qt::AlignHCenter); // Align the button horizontally in the center

        QPushButton *button3 = new QPushButton("Exit", this);
        button3->setFixedSize(QSize(150, 50)); // Set a fixed size for the button
        layout->addWidget(button3, 0, Qt::AlignHCenter); // Align the button horizontally in the center

        // Add another spacer at the bottom
        QSpacerItem *verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(verticalSpacerBottom);

        setLayout(layout);
};
>>>>>>> d0ef0871040ffe8d731b37cb76acaca53aaa2911
