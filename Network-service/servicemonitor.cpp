#include "servicemonitor.h"


void ServiceMonitor::sendEmail()
{
    QSettings settings("config.ini", QSettings::IniFormat);

    ZSmtp *smtp = new ZSmtp;//默认是qq邮箱服务器，想用别的服务器就 new ZSmtp(Smtp服务器地址)
    connect(smtp, SIGNAL(disconnected()), smtp, SLOT(deleteLater()));	//发送完毕自行销毁
    smtp->sendEmail(settings.value("SendEmailAddress").toString(),
                    settings.value("SendEmailPwd").toString(),
                    settings.value("ReceiveEmailAddress").toString(),
                    "警告", "您所监测的服务终止！");
    emit SendNotification("您所监测的服务异常，已向邮箱发送邮件！",1);

}

 //发短信代码
void ServiceMonitor::sendSMSNotification() {

    QSettings settings("config.ini", QSettings::IniFormat);

    // 读取值
    QString appcode = settings.value("AppCode").toString();
    QString mobile = settings.value("PhoneNumber").toString();

    // 设置请求参数

    QString content = "%E3%80%90%E7%BD%91%E7%BB%9C%E6%9C%8D%E5%8A%A1%E7%9B%91%E6%B5%8B%E7%B3%BB%E7%BB%9F%E3%80%91%E8%AD%A6%E6%8A%A5%EF%BC%9A%E6%82%A8%E6%89%80%E7%9B%91%E6%B5%8B%E7%9A%84%E6%9C%8D%E5%8A%A1%E5%87%BA%E7%8E%B0%E5%BC%82%E5%B8%B8%EF%BC%81"; // 替换为您要发送的短信内容

    // 构造请求URL
    QUrl url("https://zwp.market.alicloudapi.com/sms/sendv2");
    url.setQuery("mobile=" + mobile + "&content=" + content);

    // 设置请求头
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Authorization", ("APPCODE " + appcode).toUtf8());

    // 发送请求并处理响应
    currentReply = manager->get(request);

    // 创建一个事件循环
    QEventLoop loop;

    // 创建一个定时器，在40秒后停止事件循环
    QTimer::singleShot(40000, &loop, &QEventLoop::quit);

    // 连接reply的finished()信号和定时器的超时信号到事件循环的退出槽
    QObject::connect(currentReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//    QObject::connect(&loop, &QEventLoop::quit, this, &ServiceMonitor::quit);

    // 运行事件循环，阻塞当前线程
    loop.exec();

    // 当事件循环退出后，检查请求的结果
    handleNetworkReply();
    // 清理资源
    currentReply->deleteLater();
}




void ServiceMonitor::handleNetworkReply() {

    if (currentReply->error() == QNetworkReply::NoError) {
         // 解析JSON响应
        QByteArray responseData = currentReply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = document.object();

        // 检查响应状态
        int code = jsonObject["error_code"].toInt();
        if (code == 0) {
            emit SendNotification("服务异常，已向手机发送短信！",1);
//            qDebug() << "服务异常，已向手机发送短信！";
        } else {
            qDebug() << "短信发送失败，错误码";
            emit SendNotification("短信发送失败，错误码："+ QString::number(code) + '\n' + "错误信息："+\
                QUrl::fromPercentEncoding(jsonObject["reason"].toString().toUtf8()),0);
            }
    }
    currentReply->deleteLater();
}


bool ServiceMonitor::testHttp(const QString &ip, quint16 port, int timeoutMs)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://%1:%2").arg(ip).arg(port)));
    request.setRawHeader("Host", (ip + ":" + QString::number(port)).toUtf8());

    QEventLoop loop;
    QTimer timer;

    QObject::connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    timer.start(timeoutMs);
    QNetworkReply *reply = manager->get(request);
    loop.exec();

    // 获取HTTP状态码
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return reply->error() == QNetworkReply::NoError && statusCode >=200 && statusCode <=400;
}

bool ServiceMonitor::testFtp(const QString &ip, quint16 port, int timeoutMs)
{
    QTcpSocket socket;
    QEventLoop loop;
    QTimer timer;

    QObject::connect(&socket, &QTcpSocket::connected, &loop, &QEventLoop::quit);
    QObject::connect(&socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::errorOccurred), &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    timer.start(timeoutMs);
    socket.connectToHost(ip, port);
    loop.exec();

    return socket.state() == QTcpSocket::ConnectedState;
}

bool ServiceMonitor::testSmtp(const QString &ip, quint16 port, int timeoutMs)
{
    ZSmtp zsmtp(ip,port);
    QEventLoop loop;
    QTimer timer;

    QObject::connect(&zsmtp, &ZSmtp::emailStatus, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    timer.start(timeoutMs);
    zsmtp.testSmtpService(ip, port);
    loop.exec();

    return zsmtp.getTestStatus();
}




void ServiceMonitor::run()
{
    manager = new QNetworkAccessManager();

    bool flag{false};
    if(choice == 0) {
        flag = testHttp(ip,port.toUShort());
    }else if (choice == 1){
        flag = testFtp(ip,port.toUShort());
    }else if (choice == 2){
        flag =testSmtp(ip,port.toUShort());
    }
    QString flag_des;
    if (flag)
        flag_des = "正常";
    else
        flag_des = "异常";

    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 将日期和时间转换为字符串
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd-hh:mm:ss");

    //写日志等操作
    emit send_data(QString::number(id,10)+"  "+currentDateTimeString+"  "+ip+":"+port+"  "+flag_des);


    qDebug()<<flag;
    if(!flag){
        if(flag_email)
            sendEmail();
        if(flag_phone)
        {
            sendSMSNotification();
        }
        emit end_monitor();
    }
}
