#ifndef CHATTAB_H
#define CHATTAB_H

#include <QWidget>
#include "talkwindow.h"
#include <QtGui/QApplication>
#include <QStandardItemModel>
#include "talkwindowtab.h"
#include "QTreeWidgetItem"

namespace Ui {
    class ChatTab;
}


class IRCUserItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:

    IRCUserItem( QString usersName, QString startModes )
        : QTreeWidgetItem((QTreeWidget*)0, QStringList(usersName))
    {
        userName = usersName;
        parseMode(startModes);
        setText(0,userName);
    }
    void parseMode( QString modeString )
    {
        if ( modeString.length() > 1 && modeString.at(0) == QChar('+') )
        {
            QString modes = modeString.mid(1);
            for ( int i = 0; i < modes.size(); i++ )
            {
                if ( !userModes.contains( modes.at(i) ) )
                    userModes.append(modes.at(i));
            }
        }
        else if ( modeString.length() > 1 && modeString.at(0) == QChar('-') )
        {
            QString modes = modeString.mid(1);
            for ( int i = 0; i < modes.size(); i++ )
            {
                if ( userModes.contains( modes.at(i) ) )
                    userModes.remove(modes.at(i));
            }

        }
        if ( userModes.length() < 1 )
        {
            QIcon ico(":/icons/voice.png");
            setIcon(0,ico);
        }
        else
        {
            if ( userModes.contains('o'))
            {
                QIcon ico(":/icons/op.png");
                setIcon(0,ico);
            }
            else if ( userModes.contains('v'))
            {
                QIcon ico(":/icons/normal.png");
                setIcon(0,ico);
            }
        }
    }

    bool isOp(){ return userModes.contains('o'); }
    bool isVoiced(){ return userModes.contains('v'); }
    QString getUserModes(){ return userModes; }
    QString getUserName( ){ return userName;}
    void setUserName( QString newUname )
    {
        userName = newUname;
        setText(0,userName);
    }
private:
    QString userModes;
    QString userName;

};

class ChatTab : public TalkWindowTab {
    Q_OBJECT
public:
    ChatTab(QWidget *parent = 0, TalkWindow *pTalkWindow = 0, QString tChannel = tr("null"));
    ~ChatTab();

    void AddChatLine( QString line );
    void AddUser( QString user );
    bool RemoveUser( QString user );
    void EditUser( QString oldUser, QString newUser );
    void ModeUser( QString user, QString modes );


    TalkWindowTabType_t GetTabType() { return CHANNEL_TAB; }
    QString GetTabContext() { return channel; }
    bool UpdateNick( QString oldNick, QString newNick );
    IRCUserItem *GetSelectedUser();
    IRCUserItem *FindUserByUserName( QString userName );
    void RemoveUserFromUserList( IRCUserItem* user );
    void UpdateUserCategory( IRCUserItem *ircUser );
    void LocalNickUpdated(QString nick);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::ChatTab *ui;
    TalkWindow *talkWindow;
    QString channel;
    QTreeWidgetItem *treeOps;
    QTreeWidgetItem *treeVoice;
    QTreeWidgetItem *treeOthers;
    int iUserCount;

private slots:

    void on_cmbOptions_currentIndexChanged(int index);
    void on_treeUsers_customContextMenuRequested(QPoint pos);
    void on_treeUsers_doubleClicked(QModelIndex index);
    void on_txtChat_returnPressed();

    void IRC_DoNickChange(QString nick);
    void IRC_DoChannelJoin(QString channel);
    void IRC_Action_PM_User();
    void IRC_Action_Kick_User();
    void IRC_Action_Ban_User();
    void IRC_Action_Op_User();
    void IRC_Action_Voice_User();
    void IRC_Action_DeOp_User();
    void IRC_Action_DeVoice_User();

    void IRC_SetChannelTopic(QString topic);
    void IRC_SetChannelMode(QString mode);
};

#endif // CHATTAB_H
