/********************************************************************************
** Form generated from reading UI file 'servertab.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERTAB_H
#define UI_SERVERTAB_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerTab
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QListWidget *lstStatus;
    QWidget *tbMOTD;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *txtMOTD;
    QWidget *tbRaw;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *txtMessages;
    QLabel *label;
    QLineEdit *txtChat;

    void setupUi(QWidget *ServerTab)
    {
        if (ServerTab->objectName().isEmpty())
            ServerTab->setObjectName(QString::fromUtf8("ServerTab"));
        ServerTab->resize(400, 300);
        verticalLayout = new QVBoxLayout(ServerTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(ServerTab);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lstStatus = new QListWidget(tab_3);
        lstStatus->setObjectName(QString::fromUtf8("lstStatus"));

        verticalLayout_3->addWidget(lstStatus);

        tabWidget->addTab(tab_3, QString());
        tbMOTD = new QWidget();
        tbMOTD->setObjectName(QString::fromUtf8("tbMOTD"));
        verticalLayout_4 = new QVBoxLayout(tbMOTD);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        txtMOTD = new QTextEdit(tbMOTD);
        txtMOTD->setObjectName(QString::fromUtf8("txtMOTD"));
        QFont font;
        font.setPointSize(10);
        txtMOTD->setFont(font);
        txtMOTD->setReadOnly(true);

        verticalLayout_4->addWidget(txtMOTD);

        tabWidget->addTab(tbMOTD, QString());
        tbRaw = new QWidget();
        tbRaw->setObjectName(QString::fromUtf8("tbRaw"));
        verticalLayout_2 = new QVBoxLayout(tbRaw);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        txtMessages = new QTextEdit(tbRaw);
        txtMessages->setObjectName(QString::fromUtf8("txtMessages"));
        txtMessages->setFont(font);

        verticalLayout_2->addWidget(txtMessages);

        label = new QLabel(tbRaw);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        txtChat = new QLineEdit(tbRaw);
        txtChat->setObjectName(QString::fromUtf8("txtChat"));

        verticalLayout_2->addWidget(txtChat);

        tabWidget->addTab(tbRaw, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ServerTab);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ServerTab);
    } // setupUi

    void retranslateUi(QWidget *ServerTab)
    {
        ServerTab->setWindowTitle(QApplication::translate("ServerTab", "Form", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ServerTab", "Connection Info", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tbMOTD), QApplication::translate("ServerTab", "Server MOTD", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ServerTab", "Send Raw Command to Server:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tbRaw), QApplication::translate("ServerTab", "Raw Log", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ServerTab: public Ui_ServerTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERTAB_H
