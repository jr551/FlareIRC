/********************************************************************************
** Form generated from reading UI file 'inputdialog.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDIALOG_H
#define UI_INPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputDialog
{
public:
    QPushButton *btnOK;
    QLineEdit *txtInput;
    QLabel *lblMessage;

    void setupUi(QDialog *InputDialog)
    {
        if (InputDialog->objectName().isEmpty())
            InputDialog->setObjectName(QString::fromUtf8("InputDialog"));
        InputDialog->resize(270, 111);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InputDialog->sizePolicy().hasHeightForWidth());
        InputDialog->setSizePolicy(sizePolicy);
        InputDialog->setMinimumSize(QSize(270, 111));
        InputDialog->setMaximumSize(QSize(270, 111));
        btnOK = new QPushButton(InputDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(200, 70, 61, 32));
        btnOK->setDefault(true);
        txtInput = new QLineEdit(InputDialog);
        txtInput->setObjectName(QString::fromUtf8("txtInput"));
        txtInput->setGeometry(QRect(10, 40, 251, 21));
        lblMessage = new QLabel(InputDialog);
        lblMessage->setObjectName(QString::fromUtf8("lblMessage"));
        lblMessage->setGeometry(QRect(10, 10, 251, 17));

        retranslateUi(InputDialog);

        QMetaObject::connectSlotsByName(InputDialog);
    } // setupUi

    void retranslateUi(QDialog *InputDialog)
    {
        InputDialog->setWindowTitle(QApplication::translate("InputDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("InputDialog", "OK", 0, QApplication::UnicodeUTF8));
        lblMessage->setText(QApplication::translate("InputDialog", "-", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InputDialog: public Ui_InputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDIALOG_H
