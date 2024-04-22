#ifndef DIALOG_FUNCTION_H
#define DIALOG_FUNCTION_H

#include <QDialog>

namespace Ui {
class Dialog_function;
}

class Dialog_function : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_function(QWidget *parent = nullptr);
    ~Dialog_function();

private slots:

    void on_pushButton_clicked();

private:
    Ui::Dialog_function *ui;

signals:
    void closeButtonClicked();
};


#endif // DIALOG_FUNCTION_H
