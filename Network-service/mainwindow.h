#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "loghistory.h"
#include "qboxlayout.h"
#include "servicemonitor.h"
#include "display_label.h"
#include "end_btn.h"
#include <QFileDialog>
#include <QUrl>
#include <ZSmtp.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QLabel>
#include <QLinkedList>
#include "DbConnectionPool.h"
#include "monitor_timer.h"

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

    void startThread(int);

//    void on_end_task1_clicked();

//    void on_end_task2_clicked();

//    void on_end_task3_clicked();

    void on_btn_openlog_clicked();

    void log_display_updata(QString data,int);

    void displayNotification(QString,int);

    void Create_Logdatabase();

    void end_task(int id);
private:
    void init();
    void initConfig();

    bool saveConfig();

    void setWidgetEnable(bool flag);


    void sendSMSNotification();


    QVBoxLayout *ScrollContentLayout;
    QWidget *ScrollContentWidget;

    QSettings *m_settings;

//    QLinkedList<QTimer*> monitor_timers;
    QLinkedList<Monitor_Timer*> monitor_timers;
    QLinkedList<ServiceMonitor*> monitors;
    QLinkedList<int> monitor_checks;

//    QTimer *monitor_timer[3];
//    ServiceMonitor *monitor[3] = {};
//    int monitor_check[3] = {0,0,0};


    LogHistory *loghistory;
    void updata_database(QString data);

    QLinkedList<display_label*> display_labels;
    QLinkedList<end_btn*> end_btns;

    int display_unit_cout = 0;

    template <typename T>
    void insertNode(QLinkedList<T>& list, int index, const T& data) ;
    template <typename T>
    void removeNode(QLinkedList<T>& list, int index);


    // 链表遍历模板函数
    template<typename T>
    typename QLinkedList<T>::iterator getIteratorAtIndex(QLinkedList<T>& list, int index);

    //链表节点删除后更新id
    template<typename NodeType>
    void updateNodeIds(QLinkedList<NodeType*>& list, int startId);


};

#endif // MAINWINDOW_H
