#ifndef SERVERTAB_H
#define SERVERTAB_H

#include <QWidget>
#include "talkwindowtab.h"
#include "talkwindow.h"

namespace Ui {
    class ServerTab;
}
class TalkWindow;

class ServerTab : public TalkWindowTab {
    Q_OBJECT
public:
    // Qt makes you *need* a constructor which can be called like this.
    ServerTab(QWidget *parent = 0, TalkWindow *pTalkWindow = 0);
    ~ServerTab();

    void AddChatLine( QString line );

    virtual TalkWindowTabType_t GetTabType() { return SERVER_TAB; }
    virtual QString GetTabContext() { return tr("server"); }
    void LocalNickUpdated(QString nick){;}

    bool UpdateNick( QString oldNick, QString newNick ){return false;}
    void AddStatusLine( QString line, QIcon icon );
    void AddMOTDLine( QString line );
protected:
    void changeEvent(QEvent *e);

private:
    Ui::ServerTab *ui;
    TalkWindow *talkWindow;

private slots:
    void on_txtChat_returnPressed();
};

#endif // SERVERTAB_H
