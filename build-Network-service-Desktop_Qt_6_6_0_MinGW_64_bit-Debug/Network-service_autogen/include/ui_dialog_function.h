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
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_function
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_function)
    {
        if (Dialog_function->objectName().isEmpty())
            Dialog_function->setObjectName("Dialog_function");
        Dialog_function->resize(542, 404);
        gridLayout = new QGridLayout(Dialog_function);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(Dialog_function);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(28);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton = new QPushButton(Dialog_function);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        retranslateUi(Dialog_function);

        QMetaObject::connectSlotsByName(Dialog_function);
    } // setupUi

    void retranslateUi(QDialog *Dialog_function)
    {
        Dialog_function->setWindowTitle(QCoreApplication::translate("Dialog_function", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog_function", "\345\212\237\350\203\275\347\225\214\351\235\242", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog_function", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_function: public Ui_Dialog_function {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FUNCTION_H
