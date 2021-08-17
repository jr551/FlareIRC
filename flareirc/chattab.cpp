#include "chattab.h"
#include "ui_chattab.h"
#include <QMenu>
#include "inputdialog.h"
#include <QList>

ChatTab::ChatTab(QWidget *parent, TalkWindow *pTalkWindow, QString tChannel) :
    TalkWindowTab(parent),
    ui(new Ui::ChatTab)
{
    iUserCount = 0;
    channel = tChannel;
    talkWindow = pTalkWindow;
    ui->setupUi(this);

    QColor grey(51,51,51,255);
    QBrush greyBrush( grey );

    treeOps = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Ops")) );
    treeOps->setForeground(0, greyBrush );
    treeVoice = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Voiced")) );
    treeVoice->setForeground(0, greyBrush );
    treeOthers = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Others")) );
    treeOthers->setForeground(0, greyBrush );
    ui->treeUsers->insertTopLevelItem(0, treeOthers);
    ui->treeUsers->insertTopLevelItem(0, treeVoice);
    ui->treeUsers->insertTopLevelItem(0, treeOps);
    ui->treeUsers->expandAll();

    ui->txtChat->setFocus();

    ui->cmbOptions->addItem( QIcon(":/icons/user_voice.png"), pTalkWindow->GetIRCConnection()->getNick() );
    ui->cmbOptions->addItem( QIcon(":/icons/edit.png"), "Change Nick" );
    ui->cmbOptions->addItem( QIcon(":/icons/edit.png"), "Set Topic" );
    ui->cmbOptions->addItem( QIcon(":/icons/edit.png"), "Set Channel Mode");
    ui->cmbOptions->addItem( QIcon(":/icons/channel_chat.png"), "Join Channel");
}

ChatTab::~ChatTab()
{
    delete ui;
}

void ChatTab::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool ChatTab::UpdateNick( QString oldNick, QString newNick )
{

    IRCUserItem *user = FindUserByUserName( oldNick );
    if (!user)
        return false;

    user->setUserName(newNick);
    return true;
}


void ChatTab:: AddChatLine( QString line )
{

    ui->txtMessages->append(line);
}

void ChatTab::AddUser( QString user )
{\
    if ( user.mid(0,1).compare("@") == 0 )
        treeOps->addChild( new IRCUserItem( user.mid(1), "+o") );
    else if ( user.mid(0,1).compare("+") == 0 )
        treeVoice->addChild( new IRCUserItem( user.mid(1), "+v") );
    else
        treeOthers->addChild( new IRCUserItem( user, "") );
    iUserCount++;
    QString usersNum;
    usersNum.setNum(iUserCount);
    ui->lblUserCount->setText(usersNum + tr(" Users"));
}


bool ChatTab::RemoveUser( QString user )
{
    IRCUserItem *ircUser = FindUserByUserName( user );
    if (!ircUser)
        return false;

    RemoveUserFromUserList(ircUser);
    iUserCount--;

    QString usersNum;
    usersNum.setNum(iUserCount);
    ui->lblUserCount->setText(usersNum + tr(" Users"));

    return true;
}

void ChatTab::ModeUser( QString user, QString modes )
{
    IRCUserItem *ircUser = FindUserByUserName( user );
    if (!ircUser)
        return;

    ircUser->parseMode(modes);
    UpdateUserCategory( ircUser );
}

void ChatTab::UpdateUserCategory( IRCUserItem *ircUser )
{
    IRCUserItem *ircUserIt = FindUserByUserName( ircUser->getUserName() );
    if (!ircUserIt)
        return;

    RemoveUserFromUserList(ircUserIt);

    if ( ircUserIt->isOp() )
        treeOps->addChild(ircUserIt);
    else if ( ircUserIt->isVoiced() )
        treeVoice->addChild(ircUserIt);
    else
        treeOthers->addChild(ircUserIt);

}

void ChatTab::EditUser( QString oldUser, QString newUser )
{
    IRCUserItem *user = FindUserByUserName( oldUser );
    if (!user)
        return;
    user->setUserName(newUser);
}

