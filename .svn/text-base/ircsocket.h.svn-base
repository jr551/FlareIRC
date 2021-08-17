#ifndef IRCSOCKET_H
#define IRCSOCKET_H

#include <QTCPSocket>
#include <QList>
#include <QStringList>
#include <QTime>

enum e_IRC_Error
{
    ERR_NICKNAMEINUSE = 0, //433 (rfc2812)
    ERR_ERRONEUSNICKNAME,  //432 (rfc2812)
    ERR_NONICKNAMEGIVEN,   //431 (rfc2812)
    ERR_LAST
};

class IRCConnection : public QObject
{
    Q_OBJECT
public:
    IRCConnection( QString server, int port, QString nick );
    void Connect( );
    void Disconnect();
    void SendRawData( QString data );
    void JoinChannel( QString channel );
    void PrivMsg( QString to, QString message );
    void LeaveChannel( QString channel, QString partMsg );
    void Login();
    bool IsInChannel( QString channel );
    QString getServer(){ return szServer; }
    QString getNick(){ return szNick; }
    void ChangeNick( QString newNick );
    void updateNick( QString newNick ){ szNick = newNick; }


private:
    QString szServer;
    QString szNick;
    int iPort;
    QTcpSocket* qSocket;
    bool bConnecting;
    QStringList lsChannels;
    bool bReadyForCommands;


private slots:

    void Connection_ReadyRead();
    void displayError(QAbstractSocket::SocketError socketError);
    void Connection_Connected();
    void Connection_Disconnected();
    void Connection_StateChanged( QAbstractSocket::SocketState socketState );

signals:

    void IRC_Connected();
    void IRC_Disconnected();

    void IRC_ReadyForCommands();

    void IRC_JoinedChannel( QString source, QString channel );
    void IRC_LeftChannel( QString source, QString channel, QString quitMsg  );
    void IRC_UserQuit( QString source, QString quitMsg  );

    void IRC_ModeChange( QString source, QString channel, QString whom, QString modes  );

    void IRC_ChannelMessage( QString source, QString context, QString msg, bool action );
    void IRC_PrivateMessage( QString source, QString msg, bool action );
    void IRC_ServerMessage( QString msg );

    void IRC_Kick( QString source, QString channel, QString whom, QString message );

    void IRC_MOTD_Line( QString line );

    void IRC_NickChange( QString oldNick, QString newNick );
    void IRC_UserList( QString channel, QStringList users);
    void IRC_ChannelTopic( QString channel, QString topic);
    void IRC_UserInfo( QString user, QString data);

    void IRC_Error( e_IRC_Error error );
};

#endif // IRCSOCKET_H
