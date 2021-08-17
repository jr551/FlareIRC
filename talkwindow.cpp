#include "talkwindow.h"
#include "ui_talkwindow.h"
#include "chattab.h"
#include "connectwindow.h"
#include <QMessageBox>
#include "privatemessagetab.h"
#include <QSettings>
#include "optionswindow.h"
#include "inputdialog.h"
#include <QSound>


TalkWindow::TalkWindow(QWidget *parent, QString server, int port, QString nick, QStringList channels ) :
    QMainWindow(parent),
    ui(new Ui::TalkWindow)
{
    ui->setupUi(this);
    setWindowIcon (QIcon(":/icons/icon_blue.png"));
    ircConnection = new IRCConnection(server, 6667, nick);
    ircConnection->Connect();
    serverTab = new ServerTab(this, this);
    ui->tabChats->removeTab(0);
    ui->tabChats->addTab( serverTab, server);
    joinChannels = channels;

    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(ShowWindow()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(ShowWindow()));

    trayIcon->setIcon(QIcon(":/icons/private_chat.png"));
    trayIcon->setVisible(true);
    trayIcon->setToolTip("FlareIRC - " + server );

    QString szPort;
    szPort.setNum(port);

    setWindowTitle(tr("FlareIRC ") + server + " ("+ nick +")");
    connect(ircConnection, SIGNAL(IRC_Connected()), this, SLOT(IRC_Connected()));
    connect(ircConnection, SIGNAL(IRC_Disconnected()), this, SLOT(IRC_Disconnected()));
    connect(ircConnection, SIGNAL(IRC_ReadyForCommands()), this, SLOT(IRC_ReadyForCommands()));
    connect(ircConnection, SIGNAL(IRC_ServerMessage(QString)), this, SLOT(IRC_ServerMessage(QString)));
    connect(ircConnection, SIGNAL(IRC_Error(e_IRC_Error)), this, SLOT(IRC_Error(e_IRC_Error)));
    connect(ircConnection, SIGNAL(IRC_MOTD_Line(QString)), this, SLOT(IRC_MOTD_Line(QString)));
    connect(ircConnection, SIGNAL(IRC_JoinedChannel(QString,QString)), this, SLOT(IRC_JoinedChannel(QString, QString)));
    connect(ircConnection, SIGNAL(IRC_PrivateMessage(QString, QString, bool)), this, SLOT(IRC_PrivateMessage(QString, QString, bool)));
    connect(ircConnection, SIGNAL(IRC_ChannelMessage(QString, QString, QString, bool)), this, SLOT(IRC_ChannelMessage(QString, QString, QString, bool)));
    connect(ircConnection, SIGNAL(IRC_LeftChannel(QString, QString, QString)), this, SLOT(IRC_LeftChannel(QString, QString, QString)));
    connect(ircConnection, SIGNAL(IRC_ModeChange(QString, QString, QString, QString)), this, SLOT(IRC_ModeChange(QString, QString, QString, QString)));
    connect(ircConnection, SIGNAL(IRC_UserList(QString,QStringList)), this, SLOT(IRC_UserList(QString, QStringList)));
    connect(ircConnection, SIGNAL(IRC_Kick(QString,QString,QString,QString)), this, SLOT(IRC_Kick(QString, QString,QString,QString)));
    connect(ircConnection, SIGNAL(IRC_ChannelTopic(QString,QString)), this, SLOT(IRC_ChannelTopic(QString, QString)));
    connect(ircConnection, SIGNAL(IRC_UserQuit(QString, QString)), this, SLOT(IRC_UserQuit(QString, QString)));
    connect(ircConnection, SIGNAL(IRC_NickChange(QString, QString)), this, SLOT(IRC_NickChange(QString, QString)));
    connect(ircConnection, SIGNAL(IRC_UserInfo(QString, QString)), this, SLOT(IRC_UserInfo(QString, QString)));
}

TalkWindow::~TalkWindow()
{
    ircConnection->SendRawData(tr("QUIT"));
    trayIcon->hide();
    delete ui;
    delete trayIcon;
    delete serverTab;
    delete ircConnection;
}

void TalkWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TalkWindow::SendRaw( QString message )
{
    ircConnection->SendRawData(message);
}

