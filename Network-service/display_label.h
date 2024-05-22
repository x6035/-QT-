#ifndef DISPLAY_LABEL_H
#define DISPLAY_LABEL_H
#include <QLabel>

class display_label :public QLabel
{
public:
    display_label(QWidget *parent = nullptr,int id = 0) : QLabel(parent)
    {
        this->id = id;

        // Additional statements can be added here
        // For example:
        setText("Hello, world!"); // Set text for the label
    }
    int id;
private:

};

#endif // DISPLAY_LABEL_H
