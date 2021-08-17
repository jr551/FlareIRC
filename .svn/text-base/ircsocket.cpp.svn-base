#include "ircsocket.h"
#include <qmessagebox.h>
#include <QHostAddress>
#include <QTimer>

IRCConnection::IRCConnection( QString server, int port, QString nick )
{
    szServer = server;
    iPort = port;
    szNick = nick;
    qSocket = new QTcpSocket(this);
    bConnecting = false;
    bReadyForCommands = false;

    connect(qSocket, SIGNAL(readyRead()), this, SLOT(Connection_ReadyRead()));
    connect(qSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(qSocket, SIGNAL(connected()), this, SLOT(Connection_Connected()));
    connect(qSocket, SIGNAL(disconnected()), this, SLOT(Connection_Disconnected()));
    connect(qSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(Connection_StateChanged(QAbstractSocket::SocketState)));
}

void IRCConnection::Connect( )
{
    qSocket->connectToHost( szServer, iPort );
}
void IRCConnection::Disconnect()
{
    qSocket->close();
}

void IRCConnection::Connection_Connected()
{
    Login();
    emit IRC_Connected();
}

void IRCConnection::JoinChannel( QString channel )
{
    char joinString[128];
    snprintf(joinString, sizeof(joinString), "JOIN %s\r\n", qPrintable(channel));
    qSocket->write(joinString);

}

void IRCConnection::PrivMsg( QString to, QString message )
{
    char msgString[256];
    snprintf(msgString, sizeof(msgString), "PRIVMSG %s :%s\r\n", qPrintable(to), qPrintable(message));
    SendRawData(msgString);
}

void IRCConnection::ChangeNick( QString newNick )
{
    char msgString[256];
    snprintf(msgString, sizeof(msgString), "NICK %s\r\n", qPrintable(newNick));
    SendRawData(msgString);
}

void IRCConnection::Login()
{
    char nickString[128];
    snprintf(nickString, sizeof(nickString), "NICK %s\r\n", qPrintable(szNick));

    qSocket->write( nickString);

    char userString[128];
    snprintf(userString, sizeof(userString), "USER %s * %s :FlareIRC C++ Client\r\n", qPrintable(szNick), qPrintable(szServer) );
    qSocket->write(userString);
    emit IRC_ServerMessage(tr("<b>Sending: ") + userString + "</b>");

}

void IRCConnection::Connection_Disconnected()
{
    emit IRC_Disconnected();
}
void IRCConnection::Connection_StateChanged( QAbstractSocket::SocketState socketState )
{
    /*QString st;
    st.setNum(socketState);
    if (socketState == QAbstractSocket::UnconnectedState )
    {

    }
    emit IRC_ServerMessage("**** (debug)<b>Connection_StateChanged: " + st + " </b>");*/
}

void IRCConnection::LeaveChannel( QString channel, QString partMsg  )
{

    lsChannels.removeOne(channel);
    char dataString[256];
    snprintf(dataString, sizeof(dataString), "PART %s :%s\r\n", qPrintable(channel), qPrintable(partMsg) );
    qSocket->write(dataString);
}

bool IRCConnection::IsInChannel( QString channel )
{
    return lsChannels.contains(channel);
}

void IRCConnection::SendRawData( QString data )
{
    char dataString[256];
    snprintf(dataString, sizeof(dataString), "%s\r\n", qPrintable(data));
    qSocket->write(dataString);
}


void IRCConnection::Connection_ReadyRead()
{
    QTextStream stream(qSocket);
    QString data;

    
    while (true)
    {
        if ( stream.atEnd() )
            break;

        data = stream.readLine();
        if (data.isNull())
            break;

        QStringList lst = data.split(tr(" "));
        QStringList lstParam = data.split(tr(":"));
        QStringList lstExcla = lst.first().split(tr("!"));

        if ( lst.size() > 0 && lst.at(0).compare(tr("PING"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            QString pingReply ("PONG "+lst.last()+"\r\n");
            qSocket->write(pingReply.toAscii());
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("001"), Qt::CaseInsensitive) == 0 && !bReadyForCommands)
        {
            emit IRC_ReadyForCommands();  
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("433"), Qt::CaseInsensitive) == 0)
        {
            emit IRC_Error(ERR_NICKNAMEINUSE);
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("432"), Qt::CaseInsensitive) == 0)
        {
            emit IRC_Error(ERR_ERRONEUSNICKNAME);
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("431"), Qt::CaseInsensitive) == 0)
        {
            emit IRC_Error(ERR_NONICKNAMEGIVEN);
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("JOIN"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            if (lstExcla.first().mid(1).compare( getNick(), Qt::CaseInsensitive) == 0)
                lsChannels.append(lst.last());

             emit IRC_ServerMessage(tr("<b>Joined: (") + data + ")" +  lstParam.last() + "</b>");

             if ( lstParam.last().at(0) != '#')
                 emit IRC_JoinedChannel( lstExcla.first().mid(1), lst.last() );
             else
                emit IRC_JoinedChannel( lstExcla.first().mid(1), lstParam.last() ); //lst.last() );
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("PART"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            if (data.count(":") < 2)
                emit IRC_LeftChannel( lstExcla.first().mid(1), lst.at(2), "No Message");
            else
                emit IRC_LeftChannel( lstExcla.first().mid(1), lst.at(2), data.mid(data.indexOf(tr(":"),1)+1) );
        }
        else if ( lst.size() > 4 && lst.at(1).compare(tr("MODE"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            emit IRC_ModeChange( lstExcla.first().mid(1), lst.at(2), lst.at(4), lst.at(3) );
        }
        else if ( lst.size() > 3 && lst.at(1).compare(tr("MODE"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            emit IRC_ModeChange( lstExcla.first().mid(1), lst.at(2), "", lst.at(3) );
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("NICK"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            emit IRC_NickChange( lstExcla.first().mid(1), data.mid(data.indexOf(tr(":"),1)+1) );
        }
        else if ( lst.size() > 3 && lst.at(1).compare(tr("KICK"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            if (lstExcla.first().mid(1).compare( getNick(), Qt::CaseInsensitive) == 0)
                lsChannels.removeOne(lst.last());
             emit IRC_Kick( lstExcla.first().mid(1), lst.at(2), lst.at(3), data.mid(data.indexOf(tr(":"),1)+1) );
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("QUIT"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            if (data.count(":") < 2)
                emit IRC_UserQuit(  lstExcla.first().mid(1), "No Message");
            else
                emit IRC_UserQuit( lstExcla.first().mid(1), data.mid(data.indexOf(tr(":"),1)+1) );
        }
        else if ( lst.size() > 2 && lst.at(1).compare(tr("PRIVMSG"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty() && lst.at(2).contains(tr("#")) )
        {
            if ( lstParam.last().contains( "ACTION" ) )
            {
                QString actionMessage = data.mid(data.indexOf(tr(":"),1)+1).mid(7);
                actionMessage.chop(1);
                emit IRC_ChannelMessage( lstExcla.first().mid(1), lst.at(2), actionMessage, true);
            }
            else
                emit IRC_ChannelMessage( lstExcla.first().mid(1), lst.at(2), data.mid(data.indexOf(tr(":"),1)+1), false);
        }
        else if ( lst.size() > 2 && lst.at(1).compare(tr("PRIVMSG"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty())
        {
            if ( lstParam.last().contains( "ACTION" ) )
            {
                QString actionMessage = data.mid(data.indexOf(tr(":"),1)+1).mid(7);
                actionMessage.chop(1);
                emit IRC_PrivateMessage( lstExcla.first().mid(1), actionMessage, true);
            }
            else
                emit IRC_PrivateMessage( lstExcla.first().mid(1), data.mid(data.indexOf(tr(":"),1)+1), false);
        }
        else if ( lst.size() > 4 && lst.at(1).compare(tr("353"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty()) //353   RPL_NAMREPLY
        {
            QStringList lstUsers = lstParam.last().split(tr(" "));
            emit IRC_UserList( lst.at(4), lstUsers);
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("332"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty()) //332  topic
        {
            emit  IRC_ChannelTopic( lst.at(3), data.mid(data.indexOf(tr(":"),1)+1));
        }
        else if ( lst.size() > 1 && lst.at(1).compare(tr("TOPIC"), Qt::CaseInsensitive) == 0 && !lstParam.isEmpty()) //  topic
        {
            emit  IRC_ChannelTopic( lst.at(2), data.mid(data.indexOf(tr(":"),1)+1));
        }
        else if ( lst.size() > 4 && lst.at(1).compare(tr("311"), Qt::CaseInsensitive) == 0 )
        {
            emit IRC_UserInfo( lst.at(3), lst.at(4) + " " + lst.at(5) + " " +  data.mid(data.indexOf(tr(":"),1)+1));
        }
        else if ( lstParam.size() > 2 && ( lst.at(1).compare(tr("372"), Qt::CaseInsensitive) == 0  || lst.at(1).compare(tr("NOTICE"), Qt::CaseInsensitive) == 0) )
        {
            emit IRC_MOTD_Line( lstParam.at(2) );
        }

        emit IRC_ServerMessage(data);
    }
}

void IRCConnection::displayError(QAbstractSocket::SocketError socketError)
{
       switch (socketError) {
       case QAbstractSocket::RemoteHostClosedError:
           break;
       case QAbstractSocket::HostNotFoundError:
           QMessageBox::information(NULL, tr("Flare IRC ") + szServer + " " + iPort,
                                    tr("The host was not found. Please check the "
                                       "host name and port settings."));
           break;
       case QAbstractSocket::ConnectionRefusedError:
           QMessageBox::information(NULL, tr("Flare IRC"),
                                    tr("The connection was refused by the peer. "
                                       "Make sure the fortune server is running, "
                                       "and check that the host name and port "
                                       "settings are correct."));
           break;
       default:
           QMessageBox::information(NULL, tr("Flare IRC"),
                                    tr("The following error occurred: %1.")
                                    .arg(qSocket->errorString()));
       }
}
