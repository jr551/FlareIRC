/********************************************************************************
** Form generated from reading UI file 'privatechatwindow.ui'
**
** Created: Mon Dec 21 20:25:47 2009
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATECHATWINDOW_H
#define UI_PRIVATECHATWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PrivateChatWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *txtMessages;
    QLineEdit *txtChat;

    void setupUi(QDialog *PrivateChatWindow)
    {
        if (PrivateChatWindow->objectName().isEmpty())
            PrivateChatWindow->setObjectName(QString::fromUtf8("PrivateChatWindow"));
        PrivateChatWindow->resize(381, 281);
        verticalLayout = new QVBoxLayout(PrivateChatWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        txtMessages = new QTextEdit(PrivateChatWindow);
        txtMessages->setObjectName(QString::fromUtf8("txtMessages"));

        verticalLayout->addWidget(txtMessages);

        txtChat = new QLineEdit(PrivateChatWindow);
        txtChat->setObjectName(QString::fromUtf8("txtChat"));

        verticalLayout->addWidget(txtChat);


        retranslateUi(PrivateChatWindow);

        QMetaObject::connectSlotsByName(PrivateChatWindow);
    } // setupUi

    void retranslateUi(QDialog *PrivateChatWindow)
    {
        PrivateChatWindow->setWindowTitle(QApplication::translate("PrivateChatWindow", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrivateChatWindow: public Ui_PrivateChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATECHATWINDOW_H