void TalkWindow::IRC_ServerMessage( QString msg )
{
    serverTab->AddChatLine(msg);
}
void TalkWindow::IRC_Disconnected()
{
    for ( int i = 0; i < ui->tabChats->count(); i++ )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(i);

        if (!tb)
            continue;
        tb->AddChatLine( "<FONT COLOR='red'>Disconnected from server</FONT>");
    }
    serverTab->AddStatusLine( "Disconnected from server", QIcon(":/icons/disconnect.png") );

}


void TalkWindow::IRC_Error( e_IRC_Error error )
{
    switch ( error )
    {
        case ERR_NICKNAMEINUSE:
            serverTab->AddStatusLine( "Your Nickname is already in use", QIcon(":/icons/error.png") );
            break;
        case ERR_ERRONEUSNICKNAME:
            serverTab->AddStatusLine( "Your Nickname contains invalid characters", QIcon(":/icons/error.png") );
            break;
        case ERR_NONICKNAMEGIVEN:
            serverTab->AddStatusLine( "You did not give a nickname", QIcon(":/icons/error.png") );
            break;
        default:
            serverTab->AddStatusLine( "Unknown IRC Error", QIcon(":/icons/error.png") );
    }
    ircConnection->Disconnect();
}

void TalkWindow::IRC_MOTD_Line( QString line )
{
    serverTab->AddMOTDLine(line);
}

void TalkWindow::IRC_ReadyForCommands()
{
    QStringListIterator itChans(joinChannels);
       while (itChans.hasNext())
           ircConnection->JoinChannel(itChans.next());

    QSettings settings;
    if ( settings.value ( tr("Use_Ident"), QVariant(false) ).toBool() )
    {
        // Send both types some servers differ.
        SendRaw( "AUTHSERV IDENTIFY " + settings.value ( tr("IdentUsername"), QVariant(tr("")) ).toString() + " " + settings.value ( tr("IdentPassword"), QVariant(tr("")) ).toString());
        SendRaw( "NICKSERV IDENTIFY " + settings.value ( tr("IdentUsername"), QVariant(tr("")) ).toString() + " " + settings.value ( tr("IdentPassword"), QVariant(tr("")) ).toString());

    }

}

void TalkWindow::IRC_Connected()
{
    for ( int i = 0; i < ui->tabChats->count(); i++ )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(i);

        if (!tb)
            continue;
        tb->AddChatLine( "<FONT COLOR='green'>Connected to server.</FONT>");
    }

    serverTab->AddStatusLine( "Connected to server", QIcon(":/icons/server_chat.png") );
}

void TalkWindow::IRC_NickChange( QString oldNick, QString newNick )
{
    bool localNickChanged = false;
    if (oldNick.compare( ircConnection->getNick(), Qt::CaseInsensitive) == 0 )
    {
        ircConnection->updateNick(newNick);
        serverTab->AddStatusLine( "Your nickname was changed to " + newNick, QIcon(":/icons/edit.png") );
        setWindowTitle(tr("FlareIRC ") + ircConnection->getServer() + " ("+ newNick +")");
        localNickChanged = true;
        ircConnection->updateNick(newNick);
    }

    for ( int i = 0; i < ui->tabChats->count(); i++ )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(i);

        if (!tb)
            continue;

        if (localNickChanged)
            tb->LocalNickUpdated(newNick);

        if ( tb->GetTabContext().compare( oldNick, Qt::CaseInsensitive ) == 0 )
            ui->tabChats->setTabText( ui->tabChats->indexOf(tb), newNick);

        if ( tb->UpdateNick( oldNick, newNick ) )
            tb->AddChatLine( "<FONT COLOR='orange'><b>" + oldNick + "</b> changed their nickname to <b>" + newNick + "</b></FONT>");

    }

}