void ChatTab::on_txtChat_returnPressed()
{
    if ( ui->txtChat->text().length() < 1 )
        return;

    talkWindow->SendMessage(channel, ui->txtChat->text() );
    ui->txtChat->clear();
}

void ChatTab::IRC_SetChannelTopic(QString topic)
{
    talkWindow->SendRaw( "TOPIC " + channel + " :" + topic );
    AddChatLine( "<FONT COLOR='brown'>Sent topic change request</font>");
}
void ChatTab::IRC_SetChannelMode(QString mode)
{
    talkWindow->SendRaw( "MODE " + channel + " " + mode);
    AddChatLine( "<FONT COLOR='brown'>Channel mode change requested</font>");
}

void ChatTab::on_treeUsers_doubleClicked(QModelIndex index)
{
    IRCUserItem *ircUser = GetSelectedUser();
    if (!ircUser)
        return;

    talkWindow->DoPrivateChat( ircUser->getUserName() );
}

void ChatTab::on_treeUsers_customContextMenuRequested(QPoint pos)
{
    ui->treeUsers->clearSelection();
    ui->treeUsers->setItemSelected( ui->treeUsers->itemAt(pos), true );
    QMenu *menu = new QMenu;
    menu->addAction(tr("PM User"), this, SLOT(IRC_Action_PM_User()));
    menu->addAction(tr("Kick User"), this, SLOT(IRC_Action_Kick_User()));
    menu->addAction(tr("Ban User"), this, SLOT(IRC_Action_Ban_User()));
    menu->addAction(tr("Op User"), this, SLOT(IRC_Action_Op_User()));
    menu->addAction(tr("Voice User"), this, SLOT(IRC_Action_Voice_User()));
    menu->addAction(tr("De-Op User"), this, SLOT(IRC_Action_DeOp_User()));
    menu->addAction(tr("De-Voice User"), this, SLOT(IRC_Action_DeVoice_User()));
    menu->exec( ui->treeUsers->mapToGlobal(pos));

}
IRCUserItem *ChatTab::FindUserByUserName( QString userName )
{
    class IRCSearchClass
    {
    public:
        static IRCUserItem *findUser( QString userName, QTreeWidgetItem* nodeTree )
        {
            for ( int i = 0; i < nodeTree->childCount(); i++ )
            {
                IRCUserItem *ircUser = (IRCUserItem*)nodeTree->child(i);
                if (!ircUser)
                    continue;
                QString cUser = ircUser->getUserName();
                if ( cUser.compare(userName, Qt::CaseInsensitive) == 0 )
                {
                    return ircUser;
                }
            }
            return NULL;
        }
    };

    IRCUserItem *possUser = NULL;

    possUser = IRCSearchClass::findUser(userName, treeOps);

    if (possUser)
        return possUser;

    possUser = IRCSearchClass::findUser(userName, treeVoice);

    if (possUser)
        return possUser;

    possUser = IRCSearchClass::findUser(userName, treeOthers);

    if (possUser)
        return possUser;

    return NULL;

}
void ChatTab::RemoveUserFromUserList( IRCUserItem* user )
{
    class IRCSearchClass
    {
    public:
        static void findAndRemoveUser( IRCUserItem* userRemove, QTreeWidgetItem* nodeTree )
        {
            for ( int i = 0; i < nodeTree->childCount(); i++ )
            {
                if ( nodeTree->child(i) == userRemove )
                {
                    nodeTree->removeChild(userRemove);
                }
            }
        }
    };

    IRCSearchClass::findAndRemoveUser(user, treeOps);
    IRCSearchClass::findAndRemoveUser(user, treeVoice);
    IRCSearchClass::findAndRemoveUser(user, treeOthers);

}
IRCUserItem *ChatTab::GetSelectedUser()
{
    QList<QTreeWidgetItem*> selItems = ui->treeUsers->selectedItems();

    if (selItems.isEmpty())
        return NULL;

    QTreeWidgetItem *item = selItems.at(0);
    if ( item->foreground(0).color().red() == 51)
        return NULL;

    IRCUserItem *ircUser = (IRCUserItem*)item;
    if (!ircUser)
        return NULL;

    return ircUser;
}

