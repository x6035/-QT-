#include "ZSmtp.h"
#include <QHostInfo>
#include <QUrl>
#include <QDebug>

ZSmtp::ZSmtp(QString serverIP, QObject *parent) : QObject(parent)
{
    this->serverIP = serverIP;
    tcpSocket = new QTcpSocket;
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectToServer()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectFromServer()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));
}

ZSmtp::~ZSmtp()
{
    delete tcpSocket;
}

void ZSmtp::sendEmail(QString username, QString password, QString to, QString title, QString text, QString ip,qint32 port)
{
    this->serverIP=ip;
    this->username = username;
    this->password = password;
    this->to = to;
    this->title = title;
    this->text = text;
    this->port= port;
    tcpSocket->abort();
    serverText.clear();
    status = 0;
    tcpSocket->connectToHost(serverIP, port);
}
void ZSmtp::WebConnection()
{
    QUrl siteUrl(url);
        QString host = siteUrl.host();
        quint16 port = (siteUrl.scheme().toLower() == "https") ? 443 : 80;  // 默认使用80端口，HTTPS使用443端口

        // 创建一个临时的TCP套接字来测试连接
        QTcpSocket tempSocket;
        tempSocket.connectToHost(host, port);
        if (tempSocket.waitForConnected(3000)) {  // 等待3秒以检测是否成功连接
            qDebug() << "Connection to " << url << " succeeded.";
            emit webConnectionStatus(true);
        } else {
            qDebug() << "Connection to " << url << " failed.";
            emit webConnectionStatus(false);
        }
}

void ZSmtp::connectToServer()
{
    QString info = QString("<font style='color:green'>%1<br></font>").arg("连接到服务器");
    qDebug()<<info;
}

void ZSmtp::disconnectFromServer()
{
    QString info = QString("<font style='color:red'>%1<br></font>").arg("与服务器断开连接");
    qDebug()<<info;
}

#define STATUS_MAX 6

void ZSmtp::getMessage()
{
    QByteArray curText = tcpSocket->readAll();
    serverText.append(curText);
    QByteArray text;
    if(serverText.indexOf("Error")!=-1 || serverText.indexOf("503")!=-1)
    {
        qDebug()<<"get the Error message";
        emit emailStatus(EMAIL_ERROR);
        tcpSocket->disconnectFromHost();
        return ;
    }
    if(status==5 && serverText.indexOf("250")!=-1)
    {
        // 登出
        text.append("QUIT\r\n");
        status = 6;
    }
    else if(status==4 && serverText.indexOf("354")!=-1)
    {
        // 发信息
        text.append("Subject:=?utf-8?B?");
        text.append(QByteArray().append(title).toBase64());
        text.append("?=\r\n");
        text.append("To: ");
        text.append(to);
        text.append("\r\nFrom: ");
        text.append(username);
        text.append(" <");
        text.append(username);
        text.append(">\r\n");
        text.append("Content-Type: text/plain; charset=UTF8;\r\n");
        text.append("Content-Transfer-Encoding: 7BIT\r\n\r\n");
        QString t = this->text;
        t.replace("\n", "\r\n").replace("\r\n.\r\n", "\r\n..\r\n");
        text.append(t);
        text.append("\r\n.\r\n");
        status = 5;
    }
    else if(status==3 && serverText.indexOf("250")!=-1)
    {
        // DATA
        text.append("DATA\r\n");
        status = 4;
    }
    else if(status==2 && serverText.indexOf("235")!=-1)
    {
        // 发送方和接收方
        text.append("MAIL FROM: <");
        text.append(username);
        text.append(">\r\n");
        text.append("RCPT TO: <");
        text.append(to);
        text.append(">\r\n");
        status = 3;
    }
    else if(status==1 && serverText.indexOf("334")!=-1)
    {
        // 登录
        text.append(QByteArray().append(username).toBase64());
        text.append("\r\n");
        text.append(QByteArray().append(password).toBase64());
        text.append("\r\n");
        status = 2;
    }
    else if(status==0 && serverText.indexOf("220")!=-1)
    {
        text.append("EHLO ");
        text.append(serverIP);
        text.append("\r\nAUTH LOGIN\r\n");
        status = 1;
    }

    // 写入文件
    QFile file("email_data.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&file);
        out << text;
        file.close();
    }

    // 更新进度
    emit progress((double)status / STATUS_MAX);
    if(status == 6)
    {
        emit emailStatus(EMAIL_SUCCEED);
        tcpSocket->disconnectFromHost();
    }
}

