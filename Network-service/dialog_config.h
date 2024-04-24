#ifndef DIALOG_CONFIG_H
#define DIALOG_CONFIG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QRegularExpression>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>

namespace Ui {
class Dialog_config;
}

class Dialog_config : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_config(QWidget *parent = nullptr);
    ~Dialog_config();

private slots:
    void on_CB_mail_stateChanged();

    void on_btn_saveconfig_clicked();

    void on_btn_CancelConfig_clicked();
    void on_CB_phone_stateChanged();

    void on_pushButton_clicked();

private:
    Ui::Dialog_config *ui;
    QString ConfigPath;
    QSettings *settings;

};

#endif // DIALOG_CONFIG_H
