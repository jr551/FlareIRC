#include "websocketclient.h"
#include <QJsonParseError>
#include <QTimer>
#include <QDateTime>

WebSocketClient::WebSocketClient(QString server, int port, QString nick, QObject *parent)
    : QObject(parent),
      szServer(std::move(server)),
      szNick(std::move(nick)),
      iPort(port),
      qSocket(new QWebSocket()),
      bConnected(false),
      bReadyForCommands(false)
{
    connect(qSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(qSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(qSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(qSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketClient::onBinaryMessageReceived);
    connect(qSocket, &QWebSocket::errorOccurred, this, &WebSocketClient::onError);
    connect(qSocket, &QWebSocket::stateChanged, this, &WebSocketClient::onStateChanged);
    connect(qSocket, &QWebSocket::pong, this, &WebSocketClient::onPong);
    connect(qSocket, &QWebSocket::ping, this, &WebSocketClient::onPing);
}

WebSocketClient::~WebSocketClient()
{
    disconnect();
    qSocket->deleteLater();
}

void WebSocketClient::connect()
{
    if (bConnected) {
        return;
    }

    QString urlString = QString("ws://%1:%2").arg(szServer).arg(iPort);
    QUrl url(urlString);
    qSocket->open(url);
}

void WebSocketClient::disconnect()
{
    if (bConnected) {
        qSocket->close();
    }
}

void WebSocketClient::sendMessage(const QString &to, const QString &message, bool isPrivate)
{
    if (!bConnected) {
        return;
    }

    if (isPrivate) {
        sendJsonMessage(QJsonObject{
            {"type", "private_message"},
            {"to", to},
            {"message", message},
            {"from", szNick},
            {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
        });
    } else {
        sendJsonMessage(QJsonObject{
            {"type", "channel_message"},
            {"channel", to},
            {"message", message},
            {"from", szNick},
            {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
        });
    }
}

void WebSocketClient::sendJsonMessage(const QJsonObject &message)
{
    if (!bConnected) {
        return;
    }

    QJsonDocument doc(message);
    qSocket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

void WebSocketClient::joinChannel(const QString &channel)
{
    if (!bConnected || isInChannel(channel)) {
        return;
    }

    lsChannels.append(channel);
    sendJsonMessage(QJsonObject{
        {"type", "join"},
        {"channel", channel},
        {"nick", szNick},
        {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
    });
}

void WebSocketClient::leaveChannel(const QString &channel, const QString &quitMsg)
{
    if (!bConnected || !isInChannel(channel)) {
        return;
    }

    lsChannels.removeOne(channel);
    QJsonObject msg{
        {"type", "part"},
        {"channel", channel},
        {"nick", szNick},
        {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
    };
    if (!quitMsg.isEmpty()) {
        msg["reason"] = quitMsg;
    }
    sendJsonMessage(msg);
}

void WebSocketClient::changeNick(const QString &newNick)
{
    if (!bConnected || newNick.isEmpty() || newNick == szNick) {
        return;
    }

    QString oldNick = szNick;
    szNick = newNick;

    sendJsonMessage(QJsonObject{
        {"type", "nick"},
        {"old_nick", oldNick},
        {"new_nick", newNick},
        {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
    });

    emit nickChange(oldNick, newNick);
}

void WebSocketClient::requestPresence(const QString &channel)
{
    if (!bConnected) {
        return;
    }

    sendJsonMessage(QJsonObject{
        {"type", "presence_request"},
        {"channel", channel},
        {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
    });
}

void WebSocketClient::requestUserList(const QString &channel)
{
    if (!bConnected) {
        return;
    }

    sendJsonMessage(QJsonObject{
        {"type", "user_list_request"},
        {"channel", channel},
        {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
    });
}

void WebSocketClient::onConnected()
{
    bConnected = true;
    bReadyForCommands = true;

    emit connected();
    emit readyForCommands();

    sendJsonMessage(QJsonObject{
        {"type", "identify"},
        {"nick", szNick},
        {"timestamp", QDateTime::currentDateTimeUtc().toString(Qt::ISODate)}
    });
}

void WebSocketClient::onDisconnected()
{
    bConnected = false;
    bReadyForCommands = false;
    lsChannels.clear();

    emit disconnected();
}

void WebSocketClient::onTextMessageReceived(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error == QJsonParseError::NoError) {
        if (doc.isObject()) {
            handleJsonMessage(doc.object());
        }
    } else {
        emit serverMessage(tr("Parse error: ") + parseError.errorString());
    }
}

void WebSocketClient::onBinaryMessageReceived(const QByteArray &message)
{
    Q_UNUSED(message)
    // Binary messages not expected for JSON-based protocol
}

void WebSocketClient::onError(QAbstractSocket::SocketError error)
{
    emit socketError(error);

    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        emit error(ERR_CONNECTIONFAILED);
        break;
    case QAbstractSocket::RemoteHostClosedError:
        // Handled by disconnected signal
        break;
    default:
        emit error(ERR_CONNECTIONFAILED);
        break;
    }
}

void WebSocketClient::onStateChanged(QAbstractSocket::SocketState state)
{
    Q_UNUSED(state)
    // State change handling if needed
}

void WebSocketClient::onPing(const QByteArray &payload)
{
    qSocket->sendPong(payload);
}

void WebSocketClient::onPong(const QByteArray &payload)
{
    Q_UNUSED(payload)
    // Pong received - can be used for latency tracking
}

void WebSocketClient::handleJsonMessage(const QJsonObject &json)
{
    QString type = json.value("type").toString();

    if (type == "channel_message") {
        QString from = json.value("from").toString();
        QString channel = json.value("channel").toString();
        QString message = json.value("message").toString();
        bool isAction = json.value("action").toBool(false);
        emit channelMessage(from, channel, message, isAction);
    }
    else if (type == "private_message") {
        QString from = json.value("from").toString();
        QString message = json.value("message").toString();
        bool isAction = json.value("action").toBool(false);
        emit privateMessage(from, message, isAction);
    }
    else if (type == "server_message" || type == "motd") {
        QString msg = json.value("message").toString();
        emit serverMessage(msg);
    }
    else if (type == "join") {
        QString source = json.value("nick").toString();
        QString channel = json.value("channel").toString();
        emit joinedChannel(source, channel);
    }
    else if (type == "part") {
        QString source = json.value("nick").toString();
        QString channel = json.value("channel").toString();
        QString reason = json.value("reason").toString();
        emit leftChannel(source, channel, reason);
    }
    else if (type == "quit") {
        QString source = json.value("nick").toString();
        QString reason = json.value("reason").toString();
        emit userQuit(source, reason);
    }
    else if (type == "nick") {
        QString oldNick = json.value("old_nick").toString();
        QString newNick = json.value("new_nick").toString();
        emit nickChange(oldNick, newNick);
    }
    else if (type == "user_list") {
        QString channel = json.value("channel").toString();
        QStringList users;
        QJsonArray usersArray = json.value("users").toArray();
        for (const QJsonValue &val : usersArray) {
            users.append(val.toString());
        }
        emit userList(channel, users);
    }
    else if (type == "topic") {
        QString channel = json.value("channel").toString();
        QString topic = json.value("topic").toString();
        emit channelTopic(channel, topic);
    }
    else if (type == "user_info") {
        QString user = json.value("user").toString();
        QString info = json.value("info").toString();
        emit userInfo(user, info);
    }
    else if (type == "presence") {
        QString channel = json.value("channel").toString();
        QStringList users;
        QJsonArray usersArray = json.value("users").toArray();
        for (const QJsonValue &val : usersArray) {
            users.append(val.toString());
        }
        emit userList(channel, users);
    }
    else if (type == "ready") {
        emit readyForCommands();
    }
    else if (type == "error") {
        QString errorType = json.value("error_type").toString();
        if (errorType == "nick_in_use") {
            emit error(ERR_NICKNAMEINUSE);
        } else if (errorType == "erroneous_nick") {
            emit error(ERR_ERRONEUSNICKNAME);
        } else if (errorType == "no_nick_given") {
            emit error(ERR_NONICKNAMEGIVEN);
        } else {
            emit error(ERR_CONNECTIONFAILED);
        }
    }
}
