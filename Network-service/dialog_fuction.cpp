#include "dialog_fuction.h"
#include "ui_dialog_fuction.h"

Dialog_fuction::Dialog_fuction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fuction)
{
    ui->setupUi(this);
}

Dialog_fuction::~Dialog_fuction()
{
    delete ui;
}
