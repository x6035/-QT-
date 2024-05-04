#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::init()
{
    ui->stackedWidget->setCurrentIndex(0);
    //读取根目录下的ini文件
    m_settings = new QSettings("config.ini", QSettings::IniFormat);
    initConfig();
    for (int i=0;i<3;i++)
    {
        monitor_timer[i] = new QTimer;
    }
  ////////
    connect(monitor_timer[0],&QTimer::timeout,this,[this]() {
        startThread(0);
    });
  ////////
    connect(monitor_timer[1],&QTimer::timeout,this,[this]() {
        startThread(1);
    });
  ////////
    connect(monitor_timer[2],&QTimer::timeout,this,[this]() {
        startThread(2);
    });

    loghistory = new LogHistory(this,"");
    Create_Logdatabase();

}

void MainWindow::startThread(int i)
{

    if (!monitor[i]->isRunning())
    {
        monitor[i]->start();
    }
}

void MainWindow::initConfig()
{
//    ui->edit_databasepath->setText(m_settings->value("DatabasePath").toString());
    ui->edit_mail->setText(m_settings->value("ReceiveEmailAddress").toString());
    ui->edit_phone->setText(m_settings->value("PhoneNumber").toString());
    ui->CB_mail->setCheckState(m_settings->value("EmailAddressEnable").toBool()?Qt::Checked:Qt::Unchecked);
    ui->CB_phone->setCheckState(m_settings->value("PhoneNumberEnable").toBool()?Qt::Checked:Qt::Unchecked);
    ui->edit_appcode->setText(m_settings->value("AppCode").toString());
    ui->edit_mail_send->setText(m_settings->value("SendEmailAddress").toString());
    ui->edit_sendmail_pwd->setText(m_settings->value("SendEmailPwd").toString());

    setWidgetEnable(true,0);
    setWidgetEnable(true,1);
    setWidgetEnable(true,2);

}

bool MainWindow::saveConfig()
{
    // 创建一个正则表达式来验证邮箱地址
    QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    QRegularExpression phoneRegex("^1[3456789]\\d{9}$");

    if(!(ui->CB_mail->isChecked() or ui->CB_phone->isChecked())){
        QMessageBox::critical(this, "错误", "请至少选择一种警报方式！");
        return false;

    }
    if(ui->CB_mail->isChecked()){
        if(!emailRegex.match(ui->edit_mail->text()).hasMatch()){
            QMessageBox::critical(this, "错误", "邮箱有误！");
            return false;
        }
    }
    if(ui->CB_phone->isChecked()){
        if(!phoneRegex.match(ui->edit_phone->text()).hasMatch()){
            QMessageBox::critical(this, "错误", "手机号有误！");
            return false;
        }
    }

    if(ui->edit_phone->text().isEmpty()){
        QMessageBox::critical(this, "错误", "AppCode为空！");
    }

//    QString configPath = ui->edit_databasepath->text();
//    if (configPath.isEmpty() || !QDir(configPath).exists()) {
//        QMessageBox::critical(this, "错误", "数据库路径无效，请输入有效路径！");
//        return false;
//    }

//    m_settings->setValue("DatabasePath", ui->edit_databasepath->text());
    m_settings->setValue("PhoneNumber", ui->edit_phone->text());
    m_settings->setValue("ReceiveEmailAddress", ui->edit_mail->text());
    m_settings->setValue("PhoneNumberEnable", ui->CB_phone->checkState());
    m_settings->setValue("EmailAddressEnable", ui->CB_mail->checkState());
    m_settings->setValue("AppCode", ui->edit_appcode->text());
    m_settings->setValue("SendEmailAddress", ui->edit_mail_send->text());
    m_settings->setValue("SendEmailPwd", ui->edit_sendmail_pwd->text());
    m_settings->sync();

    QMessageBox::information(this, "提示", "配置保存成功！");

    ui->stackedWidget->setCurrentIndex(1);

    return true;
}

void MainWindow::setWidgetEnable(bool flag,int which_monitor)
{
    ui->confBtn->setEnabled(flag);
    ui->btn_back->setEnabled(flag);
    switch (which_monitor) {
    case 0:
        ui->end_task1->setEnabled(!flag);
        break;
    case 1:
        ui->end_task2->setEnabled(!flag);
        break;
    case 2:
        ui->end_task3->setEnabled(!flag);
        break;
}

}


void MainWindow::on_btn_enter_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_confBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    initConfig();
}


