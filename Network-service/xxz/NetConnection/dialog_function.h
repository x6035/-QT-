#ifndef DIALOG_FUNCTION_H
#define DIALOG_FUNCTION_H

#include <QDialog>
#include <QTcpSocket>
#include "Dialog_config.h"

namespace Ui {
class Dialog_function;
}

class Dialog_function : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_function(QWidget *parent = nullptr);
    Ui::Dialog_function *ui;
    ~Dialog_function();

private slots:

    void on_btn_back_clicked();

    void on_btn_config_clicked();

    void on_btn_start_clicked();

    void on_disconnectFromServer_clicked();

    void on_sendButton_clicked();

private:

    QTcpSocket *tcpSocket;

    Dialog_config dialog_config;

signals:

    void closeButtonClicked();

public slots:

};


#endif // DIALOG_FUNCTION_H
