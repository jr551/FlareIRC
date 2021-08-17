#include "servertab.h"
#include "ui_servertab.h"

ServerTab::ServerTab(QWidget *parent, TalkWindow *pTalkWindow) :
    TalkWindowTab(parent),
    ui(new Ui::ServerTab)
{
    ui->setupUi(this);
    talkWindow = pTalkWindow;

}

ServerTab::~ServerTab()
{
    delete ui;
}

void ServerTab::changeEvent(QEvent *e)
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


void ServerTab::AddChatLine( QString line )
{
    ui->txtMessages->append(line);
}

void ServerTab::AddMOTDLine( QString line )
{
    ui->txtMOTD->append(line);
}

void ServerTab::AddStatusLine( QString line, QIcon icon )
{
    ui->lstStatus->addItem( new QListWidgetItem(icon, line) );
}
void ServerTab::on_txtChat_returnPressed()
{
    talkWindow->SendRaw( ui->txtChat->text().toAscii() );
    ui->txtMessages->append("<b>"+ui->txtChat->text()+"</b>");
    ui->txtChat->clear();
}
