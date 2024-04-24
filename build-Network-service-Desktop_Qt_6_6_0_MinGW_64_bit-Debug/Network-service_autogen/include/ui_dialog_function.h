/********************************************************************************
** Form generated from reading UI file 'dialog_function.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FUNCTION_H
#define UI_DIALOG_FUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_function
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn_config;
    QSpacerItem *verticalSpacer;
    QComboBox *comboBox;
    QPushButton *btn_back;
    QScrollArea *log_res;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edit_ip;
    QLineEdit *edit_port;
    QPushButton *btn_start;
    QLabel *label;

    void setupUi(QDialog *Dialog_function)
    {
        if (Dialog_function->objectName().isEmpty())
            Dialog_function->setObjectName("Dialog_function");
        Dialog_function->resize(542, 404);
        gridLayout = new QGridLayout(Dialog_function);
        gridLayout->setObjectName("gridLayout");
        btn_config = new QPushButton(Dialog_function);
        btn_config->setObjectName("btn_config");

        gridLayout->addWidget(btn_config, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        comboBox = new QComboBox(Dialog_function);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        btn_back = new QPushButton(Dialog_function);
        btn_back->setObjectName("btn_back");

        gridLayout->addWidget(btn_back, 6, 0, 1, 2);

        log_res = new QScrollArea(Dialog_function);
        log_res->setObjectName("log_res");
        log_res->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 522, 101));
        log_res->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(log_res, 5, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        edit_ip = new QLineEdit(Dialog_function);
        edit_ip->setObjectName("edit_ip");

        horizontalLayout->addWidget(edit_ip);

        edit_port = new QLineEdit(Dialog_function);
        edit_port->setObjectName("edit_port");

        horizontalLayout->addWidget(edit_port);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 2);

        btn_start = new QPushButton(Dialog_function);
        btn_start->setObjectName("btn_start");

        gridLayout->addWidget(btn_start, 3, 0, 1, 2);

        label = new QLabel(Dialog_function);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(28);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 2);


        retranslateUi(Dialog_function);

        QMetaObject::connectSlotsByName(Dialog_function);
    } // setupUi

    void retranslateUi(QDialog *Dialog_function)
    {
        Dialog_function->setWindowTitle(QCoreApplication::translate("Dialog_function", "Dialog", nullptr));
        btn_config->setText(QCoreApplication::translate("Dialog_function", "\351\205\215\347\275\256", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Dialog_function", "web", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Dialog_function", "ftp", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Dialog_function", "smtp", nullptr));

        btn_back->setText(QCoreApplication::translate("Dialog_function", "\350\277\224\345\233\236", nullptr));
        edit_ip->setText(QCoreApplication::translate("Dialog_function", "\350\276\223\345\205\245\347\233\256\346\240\207\344\270\273\346\234\272IP", nullptr));
        edit_port->setText(QCoreApplication::translate("Dialog_function", "\350\276\223\345\205\245\347\233\256\346\240\207\346\234\215\345\212\241PORT", nullptr));
        btn_start->setText(QCoreApplication::translate("Dialog_function", "\345\274\200\345\247\213\347\233\221\346\265\213", nullptr));
        label->setText(QCoreApplication::translate("Dialog_function", "\345\212\237\350\203\275\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_function: public Ui_Dialog_function {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FUNCTION_H