void TalkWindow::IRC_JoinedChannel( QString source, QString channel )
{
    if ( source.compare( ircConnection->getNick(), Qt::CaseInsensitive ) == 0 )
    {
        ChatTab *t = new ChatTab(ui->tabChats, this, channel);
        ui->tabChats->addTab( t, channel);
        ui->tabChats->setCurrentWidget(t);
        serverTab->AddStatusLine( "You have joined the channel " + channel, QIcon(":/icons/channel_chat.png") );
        return;
    }

    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(channel);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
        return;

    ChatTab *chatTab = (ChatTab*)tb;
    NotifyChange(chatTab);
    chatTab->AddUser(source);
    chatTab->AddChatLine( "<FONT COLOR='green'><b>" + source + "</b> joined the channel</FONT>");

}
void TalkWindow::IRC_UserList( QString channel, QStringList users)
{
    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(channel);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
        return;
    ChatTab *chatTab = (ChatTab*)tb;

    users.removeAll("");

    QStringListIterator itUsers(users);
       while (itUsers.hasNext())
           chatTab->AddUser(itUsers.next());
}

void TalkWindow::IRC_ModeChange( QString source, QString channel, QString whom, QString modes  )
{
    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(channel);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
        return;

    if ( whom.compare("", Qt::CaseInsensitive) == 0 )
        tb->AddChatLine("<FONT COLOR='purple'><b>" + source + "</b> set mode(s) " + modes + " on <b>" + channel + "</b></FONT>");
    else
    {
        tb->AddChatLine("<FONT COLOR='purple'><b>" + source + "</b> set mode(s) " + modes + " on <b>" + whom + "</b></FONT>");

        ChatTab *chatTab = (ChatTab*)tb;
        chatTab->ModeUser(whom, modes);
    }
    NotifyChange(tb);

}
void TalkWindow::IRC_LeftChannel( QString source, QString channel, QString quitMsg  )
{
    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(channel);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
        return;

    ChatTab *chatTab = (ChatTab*)tb;
    NotifyChange(chatTab);
    chatTab->RemoveUser(source);
    chatTab->AddChatLine( "<FONT COLOR='red'><b>" + source + "</b> left the channel (" + quitMsg + ")</FONT>");

}

void TalkWindow::IRC_UserQuit( QString source, QString quitMsg  )
{
    for ( int i = 0; i < ui->tabChats->count(); i++ )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(i);
        if (!tb)
            continue;
        if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
            continue;

        ChatTab *chatTab = (ChatTab*)tb;

        if ( chatTab->RemoveUser(source) )
        {
            chatTab->RemoveUser(source);
            chatTab->AddChatLine( "<FONT COLOR='red'><b>" + source + "</b> Quit (" + quitMsg + ")</FONT>");
            NotifyChange(chatTab);
        }
    }

}

void TalkWindow::IRC_Kick( QString source, QString channel, QString whom, QString message )
{
    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(channel);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
        return;

    ChatTab *chatTab = (ChatTab*)tb;
    NotifyChange(chatTab);
    if ( whom.compare(ircConnection->getNick(), Qt::CaseInsensitive ) == 0 )
    {
        QMessageBox::information(NULL, tr("FlareIRC - Kick."), "You were kicked from " + channel + " by " + source + " (" + message + ")");
        serverTab->AddStatusLine( "You were kicked from " + channel, QIcon(":/icons/channel_chat.png") );
        on_tabChats_tabCloseRequested(ui->tabChats->indexOf(chatTab));
        return;
    }

    chatTab->AddChatLine( "<FONT COLOR='red'><b>" + whom + "</b> was kicked by <b>" + source + "</b> reason: (" + message + ")</FONT>");
    chatTab->RemoveUser(whom);



}

void TalkWindow::IRC_ChannelMessage( QString source, QString context, QString msg, bool action )
{
    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(context);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::CHANNEL_TAB)
        return;

    QSettings settings;
    if ( settings.value ( tr("NotifyChanMsg"), QVariant(false) ).toBool() )
        trayIcon->showMessage(context + " " + source, msg, QSystemTrayIcon::Information, 100);

    if ( settings.value ( tr("SoundChanMsg"), QVariant(false) ).toBool() )
    {
        QSound snd( ":/sounds/notify.wav", this );
        snd.play();
    }


    ChatTab *chatTab = (ChatTab*)tb;
    NotifyChange(tb);
    if ( action )
        chatTab->AddChatLine("<FONT COLOR='#FF0066'><b> **" + source + " " + msg + "** </b></FONT>");
    else
        chatTab->AddChatLine("<FONT COLOR='#666'><b>" +source + "</b></FONT>: " + msg);

}

void TalkWindow::ShowWindow()
{
    activateWindow();
}

