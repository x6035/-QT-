/********************************************************************************
** Form generated from reading UI file 'dialog_config.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CONFIG_H
#define UI_DIALOG_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Dialog_config
{
public:
    QGridLayout *gridLayout;
    QCheckBox *CB_phone;
    QPushButton *pushButton;
    QLineEdit *edit_mail;
    QLabel *label;
    QLineEdit *edit_phone;
    QLabel *label_2;
    QCheckBox *CB_mail;
    QLineEdit *edit_configpath;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_saveconfig;
    QPushButton *btn_CancelConfig;

    void setupUi(QDialog *Dialog_config)
    {
        if (Dialog_config->objectName().isEmpty())
            Dialog_config->setObjectName("Dialog_config");
        Dialog_config->resize(601, 364);
        gridLayout = new QGridLayout(Dialog_config);
        gridLayout->setObjectName("gridLayout");
        CB_phone = new QCheckBox(Dialog_config);
        CB_phone->setObjectName("CB_phone");
        CB_phone->setChecked(true);

        gridLayout->addWidget(CB_phone, 4, 0, 1, 1);

        pushButton = new QPushButton(Dialog_config);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);

        edit_mail = new QLineEdit(Dialog_config);
        edit_mail->setObjectName("edit_mail");

        gridLayout->addWidget(edit_mail, 3, 1, 1, 1);

        label = new QLabel(Dialog_config);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        edit_phone = new QLineEdit(Dialog_config);
        edit_phone->setObjectName("edit_phone");

        gridLayout->addWidget(edit_phone, 4, 1, 1, 1);

        label_2 = new QLabel(Dialog_config);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 3);

        CB_mail = new QCheckBox(Dialog_config);
        CB_mail->setObjectName("CB_mail");
        CB_mail->setChecked(true);

        gridLayout->addWidget(CB_mail, 3, 0, 1, 1);

        edit_configpath = new QLineEdit(Dialog_config);
        edit_configpath->setObjectName("edit_configpath");

        gridLayout->addWidget(edit_configpath, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        btn_saveconfig = new QPushButton(Dialog_config);
        btn_saveconfig->setObjectName("btn_saveconfig");

        gridLayout->addWidget(btn_saveconfig, 7, 0, 1, 1);

        btn_CancelConfig = new QPushButton(Dialog_config);
        btn_CancelConfig->setObjectName("btn_CancelConfig");

        gridLayout->addWidget(btn_CancelConfig, 7, 2, 1, 1);


        retranslateUi(Dialog_config);

        QMetaObject::connectSlotsByName(Dialog_config);
    } // setupUi

    void retranslateUi(QDialog *Dialog_config)
    {
        Dialog_config->setWindowTitle(QCoreApplication::translate("Dialog_config", "Dialog", nullptr));
        CB_phone->setText(QString());
        pushButton->setText(QCoreApplication::translate("Dialog_config", "\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        edit_mail->setText(QString());
        edit_mail->setPlaceholderText(QCoreApplication::translate("Dialog_config", "\345\241\253\345\206\231\351\202\256\347\256\261\345\234\260\345\235\200", nullptr));
        label->setText(QCoreApplication::translate("Dialog_config", "\351\205\215\347\275\256\345\241\253\345\206\231", nullptr));
        edit_phone->setText(QString());
        edit_phone->setPlaceholderText(QCoreApplication::translate("Dialog_config", "\345\241\253\345\206\231\346\211\213\346\234\272\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_config", "\346\263\250\346\204\217\357\274\232\350\257\267\350\207\263\345\260\221\351\200\211\346\213\251\344\270\200\347\247\215\346\212\245\350\255\246\346\226\271\345\274\217", nullptr));
        CB_mail->setText(QString());
        edit_configpath->setText(QString());
        edit_configpath->setPlaceholderText(QCoreApplication::translate("Dialog_config", "\345\241\253\345\206\231\346\210\226\351\200\211\346\213\251\346\227\245\345\277\227\350\267\257\345\276\204", nullptr));
        btn_saveconfig->setText(QCoreApplication::translate("Dialog_config", "\344\277\235\345\255\230", nullptr));
        btn_CancelConfig->setText(QCoreApplication::translate("Dialog_config", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_config: public Ui_Dialog_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CONFIG_H
