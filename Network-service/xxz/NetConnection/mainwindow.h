#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_function.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_enter_clicked();

    void on_btn_close_clicked();

    void showMainWindow(); // 显示主窗口


private:
    Ui::MainWindow *ui;
    Dialog_function dialog_func;
};
#endif // MAINWINDOW_H