void MainWindow::on_btn_saveconfig_clicked()
{
    if(saveConfig()) {
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_btn_CancelConfig_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    initConfig();
}


void MainWindow::on_btn_close_clicked()
{
    close();
}


//void MainWindow::on_pushButton_clicked()
//{
//    // 打开文件对话框
//    QString filePath = QFileDialog::getExistingDirectory(nullptr, "选择数据库存放的路径", QDir::homePath());
//    // 在此处可以对选择的文件路径进行处理
//    if (!filePath.isEmpty()) {
//        qDebug() << "选择的路径为:" << filePath;
//    }
//    ui->edit_databasepath->setText(filePath);
//}


void MainWindow::on_CB_mail_stateChanged()
{
    ui->edit_mail->setEnabled(ui->CB_mail->isChecked());
    ui->edit_mail_send->setEnabled(ui->CB_mail->isChecked());
    ui->edit_sendmail_pwd->setEnabled(ui->CB_mail->isChecked());
}


void MainWindow::on_CB_phone_stateChanged()
{
    ui->edit_phone->setEnabled(ui->CB_phone->isChecked());
    ui->edit_appcode->setEnabled(ui->CB_phone->isChecked());
}


void MainWindow::on_btn_new_task_clicked()
{
    if(ui->edit_ip->text().isEmpty()||ui->edit_port->text().isEmpty()) {
        QMessageBox::critical(this, "错误", "ip或端口不得为空");
        return;
    }

    int i = 0;
    for (;i<3;)
    {
        if (monitor_check[i] == 0)
        {
            monitor[i] = new ServiceMonitor(this,ui->comboBox->currentIndex(),
                                            ui->edit_ip->text(),
                                            ui->edit_port->text(),
                                            i,
                                            ui->CB_mail->isEnabled(),
                                            ui->CB_phone->isEnabled());
            switch (i) {
            case 0:
                ui->task1_disp->setText("");
                break;
            case 1:
                ui->task2_disp->setText("");
                break;
            case 2:
                ui->task3_disp->setText("");
                break;
            }

            connect(monitor[i], SIGNAL(send_data(QString)), this, SLOT(log_display_updata(QString)));
            connect(monitor[i], SIGNAL(SendNotification(QString,int)),
                    this, SLOT(displayNotification(QString,int)), Qt::QueuedConnection);
            switch (i) {
            case 0:
                connect(monitor[i], SIGNAL(end_monitor()), this, SLOT(on_end_task1_clicked()));
                break;
            case 1:
                connect(monitor[i], SIGNAL(end_monitor()), this, SLOT(on_end_task2_clicked()));
                break;
            case 2:
                connect(monitor[i], SIGNAL(end_monitor()), this, SLOT(on_end_task3_clicked()));
                break;
            }

            monitor_timer[i]->start(5000); //5s监视一次，给网络预留时间
            setWidgetEnable(false,i);
            monitor_check[i] = 1;
            break;
        }
        else
        {
            i++;
        }

        if(i == 3)
        {
            QMessageBox::critical(this, "错误", "任务列表已满！");
        }
    }

}


void MainWindow::on_end_task1_clicked()
{
    setWidgetEnable(true,0);
    monitor_check[0] = 0;
    monitor_timer[0]->stop();
}


void MainWindow::on_end_task2_clicked()
{
    setWidgetEnable(true,1);
    monitor_check[1] = 0;
    monitor_timer[1]->stop();
}


void MainWindow::on_end_task3_clicked()
{
    setWidgetEnable(true,2);
    monitor_check[2] = 0;
    monitor_timer[2]->stop();
}

void MainWindow::log_display_updata(QString data)
{
    int id = data.mid(0, 1).toInt();
    switch (id) {
    case 0:
        ui->task1_disp->append(data.mid(2,-1));
        break;
    case 1:
        ui->task2_disp->append(data.mid(2,-1));
        break;
    case 2:
        ui->task3_disp->append(data.mid(2,-1));
        break;
    }
    updata_database(data);

}

void MainWindow::displayNotification(QString message,int typ){
    //typ:1=info,0=critical
    if(typ)
        QMessageBox::information(this,"警报",message);
    else
        QMessageBox::critical(this, "错误", message);
}

//数据库初始化
void MainWindow::Create_Logdatabase()
{
    QString dbPath = "LogHistory.db"; // 数据库文件名

    // 检查数据库是否存在
    if (!QFile::exists(dbPath)) {
        // 创建数据库
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);
        if (!db.open()) {
            qDebug() << "Error creating database:" << db.lastError();
            return;
        }

        // 创建表
        QSqlQuery query(db);
        bool res = query.exec("CREATE TABLE records (time DATETIME PRIMARY KEY, ip_address TEXT, status TEXT)");
        if (!res) {
            qDebug() << "Error creating table:" << query.lastError();
            return;
        }

        db.close(); // 关闭数据库
    }
}

void MainWindow::updata_database(QString data)
{
    QString dbPath = "LogHistory.db"; // 数据库文件名

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);  // 使用内存数据库，你可以改为你的数据库文件路径

    if (!db.open()) {
        qDebug() << "无法打开数据库";
    }
    QSqlQuery query(db);

    // 插入数据
    QStringList parts = data.split("  ");  // 去掉大括号并分割数据
    query.prepare("INSERT INTO records (time, ip_address, status) VALUES (?, ?, ?)");
    query.addBindValue(parts[1]);
    query.addBindValue(parts[2]);
    query.addBindValue(parts[3]);
    bool flag_insert = query.exec();

    // Check if the query execution was successful
    if (!flag_insert) {
        qDebug() << "Error inserting data into table:" << query.lastError();
        return;
    }

    db.close(); // Close the database connection
}

//读取数据库
void MainWindow::on_btn_openlog_clicked()
{
    QString dbPath = "LogHistory.db"; // 数据库文件名

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);  // 数据库文件路径

    if (!db.open()) {
        qDebug() << "无法打开数据库";
    }


    QSqlQuery query(db);
    query.exec("SELECT * FROM records");


    QString res_data = "";
    while (query.next()) {
        QString timestamp = query.value(0).toString();
        QString ip_address = query.value(1).toString();
        QString status = query.value(2).toString();

        QString output = QString("%1  %2  %3")
                             .arg(timestamp)
                             .arg(ip_address)
                             .arg(status);
        res_data = res_data.append(output+"\n");

    }
    db.close();
    loghistory = new LogHistory(this,res_data);
    loghistory->show();
}

