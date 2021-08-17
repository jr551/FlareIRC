/********************************************************************************
** Form generated from reading UI file 'privatemessagetab.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATEMESSAGETAB_H
#define UI_PRIVATEMESSAGETAB_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QScrollArea>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrivateMessageTab
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblInfo;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QTextEdit *txtMessages;
    QLineEdit *txtChat;

    void setupUi(QWidget *PrivateMessageTab)
    {
        if (PrivateMessageTab->objectName().isEmpty())
            PrivateMessageTab->setObjectName(QString::fromUtf8("PrivateMessageTab"));
        PrivateMessageTab->resize(400, 300);
        verticalLayout = new QVBoxLayout(PrivateMessageTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(PrivateMessageTab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMaximumSize(QSize(16777215, 22));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 20));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lblInfo = new QLabel(scrollAreaWidgetContents);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));
        QFont font;
        font.setPointSize(10);
        lblInfo->setFont(font);
        lblInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(lblInfo);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        frame = new QFrame(PrivateMessageTab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtMessages = new QTextEdit(frame);
        txtMessages->setObjectName(QString::fromUtf8("txtMessages"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtMessages->sizePolicy().hasHeightForWidth());
        txtMessages->setSizePolicy(sizePolicy);
        txtMessages->setReadOnly(true);

        horizontalLayout->addWidget(txtMessages);


        verticalLayout->addWidget(frame);

        txtChat = new QLineEdit(PrivateMessageTab);
        txtChat->setObjectName(QString::fromUtf8("txtChat"));

        verticalLayout->addWidget(txtChat);


        retranslateUi(PrivateMessageTab);

        QMetaObject::connectSlotsByName(PrivateMessageTab);
    } // setupUi

    void retranslateUi(QWidget *PrivateMessageTab)
    {
        PrivateMessageTab->setWindowTitle(QApplication::translate("PrivateMessageTab", "Form", 0, QApplication::UnicodeUTF8));
        lblInfo->setText(QApplication::translate("PrivateMessageTab", "Retrieving User Info...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrivateMessageTab: public Ui_PrivateMessageTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATEMESSAGETAB_H
