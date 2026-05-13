#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtWebSockets/QWebSocket>
#else
#include <QWebSocket>
#endif
#include <QUrl>

enum WebSocketError
{
    ERR_CONNECTIONFAILED = 0,
    ERR_HANDSHAKEFAILED,
    ERR_AUTHFAILED,
    ERR_NICKNAMEINUSE,
    ERR_ERRONEUSNICKNAME,
    ERR_NONICKNAMEGIVEN,
    ERR_LAST
};

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QString server, int port, QString nick, QObject *parent = nullptr);
    ~WebSocketClient();

    void connect();
    void disconnect();
    void sendMessage(const QString &to, const QString &message, bool isPrivate = false);
    void sendJsonMessage(const QJsonObject &message);
    void joinChannel(const QString &channel);
    void leaveChannel(const QString &channel, const QString &quitMsg = QString());
    void changeNick(const QString &newNick);
    void requestPresence(const QString &channel);
    void requestUserList(const QString &channel);

    bool isConnected() const { return bConnected; }
    bool isInChannel(const QString &channel) const { return lsChannels.contains(channel); }
    QString getServer() const { return szServer; }
    QString getNick() const { return szNick; }
    QStringList getChannels() const { return lsChannels; }

signals:
    void connected();
    void disconnected();
    void readyForCommands();

    void channelMessage(const QString &source, const QString &channel, const QString &msg, bool action);
    void privateMessage(const QString &source, const QString &msg, bool action);
    void serverMessage(const QString &msg);

    void joinedChannel(const QString &source, const QString &channel);
    void leftChannel(const QString &source, const QString &channel, const QString &quitMsg);
    void userQuit(const QString &source, const QString &quitMsg);

    void nickChange(const QString &oldNick, const QString &newNick);

    void userList(const QString &channel, const QStringList &users);
    void channelTopic(const QString &channel, const QString &topic);
    void userInfo(const QString &user, const QString &data);
    void motdLine(const QString &line);

    void error(WebSocketError error);
    void socketError(QAbstractSocket::SocketError socketError);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &message);
    void onError(QAbstractSocket::SocketError error);
    void onStateChanged(QAbstractSocket::SocketState state);
    void onPing(const QByteArray &payload);
    void onPong(const QByteArray &payload);

private:
    void handleJsonMessage(const QJsonObject &json);
    void sendWebSocketMessage(const QJsonObject &json);
    QString buildJsonMessage(const QString &type, const QJsonObject &data = QJsonObject());
    QString buildChannelMessage(const QString &channel, const QString &message, bool isAction);
    QString buildPrivateMessage(const QString &to, const QString &message, bool isAction);
    QString buildJoinMessage(const QString &channel);
    QString buildPartMessage(const QString &channel, const QString &reason);
    QString buildNickMessage(const QString &nick);
    QString buildPingMessage();
    QString buildPongMessage(const QByteArray &payload);

    QString szServer;
    QString szNick;
    int iPort;
    QWebSocket *qSocket;
    bool bConnected;
    bool bReadyForCommands;
    QStringList lsChannels;

    static constexpr int WS_PORT_DEFAULT = 8080;
};

#endif // WEBSOCKETCLIENT_H
