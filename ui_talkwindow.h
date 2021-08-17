/********************************************************************************
** Form generated from reading UI file 'talkwindow.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALKWINDOW_H
#define UI_TALKWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TalkWindow
{
public:
    QAction *actionNew_Server_Connection;
    QAction *actionOpen_Options;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionDisconnect;
    QAction *actionJoin_Channel;
    QAction *actionChange_Nick;
    QAction *actionEnable_Logging;
    QAction *actionDisable_Scripting;
    QAction *actionManage_Scripts;
    QAction *actionHj;
    QAction *actionPastebin;
    QAction *actionFile_Upload;
    QAction *actionLogging;
    QAction *actionScripting;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabChats;
    QWidget *tbConnecting;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QMenu *menuHelp;

    void setupUi(QMainWindow *TalkWindow)
    {
        if (TalkWindow->objectName().isEmpty())
            TalkWindow->setObjectName(QString::fromUtf8("TalkWindow"));
        TalkWindow->resize(629, 451);
        actionNew_Server_Connection = new QAction(TalkWindow);
        actionNew_Server_Connection->setObjectName(QString::fromUtf8("actionNew_Server_Connection"));
        actionOpen_Options = new QAction(TalkWindow);
        actionOpen_Options->setObjectName(QString::fromUtf8("actionOpen_Options"));
        actionAbout = new QAction(TalkWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionExit = new QAction(TalkWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionDisconnect = new QAction(TalkWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionJoin_Channel = new QAction(TalkWindow);
        actionJoin_Channel->setObjectName(QString::fromUtf8("actionJoin_Channel"));
        actionChange_Nick = new QAction(TalkWindow);
        actionChange_Nick->setObjectName(QString::fromUtf8("actionChange_Nick"));
        actionEnable_Logging = new QAction(TalkWindow);
        actionEnable_Logging->setObjectName(QString::fromUtf8("actionEnable_Logging"));
        actionDisable_Scripting = new QAction(TalkWindow);
        actionDisable_Scripting->setObjectName(QString::fromUtf8("actionDisable_Scripting"));
        actionManage_Scripts = new QAction(TalkWindow);
        actionManage_Scripts->setObjectName(QString::fromUtf8("actionManage_Scripts"));
        actionHj = new QAction(TalkWindow);
        actionHj->setObjectName(QString::fromUtf8("actionHj"));
        actionPastebin = new QAction(TalkWindow);
        actionPastebin->setObjectName(QString::fromUtf8("actionPastebin"));
        actionFile_Upload = new QAction(TalkWindow);
        actionFile_Upload->setObjectName(QString::fromUtf8("actionFile_Upload"));
        actionLogging = new QAction(TalkWindow);
        actionLogging->setObjectName(QString::fromUtf8("actionLogging"));
        actionScripting = new QAction(TalkWindow);
        actionScripting->setObjectName(QString::fromUtf8("actionScripting"));
        centralwidget = new QWidget(TalkWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabChats = new QTabWidget(centralwidget);
        tabChats->setObjectName(QString::fromUtf8("tabChats"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabChats->sizePolicy().hasHeightForWidth());
        tabChats->setSizePolicy(sizePolicy);
        tabChats->setAutoFillBackground(false);
        tabChats->setTabShape(QTabWidget::Rounded);
        tabChats->setElideMode(Qt::ElideRight);
        tabChats->setDocumentMode(true);
        tabChats->setTabsClosable(true);
        tabChats->setMovable(true);
        tbConnecting = new QWidget();
        tbConnecting->setObjectName(QString::fromUtf8("tbConnecting"));
        horizontalLayout = new QHBoxLayout(tbConnecting);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabChats->addTab(tbConnecting, QString());

        verticalLayout->addWidget(tabChats);

        TalkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TalkWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 629, 21));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        TalkWindow->setMenuBar(menubar);

        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuOptions->addAction(actionOpen_Options);
        menuOptions->addAction(actionNew_Server_Connection);
        menuOptions->addSeparator();
        menuOptions->addAction(actionDisconnect);
        menuOptions->addAction(actionJoin_Channel);
        menuOptions->addAction(actionChange_Nick);
        menuOptions->addSeparator();
        menuOptions->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(TalkWindow);

        tabChats->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TalkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TalkWindow)
    {
        TalkWindow->setWindowTitle(QApplication::translate("TalkWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew_Server_Connection->setText(QApplication::translate("TalkWindow", "New Server Connection", 0, QApplication::UnicodeUTF8));
        actionOpen_Options->setText(QApplication::translate("TalkWindow", "Open Options", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("TalkWindow", "About", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("TalkWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionDisconnect->setText(QApplication::translate("TalkWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        actionJoin_Channel->setText(QApplication::translate("TalkWindow", "Join Channel", 0, QApplication::UnicodeUTF8));
        actionChange_Nick->setText(QApplication::translate("TalkWindow", "Change Nick", 0, QApplication::UnicodeUTF8));
        actionEnable_Logging->setText(QApplication::translate("TalkWindow", "Enable Logging", 0, QApplication::UnicodeUTF8));
        actionDisable_Scripting->setText(QApplication::translate("TalkWindow", "Disable Scripting", 0, QApplication::UnicodeUTF8));
        actionManage_Scripts->setText(QApplication::translate("TalkWindow", "Manage Scripts", 0, QApplication::UnicodeUTF8));
        actionHj->setText(QApplication::translate("TalkWindow", "hj", 0, QApplication::UnicodeUTF8));
        actionPastebin->setText(QApplication::translate("TalkWindow", "Pastebin", 0, QApplication::UnicodeUTF8));
        actionFile_Upload->setText(QApplication::translate("TalkWindow", "File Upload", 0, QApplication::UnicodeUTF8));
        actionLogging->setText(QApplication::translate("TalkWindow", "Logging", 0, QApplication::UnicodeUTF8));
        actionScripting->setText(QApplication::translate("TalkWindow", "Scripting", 0, QApplication::UnicodeUTF8));
        tabChats->setTabText(tabChats->indexOf(tbConnecting), QApplication::translate("TalkWindow", "Connecting...", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("TalkWindow", "Connection", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("TalkWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TalkWindow: public Ui_TalkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALKWINDOW_H
