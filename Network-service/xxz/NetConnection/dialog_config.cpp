#include "dialog_config.h"
#include "ui_dialog_config.h"
#include<QDebug>
Dialog_config::Dialog_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_config)
{
    ui->setupUi(this);
    //保存配置到根目录下的ini文件
    this->settings = new QSettings("config.ini", QSettings::IniFormat);
    ui->edit_configpath->setText(settings->value("ConfigPath").toString());
    ui->edit_mail->setText(settings->value("EmailAddress").toString());
    ui->edit_phone->setText(settings->value("PhoneNumber").toString());
}

Dialog_config::~Dialog_config()
{
    delete ui;
}

//两个下拉框
void Dialog_config::on_CB_mail_stateChanged()
{
    this->ui->edit_mail->setEnabled(ui->CB_mail->isChecked());

}

void Dialog_config::on_CB_phone_stateChanged()
{
    this->ui->edit_phone->setEnabled(ui->CB_phone->isChecked());

}


void Dialog_config::on_btn_saveconfig_clicked()
{
    bool flag_correct = true;
    // 创建一个正则表达式来验证邮箱地址
    QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    QRegularExpression phoneRegex("^1[3456789]\\d{9}$");

    if(!(ui->CB_mail->isChecked() or ui->CB_phone->isChecked())){
//        qDebug()<<"请至少选择一种警报方式！";
        QMessageBox::critical(this, "错误", "请至少选择一种警报方式！");
        flag_correct = false;

    }
    if(ui->CB_mail->isChecked()){
        if(!emailRegex.match(ui->edit_mail->text()).hasMatch()){
//            qDebug()<<"邮箱有误！";
        QMessageBox::critical(this, "错误", "邮箱有误！");
        flag_correct = false;
        }
    }
    if(ui->CB_phone->isChecked()){
        if(!phoneRegex.match(ui->edit_phone->text()).hasMatch()){
//            qDebug()<<"手机号有误！";
        QMessageBox::critical(this, "错误", "手机号有误！");
        flag_correct = false;
        }
    }

    QString configPath = ui->edit_configpath->text();
    if (configPath.isEmpty() || !QDir(configPath).exists()) {
        QMessageBox::critical(this, "错误", "配置路径无效，请输入有效路径！");
        flag_correct = false;
    }

    if(flag_correct){
        this->settings->setValue("ConfigPath", configPath);
        this->settings->setValue("PhoneNumber", ui->edit_phone->text());
        this->settings->setValue("EmailAddress", ui->edit_mail->text());

//        qDebug()<<"配置保存成功！";
        QMessageBox::information(this, "提示", "配置保存成功！");
        this->close();
    }
    else
//        qDebug()<<"配置未保存！";
        QMessageBox::warning(this, "错误", "配置未保存！");
}


void Dialog_config::on_btn_CancelConfig_clicked()
{
    this->close();
}


void Dialog_config::on_pushButton_clicked()
{
        // 打开文件对话框
        QString filePath = QFileDialog::getExistingDirectory(nullptr, "选择配置文件存放的路径", QDir::homePath());
        // 在此处可以对选择的文件路径进行处理
        if (!filePath.isEmpty()) {
            qDebug() << "选择的文件路径为:" << filePath;
        }
        ui->edit_configpath->setText(filePath);
}

