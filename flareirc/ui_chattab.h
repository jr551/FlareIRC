/********************************************************************************
** Form generated from reading UI file 'chattab.ui'
**
** Created: Sat 16. Jan 16:44:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATTAB_H
#define UI_CHATTAB_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatTab
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QTextEdit *txtMessages;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeUsers;
    QLabel *lblUserCount;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtChat;
    QComboBox *cmbOptions;

    void setupUi(QWidget *ChatTab)
    {
        if (ChatTab->objectName().isEmpty())
            ChatTab->setObjectName(QString::fromUtf8("ChatTab"));
        ChatTab->resize(537, 291);
        ChatTab->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(ChatTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(ChatTab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setContextMenuPolicy(Qt::NoContextMenu);
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
        txtMessages->setContextMenuPolicy(Qt::DefaultContextMenu);
        txtMessages->setReadOnly(true);

        horizontalLayout->addWidget(txtMessages);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeUsers = new QTreeWidget(frame_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeUsers->setHeaderItem(__qtreewidgetitem);
        treeUsers->setObjectName(QString::fromUtf8("treeUsers"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeUsers->sizePolicy().hasHeightForWidth());
        treeUsers->setSizePolicy(sizePolicy1);
        treeUsers->setMaximumSize(QSize(150, 16777215));
        treeUsers->setContextMenuPolicy(Qt::CustomContextMenu);
        treeUsers->setAutoScroll(false);
        treeUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeUsers->setProperty("showDropIndicator", QVariant(false));
        treeUsers->setAlternatingRowColors(true);
        treeUsers->setIndentation(5);
        treeUsers->setRootIsDecorated(true);
        treeUsers->header()->setVisible(false);

        verticalLayout_2->addWidget(treeUsers);

        lblUserCount = new QLabel(frame_2);
        lblUserCount->setObjectName(QString::fromUtf8("lblUserCount"));
        lblUserCount->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lblUserCount);


        horizontalLayout->addWidget(frame_2);


        verticalLayout->addWidget(frame);

        frame_3 = new QFrame(ChatTab);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        txtChat = new QLineEdit(frame_3);
        txtChat->setObjectName(QString::fromUtf8("txtChat"));
        txtChat->setMaxLength(512);

        horizontalLayout_2->addWidget(txtChat);

        cmbOptions = new QComboBox(frame_3);
        cmbOptions->setObjectName(QString::fromUtf8("cmbOptions"));

        horizontalLayout_2->addWidget(cmbOptions);


        verticalLayout->addWidget(frame_3);


        retranslateUi(ChatTab);

        QMetaObject::connectSlotsByName(ChatTab);
    } // setupUi

    void retranslateUi(QWidget *ChatTab)
    {
        ChatTab->setWindowTitle(QApplication::translate("ChatTab", "Form", 0, QApplication::UnicodeUTF8));
        lblUserCount->setText(QApplication::translate("ChatTab", "? Users", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChatTab: public Ui_ChatTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATTAB_H
