#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    ScrollContentWidget = new QWidget(ui->scrollArea);
    ScrollContentLayout  = new QVBoxLayout(ScrollContentWidget);
    ui->scrollArea->setWidget(ScrollContentWidget);
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

    loghistory = new LogHistory(this,"");
    Create_Logdatabase();

}

void MainWindow::startThread(int id)
{
    QLinkedList<ServiceMonitor*>::iterator i_monitor = getIteratorAtIndex(monitors,id-1);
    if (!(*i_monitor)->isRunning())
    {
        (*i_monitor)->start();
    }
}

void MainWindow::initConfig()
{
    ui->edit_mail->setText(m_settings->value("ReceiveEmailAddress").toString());
    ui->edit_phone->setText(m_settings->value("PhoneNumber").toString());
    ui->CB_mail->setCheckState(m_settings->value("EmailAddressEnable").toBool()?Qt::Checked:Qt::Unchecked);
    ui->CB_phone->setCheckState(m_settings->value("PhoneNumberEnable").toBool()?Qt::Checked:Qt::Unchecked);
    ui->edit_appcode->setText(m_settings->value("AppCode").toString());
    ui->edit_mail_send->setText(m_settings->value("SendEmailAddress").toString());
    ui->edit_sendmail_pwd->setText(m_settings->value("SendEmailPwd").toString());

//    setWidgetEnable(true);

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
        if(ui->edit_phone->text().isEmpty()){
            QMessageBox::critical(this, "错误", "AppCode为空！");
            return false;
        }
    }


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

void MainWindow::setWidgetEnable(bool flag)
{
    ui->confBtn->setEnabled(flag);
    ui->btn_back->setEnabled(flag);

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
    //创建一个正则表达式验证端口是否正确
    QRegularExpression PortRegex("^(?:0|65536|[1-9]\\d{0,4}|[1-5]\\d{0,4}|6[0-4]\\d{0,3}|65[0-4]\\d{0,2}|655[0-2]\\d{0,1}|6553[0-6])$");
    if(!PortRegex.match(ui->edit_port->text()).hasMatch()){
        QMessageBox::critical(this, "错误", "输入端口有误！");
        return ;
    }

    display_unit_cout++;
    display_label *newLabel = new display_label(this,display_unit_cout);
    end_btn *newBtn = new end_btn(display_unit_cout);
    connect(newBtn,SIGNAL(sendid(int)),this,SLOT(end_task(int)));

    Monitor_Timer *timer = new Monitor_Timer(this,display_unit_cout);
    monitor_timers.append(timer);
    connect(timer,&QTimer::timeout,this,[this, timer]() {
        startThread(timer->id);
    });



    QHBoxLayout *scrollLayout = new QHBoxLayout();
    scrollLayout->addWidget(newLabel);
    scrollLayout->addWidget(newBtn);

    ScrollContentLayout->addLayout(scrollLayout);


    // 将新的QLabel添加到数组中
    display_labels.append(newLabel);
    end_btns.append(newBtn);

    monitors.append(new ServiceMonitor(ui->comboBox->currentIndex(),
                                         ui->edit_ip->text(),
                                         ui->edit_port->text(),
                                         display_unit_cout,
                                         ui->CB_mail->isChecked(),
                                       ui->CB_phone->isChecked()));
    QLinkedList<ServiceMonitor*>::iterator i_monitor = getIteratorAtIndex(monitors,display_unit_cout-1);

    connect(*i_monitor, SIGNAL(send_data(QString,int)), this, SLOT(log_display_updata(QString,int)));

    connect(*i_monitor, SIGNAL(end_monitor()), newBtn, SLOT(on_end_btn_clicked()));
    //暂时不确定id需要

    newLabel->setText("初始化任务中......");

    connect(*i_monitor, SIGNAL(SendNotification(QString,int)),
            this, SLOT(displayNotification(QString,int)), Qt::QueuedConnection);

    (timer)->start(5000); //5s监视一次，给网络预留时间
    setWidgetEnable(false);
    monitor_checks.append(1);


}


//链表遍历模板
template<typename T>
typename QLinkedList<T>::iterator MainWindow::getIteratorAtIndex(QLinkedList<T>& list, int index) {
    typename QLinkedList<T>::iterator it = list.begin();
    for (int i = 0; i < index && it != list.end(); ++i) {
            ++it;
    }
    return it;
}

//链表节点删除后更新id
template<typename NodeType>
void MainWindow::updateNodeIds(QLinkedList<NodeType*>& list, int startId)
{
    for (typename QLinkedList<NodeType*>::iterator it = list.begin(); it != list.end(); ++it)
    {
            if ((*it)->id >= startId)
            {
            (*it)->id = startId--;
            }
    }
}


