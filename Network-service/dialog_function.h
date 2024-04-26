#ifndef DIALOG_FUNCTION_H
#define DIALOG_FUNCTION_H

#include <QDialog>
#include "Dialog_config.h"


#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QProcess>
#include <QFile>
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

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

    void on_btn_back_clicked();

    void on_btn_config_clicked();

    void on_btn_start_clicked();

private:
    Ui::Dialog_function *ui;
    Dialog_config dialog_config;


signals:
    void closeButtonClicked();
};


#endif // DIALOG_FUNCTION_H