void ChatTab::IRC_Action_PM_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->DoPrivateChat( pUser->getUserName() );
}

void ChatTab::IRC_Action_Kick_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->SendRaw( "KICK " + channel + " " + pUser->getUserName() + " : Bye bye!" );
    AddChatLine( "<FONT COLOR='brown'>You have attempted to kick <b>" + pUser->getUserName() + "</b></font>");
}
void ChatTab::IRC_Action_Ban_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->SendRaw( "MODE " + channel + " +b " + pUser->getUserName() );
    AddChatLine( "<FONT COLOR='brown'>You have attempted to ban <b>" + pUser->getUserName() + "</b></font>");
}
void ChatTab::IRC_Action_Op_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->SendRaw( "MODE " + channel + " +o " + pUser->getUserName() );
    AddChatLine( "<FONT COLOR='brown'>You have attempted to op <b>" + pUser->getUserName() + "</b></font>");
}
void ChatTab::IRC_Action_Voice_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->SendRaw( "MODE " + channel + " +v " + pUser->getUserName() );
    AddChatLine( "<FONT COLOR='brown'>You have attempted to voice <b>" + pUser->getUserName() + "</b></font>");
}
void ChatTab::IRC_Action_DeOp_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->SendRaw( "MODE " + channel + " -o " + pUser->getUserName() );
    AddChatLine( "<FONT COLOR='brown'>You have attempted to de-op <b>" + pUser->getUserName() + "</b></font>");
}
void ChatTab::IRC_Action_DeVoice_User()
{
    IRCUserItem *pUser = GetSelectedUser();
    if (!pUser)
        return;

    talkWindow->SendRaw( "MODE " + channel + " +v " + pUser->getUserName() );
    AddChatLine( "<FONT COLOR='brown'>You have attempted to de-voice <b>" + pUser->getUserName() + "</b></font>");
}

void ChatTab::LocalNickUpdated(QString nick)
{
    ui->cmbOptions->setItemText(0, nick);
}

void ChatTab::IRC_DoNickChange(QString nick)
{
    talkWindow->ChangeLocalNick(nick);
}
void ChatTab::IRC_DoChannelJoin(QString channel)
{
    talkWindow->SendRaw("JOIN " + channel);
}


void ChatTab::on_cmbOptions_currentIndexChanged(int index)
{
    if (ui->cmbOptions->currentIndex() == 1 )
    {
        InputDialog *dialog = new InputDialog(this, "Change Nick", "What do you want to change your nick to?", talkWindow->GetIRCConnection()->getNick() );
        connect(dialog, SIGNAL(OK_Clicked(QString)), this, SLOT(IRC_DoNickChange(QString)));
        dialog->show();
    }
    else if (ui->cmbOptions->currentIndex() == 2 )
    {

        InputDialog *dialog = new InputDialog(this, "New Topic", "Enter new topic for channel " + channel, "" );
        connect(dialog, SIGNAL(OK_Clicked(QString)), this, SLOT(IRC_SetChannelTopic(QString)));
        dialog->show();
    }
    else if (ui->cmbOptions->currentIndex() == 3 )
    {
        InputDialog *dialog = new InputDialog(this, "Set Mode(s)", "Enter new modes for channel " + channel, "+" );
        connect(dialog, SIGNAL(OK_Clicked(QString)), this, SLOT(IRC_SetChannelMode(QString)));
        dialog->show();

    }
    else if (ui->cmbOptions->currentIndex() == 4 )
    {
        InputDialog *dialog = new InputDialog(this, "Join Channel", "What channel do you want to join?", "#" );
        connect(dialog, SIGNAL(OK_Clicked(QString)), this, SLOT(IRC_DoChannelJoin(QString)));
        dialog->show();

    }

    ui->cmbOptions->setCurrentIndex(0);

}
