#ifndef TALKWINDOWTAB_H
#define TALKWINDOWTAB_H

#include <QWidget>

class TalkWindowTab : public QWidget
{
Q_OBJECT
public:
    explicit TalkWindowTab(QWidget *parent = 0);
    enum TalkWindowTabType_t
    {
        SERVER_TAB = 0,
        CHANNEL_TAB,
        PRIVMSG_TAB
    };

    virtual TalkWindowTabType_t GetTabType() = 0;
    virtual QString GetTabContext() = 0;
    virtual void AddChatLine( QString line ) = 0;
    virtual bool UpdateNick( QString oldNick, QString newNick ) = 0;
    virtual void LocalNickUpdated( QString nick ) = 0;


signals:

public slots:

};

#endif // TALKWINDOWTAB_H
