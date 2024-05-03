#include "loghistory.h"
#include "ui_loghistory.h"

LogHistory::LogHistory(QWidget *parent,QString data) :
    QDialog(parent),
    ui(new Ui::LogHistory)
{
    ui->setupUi(this);
    ui->display_loghistory->append(data);
}

LogHistory::~LogHistory()
{
    delete ui;
}

void LogHistory::on_btn_back_clicked()
{
    this->close();
}


void LogHistory::on_btn_clear_clicked()
{
    QString dbPath = "LogHistory.db"; // 数据库文件名

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);  // 数据库文件路径

    if (!db.open()) {
        qDebug() << "无法打开数据库";
    }

    QSqlQuery clearQuery(db);
    if (!clearQuery.exec("DELETE FROM records")) {
        qDebug() << "Error clearing table:" << clearQuery.lastError();
        return;
    }

    db.close(); // Close the database connection
    ui->display_loghistory->setText("");
}

