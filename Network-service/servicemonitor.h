#ifndef SERVICEMONITOR_H
#define SERVICEMONITOR_H
#include <QThread>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QWidget>
#include <ZSmtp.h>
#include <QSettings>
#include <QMessageBox>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

class ServiceMonitor : public QThread
{
    Q_OBJECT
public:
    explicit ServiceMonitor(QWidget *creator,int choice,QString ip,QString port,int id):m_creator(creator){

    this->choice = choice;
    this->ip = ip;
    this->port = port;
    this->id = id;

    manager = new QNetworkAccessManager(this);
    timeoutTimer = new QTimer(this);
    connect(timeoutTimer, &QTimer::timeout, this, &ServiceMonitor::handleTimeout);


    };
    QWidget *creator() const {
        return m_creator;
    }
    void run();

signals:
    void end_monitor();
    void send_data(QString log);

private:
    QRegularExpression serviceInterruptionRegex;
    QString lastServiceStatus;
    QString alert;

    void sendSMSNotification();
    QWidget *m_creator;

    QNetworkAccessManager *manager;
    QTimer *timeoutTimer;
    QNetworkReply *currentReply;

    int choice;
    QString ip;
    QString port;

    int id;

    bool testHttp(const QString &ip, quint16 port, int timeoutMs=3000);
    bool testFtp(const QString &ip, quint16 port, int timeoutMs=3000);
    bool testSmtp(const QString &ip, quint16 port, int timeoutMs=3000);
    void sendEmail();


private slots:
    void handleTimeout();
    void handleNetworkReply();
};

#endif // SERVICEMONITOR_H
