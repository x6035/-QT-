#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&dialog_func, &Dialog_function::closeButtonClicked, this, &MainWindow::showMainWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_enter_clicked()
{

    dialog_func.show();
    this->hide();
}

void MainWindow::showMainWindow()
{
    // 显示主窗口并关闭 dialog_function 界面
    dialog_func.close();
    this->show();
}


void MainWindow::on_btn_close_clicked()
{
    exit(1);
}

