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



void Dialog_function::on_pushButton_clicked()
{
    emit closeButtonClicked();

    this->close();
}

