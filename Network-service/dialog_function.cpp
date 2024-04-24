#include "dialog_function.h"
#include "ui_dialog_function.h"


#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QRegularExpression>
#include <QSettings>
#include <QProcess>
#include <QFile>
#include <QDate>

class WebServiceMonitor : public QThread {  //监视类
public:
    WebServiceMonitor();

    void run() override;

    int loadConfiguration();

private:
    QFile* logFile;
    QString phoneNumber;
    QMutex mutex;
    QRegularExpression serviceInterruptionRegex;
    QString lastServiceStatus;
    QString alert;

    void updateLogFile(const QString& status);
    void sendSMSNotification(const QString& message);

};

WebServiceMonitor::WebServiceMonitor() {
    logFile = nullptr;
}

void WebServiceMonitor::run() {
    while (true) {
        // 检查服务状态，是否中断/异常
        QFile logFileCopy(logFile->fileName());

        if (logFileCopy.open(QIODevice::ReadOnly)) {
            QTextStream logStream(&logFileCopy);
            QString line;
            while (!logStream.atEnd()) {
                line = logStream.readLine();
                if (serviceInterruptionRegex.match(line).hasMatch()) {
                    // 检测到异常
                    QString status = "服务中断";
                    updateLogFile(status);
                    sendSMSNotification(status);
                    break;
                }
            }
            logFileCopy.close();
        }

        // Check for service status updates from the web
        // ... (replace with your web service status checking code)

        // 用当前服务状态更新日志文件
        QString status = "服务运行中"; // 正常的状态更新
        updateLogFile(status);

        // 监视线程检查间隔
        QThread::sleep(10);
    }
}

void WebServiceMonitor::updateLogFile(const QString& status) {
    QMutexLocker locker(&mutex);

    if (logFile->isOpen()) {
        QTextStream logStream(logFile);
        logStream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << ": " << status << Qt::endl;
    }

    lastServiceStatus = status;
}

void WebServiceMonitor::sendSMSNotification(const QString& message) {
    //发短信代码

}

int WebServiceMonitor::loadConfiguration() {
    QSettings settings("QtWebServiceMonitor", "WebServiceMonitor");
    phoneNumber = settings.value("phoneNumber", "").toString();
    QString logFilePath = settings.value("logFile", "").toString();

    if (!phoneNumber.isEmpty() && !logFilePath.isEmpty()) {
        logFile = new QFile(logFilePath);
        if (!logFile->open(QIODevice::ReadWrite)) {
            delete logFile;
            logFile = nullptr;
            // Handle error opening log file
            qDebug() << "日志无法打开！请检查配置。";
            return -1;
        }
    } else {
        qDebug() << "配置未填写完全，请检查配置。";
        return 0;
    }
    return 1;
}









Dialog_function::Dialog_function(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_function)
{
    ui->setupUi(this);
}

Dialog_function::~Dialog_function()
{
    delete ui;
}



void Dialog_function::on_btn_back_clicked()
{
    emit closeButtonClicked();

    this->close();
}




void Dialog_function::on_btn_config_clicked()
{
    dialog_config.show();
}

