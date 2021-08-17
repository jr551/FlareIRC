#ifndef PRIVATEMESSAGETAB_H
#define PRIVATEMESSAGETAB_H

#include <QWidget>
#include "talkwindow.h"
#include "talkwindowtab.h"

namespace Ui {
    class PrivateMessageTab;
}

class TalkWindow;

class PrivateMessageTab : public TalkWindowTab {
    Q_OBJECT
public:
    PrivateMessageTab(QWidget *parent = 0, TalkWindow *pTalkWindow = 0, QString talkingTo = tr("null"));
    ~PrivateMessageTab();
    void AddChatLine( QString line );

    TalkWindowTabType_t GetTabType() { return PRIVMSG_TAB; }
    QString GetTabContext() { return userTalkingTo; }
    bool UpdateNick( QString oldNick, QString newNick );

    void UpdateUserInfo( QString infoString );
    void LocalNickUpdated(QString nick);

protected:
    void changeEvent(QEvent *e);

private:
    TalkWindow *talkWindow;
    QString userTalkingTo;
    Ui::PrivateMessageTab *ui;

private slots:
    void on_txtChat_returnPressed();
};

#endif // PRIVATEMESSAGETAB_H