//改进：设置label 和 按钮 销毁，计时器检查
void MainWindow::end_task(int id)
{

    //id-1 = index
    int index = id -1;
    QLinkedList<int>::iterator i_monitor_check = getIteratorAtIndex(monitor_checks,index);
    i_monitor_check = 0;

    QLinkedList<Monitor_Timer*>::iterator i_monitor_timer = getIteratorAtIndex(monitor_timers,index);

    if (i_monitor_timer != monitor_timers.end()) {
        // 假设元素是指针类型，需要手动删除
        (*i_monitor_timer)->stop();
        delete *i_monitor_timer;
        monitor_timers.erase(i_monitor_timer);
    }
    updateNodeIds(monitor_timers,id);

    //组件销毁，加从链表移除
    //label
    QLinkedList<display_label*>::iterator i_display_label = getIteratorAtIndex(display_labels,index);
    // 从布局中移除小部件
    ui->display_unit->removeWidget(*i_display_label);
    // 销毁小部件
    delete *i_display_label;
    // 从链表中移除
    display_labels.erase(i_display_label);
    updateNodeIds(display_labels,id);

    //btn
    QLinkedList<end_btn*>::iterator i_end_btn = getIteratorAtIndex(end_btns,index);
    // 从布局中移除小部件
    ui->display_unit->removeWidget(*i_end_btn);
    // 销毁小部件
    delete *i_end_btn;
    // 从链表中移除
    end_btns.erase(i_end_btn);
    updateNodeIds(end_btns,id);

    //线程
    QLinkedList<ServiceMonitor*>::iterator i_servicemonitor = getIteratorAtIndex(monitors,index);
    // 销毁小部件
    delete *i_servicemonitor;
    // 从链表中移除
    monitors.erase(i_servicemonitor);

    updateNodeIds(display_labels,id);

    display_unit_cout--;

    if(!display_unit_cout)
        setWidgetEnable(true);
}




void MainWindow::log_display_updata(QString data,int id)
{
    QLinkedList<display_label*>::iterator i_display_label = getIteratorAtIndex(display_labels,id-1);
    if (i_display_label != display_labels.end()) {
        (*i_display_label)->setText(data.mid(2,-1));
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
    QSqlDatabase db = DbConnectionPool::getInstance().getConnection();
    QString dbPath = "LogHistory.db"; // 数据库文件名
    // 检查数据库是否存在
    if (!QFile::exists(dbPath)) {
        // 创建数据库
        db = QSqlDatabase::addDatabase("QSQLITE");
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

        DbConnectionPool::getInstance().releaseConnection(db); // 关闭数据库
    }
}

void MainWindow::updata_database(QString data)
{
    QString dbPath = "LogHistory.db"; // 数据库文件名
    QSqlDatabase db = DbConnectionPool::getInstance().getConnection();
    db.setDatabaseName(dbPath);  // 使用内存数据库

    if (!db.open()) {
        qDebug() << "Cant open database！";
    }
    QSqlQuery query(db);

    // 插入数据
    QStringList parts = data.split("  ");  // 去掉大括号并分割数据
    query.prepare("INSERT INTO records (time, ip_address, status) VALUES (?, ?, ?)");
    query.addBindValue(parts[1]);
    query.addBindValue(parts[2]);
    query.addBindValue(parts[3]);
    bool flag_insert = query.exec();

    if (!flag_insert) {
        qDebug() << "Error inserting data into table:" << query.lastError();
        return;
    }

    DbConnectionPool::getInstance().releaseConnection(db); // 关闭数据库
}

//读取数据库
void MainWindow::on_btn_openlog_clicked()
{
    Create_Logdatabase();
    QSqlDatabase db = DbConnectionPool::getInstance().getConnection();
    QString dbPath = "LogHistory.db"; // 数据库文件名
    db.setDatabaseName(dbPath);  // 数据库文件路径

    if (!db.open()) {
        qDebug() << "Cant open database！";
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
    DbConnectionPool::getInstance().releaseConnection(db);
    loghistory = new LogHistory(this,res_data);
    loghistory->show();
}

template <typename T>
void MainWindow::insertNode(QLinkedList<T>& list, int index, const T& data) {
    if (index < 0 || index > list.size()) {
        return;
    }

    auto it = list.begin();
    std::advance(it, index);
    list.insert(it, data);
}

template <typename T>
void MainWindow::removeNode(QLinkedList<T>& list, int index) {
    if (index < 0 || index >= list.size()) {
        return;
    }

    auto it = list.begin();
    std::advance(it, index);
    list.erase(it);
}

