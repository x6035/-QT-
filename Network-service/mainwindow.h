#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "loghistory.h"
#include "servicemonitor.h"
#include <QFileDialog>
#include <QUrl>
#include <ZSmtp.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

private slots:
    void on_btn_enter_clicked();

    void on_btn_back_clicked();

    void on_confBtn_clicked();

    void on_btn_saveconfig_clicked();

    void on_btn_CancelConfig_clicked();

    void on_btn_close_clicked();

    void on_CB_mail_stateChanged();

    void on_CB_phone_stateChanged();

    void on_btn_new_task_clicked();

    void startThread(int i);

    void on_end_task1_clicked();

    void on_end_task2_clicked();

    void on_end_task3_clicked();

    void on_btn_openlog_clicked();

    void log_display_updata(QString data);

    void displayNotification(QString,int);

private:
    void init();
    void initConfig();

    bool saveConfig();
    void setWidgetEnable(bool flag,int which_monitor);
    void sendSMSNotification();

    QSettings *m_settings;

    QTimer *monitor_timer[3];
    ServiceMonitor *monitor[3] = {};
    int monitor_check[3] = {0,0,0};

    void Create_Logdatabase();
    void updata_database(QString data);

    LogHistory *loghistory;


};

#endif // MAINWINDOW_H
