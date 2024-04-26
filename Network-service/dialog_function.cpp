#include "dialog_function.h"
#include "ui_dialog_function.h"


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


class WebServiceMonitor : public QThread {  //监视类
public:
    WebServiceMonitor(QWidget *creator);

    void run() override;

    int loadConfiguration();

    QObject *creator() const {
        return m_creator;
    }

private:
    QFile* logFile;
    QString phoneNumber;
    QString email;
    QString appcode;
    QMutex mutex;
    QRegularExpression serviceInterruptionRegex;
    QString lastServiceStatus;
    QString alert;

    QNetworkAccessManager *manager;
    QTimer *timeoutTimer;
    QNetworkReply *currentReply;

    void updateLogFile(const QString& status);
    void sendSMSNotification(const QString& message);

    QWidget *m_creator;
private slots:
    void handleTimeout();
    void handleNetworkReply();

};


WebServiceMonitor::WebServiceMonitor(QWidget *creator)
    // 在构造函数中接收创建者的地址并存储在成员指针中
    :m_creator(creator) {

    logFile = nullptr;
    manager = new QNetworkAccessManager(this);
    timeoutTimer = new QTimer(this);
    connect(timeoutTimer, &QTimer::timeout, this, &WebServiceMonitor::handleTimeout);
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


 //发短信代码
void WebServiceMonitor::sendSMSNotification(const QString& message) {

    QSettings settings("config.ini", QSettings::IniFormat);

    // 读取"appcode"对应的值
    QString appcode = settings.value("AppCode").toString();
    QString mobile = settings.value("PhoneNumber").toString(); // 替换为您要发送短信的手机号码

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

    // 设置超时定时器
    int timeoutDuration = 60000; // 5000毫秒（5秒）超时
    timeoutTimer->setSingleShot(true);
    timeoutTimer->start(timeoutDuration);

    connect(currentReply, &QNetworkReply::finished, this, &WebServiceMonitor::handleNetworkReply);

}

void WebServiceMonitor::handleTimeout() {
    if (currentReply->isRunning()) {
        currentReply->abort();
        QMessageBox::critical(m_creator, "错误", "请求超时！");
    }
}


void WebServiceMonitor::handleNetworkReply() {
    timeoutTimer->stop();

    if (currentReply->error() == QNetworkReply::NoError) {
         // 解析JSON响应
        QByteArray responseData = currentReply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = document.object();

        // 检查响应状态
        int code = jsonObject["error_code"].toInt();
        if (code == 0) {
            QMessageBox::information(m_creator, "警报", "已向手机发送短信！");
        } else {
            QMessageBox::critical(m_creator, "错误", "短信发送失败，错误码："+ QString::number(code) + '\n' + "错误信息："+\
                QUrl::fromPercentEncoding(jsonObject["reason"].toString().toUtf8()));
            }
    }
    currentReply->deleteLater();
}



int WebServiceMonitor::loadConfiguration() {
    QSettings settings("config.ini", QSettings::IniFormat);
    phoneNumber = settings.value("PhoneNumber").toString();
    QString logFilePath = settings.value("LogConfigPath").toString();
    appcode = settings.value("AppCode").toString();
    email = settings.value("EmailAddress").toString();

    logFile = new QFile(logFilePath+"/monitor.log");
    if (!logFile->open(QIODevice::ReadWrite)) {
        delete logFile;
        logFile = nullptr;
        qDebug() << "日志无法打开！请检查配置。";
        return 0;
    }
    else
        return 1;
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


void Dialog_function::on_btn_start_clicked()
{
    WebServiceMonitor *webservicemonitor = new WebServiceMonitor(this);

    if (webservicemonitor->loadConfiguration() != 1) {
        QMessageBox::warning(this, "Configuration Error", "Unable to load configuration.");
        delete webservicemonitor;
        webservicemonitor = nullptr;
        return;
    }
    webservicemonitor->run();
}

