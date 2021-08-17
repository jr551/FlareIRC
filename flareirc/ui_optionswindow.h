/********************************************************************************
** Form generated from reading UI file 'optionswindow.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWINDOW_H
#define UI_OPTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabOptions;
    QWidget *tbGeneral;
    QLineEdit *txtDefaultNick;
    QLabel *label;
    QLineEdit *txtFullName;
    QLabel *label_2;
    QCheckBox *chkInformChatClose;
    QLineEdit *txtPartMessage;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *txtQuitMessage;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkNotifyPrivMsg;
    QCheckBox *chkNotifyChannelMsg;
    QCheckBox *chkSoundChannelMsg;
    QCheckBox *chkSoundPrivMsg;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkUseIdent;
    QGroupBox *grpIdent;
    QLineEdit *txtIdentUsername;
    QLineEdit *txtIdentPassword;
    QLabel *label_6;
    QLabel *label_7;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSave;
    QPushButton *btnCancel;

    void setupUi(QMainWindow *OptionsWindow)
    {
        if (OptionsWindow->objectName().isEmpty())
            OptionsWindow->setObjectName(QString::fromUtf8("OptionsWindow"));
        OptionsWindow->resize(366, 288);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OptionsWindow->sizePolicy().hasHeightForWidth());
        OptionsWindow->setSizePolicy(sizePolicy);
        OptionsWindow->setMinimumSize(QSize(366, 288));
        OptionsWindow->setMaximumSize(QSize(366, 288));
        centralwidget = new QWidget(OptionsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabOptions = new QTabWidget(centralwidget);
        tabOptions->setObjectName(QString::fromUtf8("tabOptions"));
        tbGeneral = new QWidget();
        tbGeneral->setObjectName(QString::fromUtf8("tbGeneral"));
        txtDefaultNick = new QLineEdit(tbGeneral);
        txtDefaultNick->setObjectName(QString::fromUtf8("txtDefaultNick"));
        txtDefaultNick->setGeometry(QRect(110, 20, 221, 22));
        label = new QLabel(tbGeneral);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 91, 20));
        txtFullName = new QLineEdit(tbGeneral);
        txtFullName->setObjectName(QString::fromUtf8("txtFullName"));
        txtFullName->setGeometry(QRect(110, 50, 221, 22));
        label_2 = new QLabel(tbGeneral);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 50, 81, 17));
        chkInformChatClose = new QCheckBox(tbGeneral);
        chkInformChatClose->setObjectName(QString::fromUtf8("chkInformChatClose"));
        chkInformChatClose->setGeometry(QRect(70, 160, 211, 21));
        txtPartMessage = new QLineEdit(tbGeneral);
        txtPartMessage->setObjectName(QString::fromUtf8("txtPartMessage"));
        txtPartMessage->setGeometry(QRect(110, 110, 221, 22));
        label_3 = new QLabel(tbGeneral);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 110, 91, 20));
        label_4 = new QLabel(tbGeneral);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 80, 91, 20));
        txtQuitMessage = new QLineEdit(tbGeneral);
        txtQuitMessage->setObjectName(QString::fromUtf8("txtQuitMessage"));
        txtQuitMessage->setGeometry(QRect(110, 80, 221, 22));
        tabOptions->addTab(tbGeneral, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chkNotifyPrivMsg = new QCheckBox(tab_2);
        chkNotifyPrivMsg->setObjectName(QString::fromUtf8("chkNotifyPrivMsg"));

        verticalLayout_2->addWidget(chkNotifyPrivMsg);

        chkNotifyChannelMsg = new QCheckBox(tab_2);
        chkNotifyChannelMsg->setObjectName(QString::fromUtf8("chkNotifyChannelMsg"));

        verticalLayout_2->addWidget(chkNotifyChannelMsg);

        chkSoundChannelMsg = new QCheckBox(tab_2);
        chkSoundChannelMsg->setObjectName(QString::fromUtf8("chkSoundChannelMsg"));

        verticalLayout_2->addWidget(chkSoundChannelMsg);

        chkSoundPrivMsg = new QCheckBox(tab_2);
        chkSoundPrivMsg->setObjectName(QString::fromUtf8("chkSoundPrivMsg"));

        verticalLayout_2->addWidget(chkSoundPrivMsg);

        tabOptions->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        chkUseIdent = new QCheckBox(tab);
        chkUseIdent->setObjectName(QString::fromUtf8("chkUseIdent"));

        verticalLayout_3->addWidget(chkUseIdent);

        grpIdent = new QGroupBox(tab);
        grpIdent->setObjectName(QString::fromUtf8("grpIdent"));
        txtIdentUsername = new QLineEdit(grpIdent);
        txtIdentUsername->setObjectName(QString::fromUtf8("txtIdentUsername"));
        txtIdentUsername->setGeometry(QRect(80, 30, 221, 20));
        txtIdentUsername->setMaxLength(32);
        txtIdentUsername->setEchoMode(QLineEdit::Normal);
        txtIdentPassword = new QLineEdit(grpIdent);
        txtIdentPassword->setObjectName(QString::fromUtf8("txtIdentPassword"));
        txtIdentPassword->setGeometry(QRect(80, 60, 221, 20));
        txtIdentPassword->setMaxLength(32);
        txtIdentPassword->setEchoMode(QLineEdit::Password);
        label_6 = new QLabel(grpIdent);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 30, 51, 16));
        label_7 = new QLabel(grpIdent);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 60, 51, 16));

        verticalLayout_3->addWidget(grpIdent);

        tabOptions->addTab(tab, QString());

        verticalLayout->addWidget(tabOptions);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSave = new QPushButton(frame);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setDefault(true);

        horizontalLayout->addWidget(btnSave);

        btnCancel = new QPushButton(frame);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addWidget(frame);

        OptionsWindow->setCentralWidget(centralwidget);

        retranslateUi(OptionsWindow);

        tabOptions->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OptionsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OptionsWindow)
    {
        OptionsWindow->setWindowTitle(QApplication::translate("OptionsWindow", "FlareIRC - Options", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OptionsWindow", "Default Nick:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OptionsWindow", "Full Name:", 0, QApplication::UnicodeUTF8));
        chkInformChatClose->setText(QApplication::translate("OptionsWindow", "Inform other user when chat tab closed.", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("OptionsWindow", "Part Message:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("OptionsWindow", "Quit Message:", 0, QApplication::UnicodeUTF8));
        tabOptions->setTabText(tabOptions->indexOf(tbGeneral), QApplication::translate("OptionsWindow", "General", 0, QApplication::UnicodeUTF8));
        chkNotifyPrivMsg->setText(QApplication::translate("OptionsWindow", "Show tray icon notifications for private messages", 0, QApplication::UnicodeUTF8));
        chkNotifyChannelMsg->setText(QApplication::translate("OptionsWindow", "Show tray icon notifications for channel messages", 0, QApplication::UnicodeUTF8));
        chkSoundChannelMsg->setText(QApplication::translate("OptionsWindow", "Play sound on new channel message", 0, QApplication::UnicodeUTF8));
        chkSoundPrivMsg->setText(QApplication::translate("OptionsWindow", "Play sound on new private message", 0, QApplication::UnicodeUTF8));
        tabOptions->setTabText(tabOptions->indexOf(tab_2), QApplication::translate("OptionsWindow", "Notifications", 0, QApplication::UnicodeUTF8));
        chkUseIdent->setText(QApplication::translate("OptionsWindow", "Send AuthServ / NickServ Identification", 0, QApplication::UnicodeUTF8));
        grpIdent->setTitle(QApplication::translate("OptionsWindow", "Identification Details", 0, QApplication::UnicodeUTF8));
        txtIdentPassword->setInputMask(QString());
        txtIdentPassword->setText(QString());
        label_6->setText(QApplication::translate("OptionsWindow", "Username:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("OptionsWindow", "Password:", 0, QApplication::UnicodeUTF8));
        tabOptions->setTabText(tabOptions->indexOf(tab), QApplication::translate("OptionsWindow", "Nickname Identification", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("OptionsWindow", "Save", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("OptionsWindow", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsWindow: public Ui_OptionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWINDOW_H
