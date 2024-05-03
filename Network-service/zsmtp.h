#ifndef ZSMTP_H
#define ZSMTP_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

#define EMAIL_ERROR     0   //邮件发送失败
#define EMAIL_SUCCEED   1   //邮件发送成功

class ZSmtp : public QObject
{
    Q_OBJECT
public:
    explicit ZSmtp(QString serverIP = "smtp.qq.com",int port = 25, QObject *parent = NULL);
    ~ZSmtp();
    void sendEmail(QString username, QString password, QString to, QString title, QString text, QString ip = "", int port=25);
    // 测试 SMTP 服务
    void testSmtpService(QString ip,int port);
    bool getTestStatus() {return testStatus;}
private:
    QString serverIP;
    QTcpSocket *tcpSocket;
    QString username;
    QString password;
    QString to;
    QString title;
    QString text;
    QByteArray serverText;
    int status;
    bool isTest{false};
    int port{0};
    bool testStatus{false};

signals:
    void disconnected();
    void emailStatus(int status);   //邮件发送的状态
    void progress(double p);
    void smtpServiceTested(bool available); // SMTP 服务测试结果

public slots:
    void connectToServer();
    void disconnectFromServer();
    void getMessage();

    void sendEmailSlot(QString username, QString password, QString to, QString title, QString text);
    // 处理 SMTP 服务测试结果
    void processSmtpServiceTest();

};

#endif // ZSMTP_H
