#ifndef END_BTN_H
#define END_BTN_H

#include <QPushButton>

class end_btn : public QPushButton
{
    Q_OBJECT
public:
    end_btn(int);
    int id;

private slots:
    void on_end_btn_clicked();

signals:
    void sendid(int);

};

#endif // END_BTN_H
