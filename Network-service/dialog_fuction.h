#ifndef DIALOG_FUCTION_H
#define DIALOG_FUCTION_H

#include <QDialog>

namespace Ui {
class Dialog_fuction;
}

class Dialog_fuction : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_fuction(QWidget *parent = nullptr);
    ~Dialog_fuction();

private:
    Ui::Dialog_fuction *ui;
};

#endif // DIALOG_FUCTION_H
