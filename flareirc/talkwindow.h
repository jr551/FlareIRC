#ifndef TALKWINDOW_H
#define TALKWINDOW_H

#include <QMainWindow>
#include "ircsocket.h"
#include "privatemessagetab.h"
#include "servertab.h"
#include <QSystemTrayIcon>
namespace Ui {
    class TalkWindow;
}

class PrivateMessageTab;
class ServerTab;
class TalkWindow : public QMainWindow {
    Q_OBJECT
public:
    // Qt makes you *need* a constructor which can be called like this.
    TalkWindow(QWidget *parent = 0, QString server=tr("null"), int port=0, QString nick=tr("null"), QStringList channels=QStringList() );
    ~TalkWindow();
    void SendRaw( QString message );
    void ChangeLocalNick( QString nick );
    void SendMessage( QString channel, QString message );
    void DoPrivateChat( QString user ){ TabForPrivChat(user); }
    IRCConnection *GetIRCConnection(){ return ircConnection; }
protected:
    void changeEvent(QEvent *e);
    void NotifyChange( TalkWindowTab* tab, bool userViewed = false);
    void NotifyChange( int tabIndex, bool userViewed = false);
    PrivateMessageTab *TabForPrivChat( QString user );
    TalkWindowTab* FindTabByContext( QString context );

private:
    Ui::TalkWindow *ui;
    IRCConnection   *ircConnection;
    ServerTab   *serverTab;
    QStringList joinChannels;
    QSystemTrayIcon *trayIcon;
private slots:
    void ShowWindow();
    void on_actionChange_Nick_triggered();
    void on_TalkWindow_destroyed();
    void DoJoinChannel( QString channel );

    void on_actionExit_triggered();
    void on_actionDisconnect_triggered();
    void on_actionJoin_Channel_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_Options_triggered();
    void on_tabChats_currentChanged(int index);
    void on_actionNew_Server_Connection_triggered();
    void on_tabChats_tabCloseRequested(int index);

    void DoNickChange(QString nick);


    void IRC_Error( e_IRC_Error error );
    void IRC_ServerMessage( QString msg );
    void IRC_Connected();
    void IRC_ReadyForCommands();
    void IRC_Disconnected();
    void IRC_JoinedChannel( QString source, QString channel );

    void IRC_LeftChannel( QString source, QString channel, QString quitMsg  );
    void IRC_ModeChange( QString source, QString channel, QString whom, QString modes  );
    void IRC_PrivateMessage( QString source, QString msg, bool action );
    void IRC_ChannelMessage( QString source, QString context, QString msg, bool action );
    void IRC_UserList( QString channel, QStringList users);
    void IRC_Kick( QString source, QString channel, QString whom, QString message );
    void IRC_ChannelTopic( QString channel, QString topic);
    void IRC_UserQuit( QString source, QString quitMsg  );
    void IRC_NickChange( QString oldNick, QString newNick );
    void IRC_UserInfo( QString user, QString data);
    void IRC_MOTD_Line( QString line );

};

#endif // TALKWINDOW_H
