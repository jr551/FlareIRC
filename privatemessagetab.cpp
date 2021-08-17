#include "privatemessagetab.h"
#include "ui_privatemessagetab.h"

PrivateMessageTab::PrivateMessageTab(QWidget *parent, TalkWindow *pTalkWindow, QString talkingTo) :
    TalkWindowTab(parent),
    ui(new Ui::PrivateMessageTab)
{
    ui->setupUi(this);
    talkWindow = pTalkWindow;
    userTalkingTo = talkingTo;
    ui->txtChat->setFocus();
    talkWindow->SendRaw( "WHOIS " + talkingTo );
}

PrivateMessageTab::~PrivateMessageTab()
{
    delete ui;
}

void PrivateMessageTab::changeEvent(QEvent *e)
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

void PrivateMessageTab::UpdateUserInfo( QString infoString )
{
    ui->lblInfo->setText( infoString );
}

bool PrivateMessageTab::UpdateNick( QString oldNick, QString newNick )
{
    if ( userTalkingTo.compare(oldNick, Qt::CaseInsensitive) == 0 )
    {
        userTalkingTo = newNick;
        return true;
    }
    return false;
}

void PrivateMessageTab::AddChatLine( QString line )
{
    ui->txtMessages->append(line);
}

void PrivateMessageTab::LocalNickUpdated(QString nick)
{
    ui->txtMessages->append("<FONT COLOR='orange'>Your nickname changed to <b>" + nick + "</b></FONT>");
}

void PrivateMessageTab::on_txtChat_returnPressed()
{
    talkWindow->SendMessage(userTalkingTo, ui->txtChat->text() );
    ui->txtChat->clear();
}
