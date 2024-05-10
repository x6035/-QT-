#ifndef LOGHISTORY_H
#define LOGHISTORY_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class LogHistory;
}

class LogHistory : public QDialog
{
    Q_OBJECT

public:
    explicit LogHistory(QWidget *parent = nullptr,QString data = "");


    ~LogHistory();
    Ui::LogHistory *ui;

private slots:
    void on_btn_back_clicked();

    void on_btn_clear_clicked();



};

#endif // LOGHISTORY_H
