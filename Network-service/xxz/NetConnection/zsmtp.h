#ifndef ZSMTP_H
#define ZSMTP_H

#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>
#include <QUrl>
#include "dialog_function.h"
#include "ui_dialog_function.h"
#include "dialog_function.h"

#define EMAIL_ERROR     0   //邮件发送失败
#define EMAIL_SUCCEED   1   //邮件发送成功

class ZSmtp : public QObject
{
    Q_OBJECT
public:
    explicit ZSmtp(QString serverIP = "smtp.qq.com", QObject *parent = NULL);
    ~ZSmtp();
    void sendEmail(QString username, QString password, QString to, QString title, QString text, QString ip,qint32 port);

private:
    QString serverIP;
    QTcpSocket *tcpSocket;
    QString username;
    QString password;
    QString to;
    QString title;
    QString text;
    QByteArray serverText;
    qint32 port;
    int status;

signals:
    void disconnected();
    void emailStatus(int status);   //邮件发送的状态
    void progress(double p);
    void webConnectionStatus(bool success);

public slots:
    void connectToServer();
    void disconnectFromServer();
    void getMessage();
    void WebConnection();

};

#endif // ZSMTP_H