void TalkWindow::IRC_PrivateMessage( QString source, QString msg, bool action )
{
    PrivateMessageTab *tab = TabForPrivChat(source);
    if (!tab)
        return;

    QSettings settings;
    if ( settings.value ( tr("NotifyPrivMsg"), QVariant(false) ).toBool() )
        trayIcon->showMessage("Message from " + source, msg, QSystemTrayIcon::Information, 100);

    if ( settings.value ( tr("SoundPrivMsg"), QVariant(false) ).toBool() )
    {
        QSound snd( ":/sounds/notify.wav", this );
        snd.play();
    }

    NotifyChange(tab);
    if ( action )
        tab->AddChatLine("<FONT COLOR='#FF0066'><b> **" + source + " " + msg + "** </b></FONT>");
    else
        tab->AddChatLine("<FONT COLOR='#666'><b>" +source + "</b></FONT>: " + msg);
}

PrivateMessageTab *TalkWindow::TabForPrivChat( QString user )
{
    TalkWindowTab *tb = FindTabByContext(user);
    if (tb && tb->GetTabType() != TalkWindowTab::PRIVMSG_TAB)
        return NULL;
    PrivateMessageTab *tabChat = (PrivateMessageTab *)tb;

    if (!tabChat)
    {
        tabChat = new PrivateMessageTab(ui->tabChats, this, user);
        ui->tabChats->addTab( tabChat, user);
        ui->tabChats->setCurrentWidget(tabChat);
    }
    return tabChat;
}

void TalkWindow::NotifyChange( int tabIndex, bool userViewed )
{

    if ( !userViewed && ui->tabChats->currentIndex() != tabIndex)
    {
        setWindowIcon (QIcon(":/icons/icon_red.png"));
        QIcon ico( ":/icons/Mail.png");
        ui->tabChats->setTabIcon(tabIndex, ico);
    }
    else if ( userViewed )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(tabIndex);
        setWindowIcon (QIcon(":/icons/icon_blue.png"));

        QIcon ico;
        if ( tb && tb->GetTabType() == TalkWindowTab::SERVER_TAB )
          ico = QIcon(":/icons/server_chat.png");
        else if ( tb && tb->GetTabType() == TalkWindowTab::CHANNEL_TAB )
          ico = QIcon(":/icons/channel_chat.png");
        else if ( tb && tb->GetTabType() == TalkWindowTab::PRIVMSG_TAB )
          ico = QIcon(":/icons/private_chat.png");

        ui->tabChats->setTabIcon(tabIndex, ico);
    }
}
void TalkWindow::NotifyChange( TalkWindowTab* tab, bool userViewed )
{
    for ( int i = 0; i < ui->tabChats->count(); i++ )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(i);
        if (tb == tab)
        {
            NotifyChange( i, userViewed );
        }
    }
}
TalkWindowTab* TalkWindow::FindTabByContext( QString context )
{
    for ( int i = 0; i < ui->tabChats->count(); i++ )
    {
        TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(i);

        if (!tb /*|| !((QObject*)tb)->inherits("TalkWindowTab")*/ )
            continue;

        if ( !tb->GetTabContext().isNull() && context.compare(tb->GetTabContext(), Qt::CaseInsensitive ) == 0  )
            return tb;
    }
    return NULL;
}

void TalkWindow::SendMessage( QString channel, QString message )
{
    QString msg;
    if ( message.startsWith("/me ") )
    {
        QString sendString = "ACTION " + message.mid(4) + "";
        ircConnection->PrivMsg( channel, sendString );
        msg = "<FONT COLOR='#FF0066'><b> ** " + ircConnection->getNick() + " " + message.mid(3) + " ** </b></FONT>";
    }
    else if ( message.startsWith("/nick ") )
    {
        ircConnection->ChangeNick(message.mid(6));
        msg = "<FONT COLOR='#FF0066'><b> You changed your nick to " + message.mid(6) + " </b></FONT>";
    }
    else
    {
        ircConnection->PrivMsg( channel, message );
        msg = "<b>" + ircConnection->getNick() +  ":</b> " + message ;
    }

    TalkWindowTab *tb = FindTabByContext(channel);
    if (tb)
        tb->AddChatLine(msg);

}
void TalkWindow::IRC_ChannelTopic( QString channel, QString topic)
{
    TalkWindowTab *tb = FindTabByContext(channel);
    if (tb)
    {
        NotifyChange(tb);
        tb->AddChatLine("<FONT COLOR='#9999CC'><i> Topic: " + topic + "</i></FONT>" );
    }
}

