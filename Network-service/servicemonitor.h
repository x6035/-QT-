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
    explicit ServiceMonitor(int choice,QString ip,QString port,int id,bool flag_email,bool flag_phone){

    this->choice = choice;
    this->ip = ip;
    this->port = port;
    this->id = id;
    this->flag_email = flag_email;
    this->flag_phone = flag_phone;

    };

    void run();

signals:
    void end_monitor();
    void send_data(QString log,int);
    //typ:1警报，2：提示
    void SendNotification(QString,int typ);

private:

    QNetworkAccessManager *manager;
    QTimer *timeoutTimer;
    QNetworkReply *currentReply;

    int choice;
    QString ip;
    QString port;
    int id;
    bool flag_phone;
    bool flag_email;

    void sendSMSNotification();
    bool testHttp(const QString &ip, quint16 port, int timeoutMs=3000);
    bool testFtp(const QString &ip, quint16 port, int timeoutMs=3000);
    bool testSmtp(const QString &ip, quint16 port, int timeoutMs=3000);
    void sendEmail();


private slots:
    void handleNetworkReply();
};

#endif // SERVICEMONITOR_H
