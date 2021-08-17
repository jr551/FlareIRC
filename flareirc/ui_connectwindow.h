/********************************************************************************
** Form generated from reading UI file 'connectwindow.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTWINDOW_H
#define UI_CONNECTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QSpinBox *spnPort;
    QLabel *lblPort;
    QLabel *lblServer;
    QLabel *lblChannel;
    QLabel *lblNick;
    QLineEdit *txtServer;
    QLineEdit *txtNick;
    QLineEdit *txtChannels;
    QPushButton *btnConnect;
    QPushButton *btnCancel;
    QPushButton *btnOptions;

    void setupUi(QMainWindow *ConnectWindow)
    {
        if (ConnectWindow->objectName().isEmpty())
            ConnectWindow->setObjectName(QString::fromUtf8("ConnectWindow"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConnectWindow->sizePolicy().hasHeightForWidth());
        ConnectWindow->setSizePolicy(sizePolicy);
        ConnectWindow->setMinimumSize(QSize(364, 235));
        ConnectWindow->setMaximumSize(QSize(364, 235));
        centralWidget = new QWidget(ConnectWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 341, 161));
        spnPort = new QSpinBox(groupBox);
        spnPort->setObjectName(QString::fromUtf8("spnPort"));
        spnPort->setGeometry(QRect(120, 60, 71, 22));
        spnPort->setMaximum(65535);
        spnPort->setValue(6667);
        lblPort = new QLabel(groupBox);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        lblPort->setGeometry(QRect(80, 60, 46, 13));
        lblServer = new QLabel(groupBox);
        lblServer->setObjectName(QString::fromUtf8("lblServer"));
        lblServer->setGeometry(QRect(70, 30, 46, 13));
        lblChannel = new QLabel(groupBox);
        lblChannel->setObjectName(QString::fromUtf8("lblChannel"));
        lblChannel->setGeometry(QRect(10, 120, 101, 20));
        lblNick = new QLabel(groupBox);
        lblNick->setObjectName(QString::fromUtf8("lblNick"));
        lblNick->setGeometry(QRect(80, 90, 46, 13));
        txtServer = new QLineEdit(groupBox);
        txtServer->setObjectName(QString::fromUtf8("txtServer"));
        txtServer->setGeometry(QRect(120, 30, 171, 20));
        txtNick = new QLineEdit(groupBox);
        txtNick->setObjectName(QString::fromUtf8("txtNick"));
        txtNick->setGeometry(QRect(120, 90, 113, 20));
        txtChannels = new QLineEdit(groupBox);
        txtChannels->setObjectName(QString::fromUtf8("txtChannels"));
        txtChannels->setGeometry(QRect(120, 120, 211, 20));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(90, 200, 75, 21));
        btnConnect->setDefault(true);
        btnCancel = new QPushButton(centralWidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(270, 200, 75, 21));
        btnOptions = new QPushButton(centralWidget);
        btnOptions->setObjectName(QString::fromUtf8("btnOptions"));
        btnOptions->setGeometry(QRect(180, 200, 81, 21));
        ConnectWindow->setCentralWidget(centralWidget);

        retranslateUi(ConnectWindow);

        QMetaObject::connectSlotsByName(ConnectWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectWindow)
    {
        ConnectWindow->setWindowTitle(QApplication::translate("ConnectWindow", "FlareIRC - New Connection", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ConnectWindow", "Connection Details", 0, QApplication::UnicodeUTF8));
        lblPort->setText(QApplication::translate("ConnectWindow", "Port:", 0, QApplication::UnicodeUTF8));
        lblServer->setText(QApplication::translate("ConnectWindow", "Server:", 0, QApplication::UnicodeUTF8));
        lblChannel->setText(QApplication::translate("ConnectWindow", "Join Channel(s):", 0, QApplication::UnicodeUTF8));
        lblNick->setText(QApplication::translate("ConnectWindow", "Nick:", 0, QApplication::UnicodeUTF8));
        txtServer->setText(QApplication::translate("ConnectWindow", "-", 0, QApplication::UnicodeUTF8));
        txtNick->setText(QApplication::translate("ConnectWindow", "-", 0, QApplication::UnicodeUTF8));
        txtChannels->setText(QApplication::translate("ConnectWindow", "-", 0, QApplication::UnicodeUTF8));
        btnConnect->setText(QApplication::translate("ConnectWindow", "Connect", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("ConnectWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        btnOptions->setText(QApplication::translate("ConnectWindow", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectWindow: public Ui_ConnectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTWINDOW_H