void TalkWindow::on_tabChats_tabCloseRequested(int index)
{
    QSettings settings;
    TalkWindowTab *tb = (TalkWindowTab*)ui->tabChats->widget(index);

    if (!tb)
        return;

    if ( tb->GetTabType() == TalkWindowTab::SERVER_TAB )
    {
        if ( QMessageBox::question(this, "Really disconnect?", "Do you really want to disconnect from the server?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No )
            return;
        ircConnection->SendRawData("QUIT : " + settings.value ( tr("QuitMessage"), QVariant(tr("FlareIRC C++ Client")) ).toString() );
        for ( int i = 0; i < ui->tabChats->count(); i++ )
        {
            ui->tabChats->widget(i)->setEnabled(false);
        }

        setWindowTitle(tr("FlareIRC ") + ircConnection->getServer() + " : Disconnected.");
        return;
    }
    else if ( tb->GetTabType() == TalkWindowTab::PRIVMSG_TAB )
    {
        if ( settings.value( tr("InformChatClose"), QVariant(true) ).toBool() )
            ircConnection->PrivMsg( tb->GetTabContext(), "ACTION has closed the conversation tab.");
    }
    else if ( tb->GetTabType() == TalkWindowTab::CHANNEL_TAB )
    {
        serverTab->AddStatusLine( "You have left the channel " + tb->GetTabContext(), QIcon(":/icons/channel_chat.png") );
        ircConnection->LeaveChannel(tb->GetTabContext(), settings.value ( tr("PartMessage"), QVariant(tr("FlareIRC C++ Client")) ).toString()  );
    }

    ui->tabChats->removeTab(index);

}
void TalkWindow::IRC_UserInfo( QString user, QString data)
{
    TalkWindowTab *tb = (TalkWindowTab*)FindTabByContext(user);
    if (!tb)
        return;
    if (tb->GetTabType() != TalkWindowTab::PRIVMSG_TAB)
        return;

    PrivateMessageTab *pTab = (PrivateMessageTab*)tb;
    pTab->UpdateUserInfo( data );
}


void TalkWindow::on_actionNew_Server_Connection_triggered()
{
    extern ConnectWindow *gConnectWindow;
    if (gConnectWindow)
        gConnectWindow->show();
}

void TalkWindow::on_tabChats_currentChanged(int index)
{
    NotifyChange(index, true);
}

void TalkWindow::on_actionOpen_Options_triggered()
{
    OptionsWindow *optWin = new OptionsWindow(this);
    optWin->show();
}

void TalkWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("FlareIRC - Alpha 0.1"), "Written by John Rowe");
}

void TalkWindow::on_actionJoin_Channel_triggered()
{
    InputDialog *dialog = new InputDialog(this, "Join Channel", "Which channel do you wish to join?", "#" );
    connect(dialog, SIGNAL(OK_Clicked(QString)), this, SLOT(DoJoinChannel(QString)));
    dialog->show();
}

void TalkWindow::DoJoinChannel( QString channel )
{
     ircConnection->JoinChannel(channel);
}

void TalkWindow::on_actionDisconnect_triggered()
{
    //disconn
}

void TalkWindow::on_actionExit_triggered()
{
    exit(1);
}

void TalkWindow::on_TalkWindow_destroyed()
{
    extern ConnectWindow *gConnectWindow;
    if (gConnectWindow)
        gConnectWindow->show();
}
void TalkWindow::ChangeLocalNick( QString nick )
{
     ircConnection->ChangeNick(nick);
}
void TalkWindow::DoNickChange(QString nick) // need 2 here because of Qt slots.
{
    ChangeLocalNick(nick);
}

void TalkWindow::on_actionChange_Nick_triggered()
{
    InputDialog *dialog = new InputDialog(this, "Change Nick", "What do you want to change your nick to?", ircConnection->getNick() );
    connect(dialog, SIGNAL(OK_Clicked(QString)), this, SLOT(DoNickChange(QString)));
    dialog->show();
}
