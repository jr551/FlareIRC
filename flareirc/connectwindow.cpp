#include "connectwindow.h"
#include "ui_connectwindow.h"
#include "talkwindow.h"
#include "optionswindow.h"
#include <QSettings>
#include <QMessageBox>

ConnectWindow::ConnectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    setWindowIcon (QIcon(":/icons/globe.png"));
    QSettings settings;

    ui->txtNick->setText(  settings.value ( tr("DefaultNick"), QVariant(tr("MrNoNickName221")) ).toString() );
    ui->txtServer->setText(  settings.value ( tr("DefaultServer"), QVariant(tr("irc.gamesurge.net")) ).toString() );
    ui->txtChannels->setText(  settings.value ( tr("Channels"), QVariant(tr("#help #welcome")) ).toString() );
    ui->spnPort->setValue( settings.value( tr("DefaultPort"), QVariant(6667) ).toInt());
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void ConnectWindow::on_btnConnect_clicked()
{
    QSettings settings;
    settings.setValue( tr("DefaultNick"), QVariant( ui->txtNick->text() ));
    settings.setValue ( tr("DefaultServer"), QVariant(ui->txtServer->text()));
    settings.setValue ( tr("Channels"), QVariant(ui->txtChannels->text()));
    settings.setValue( tr("DefaultPort"), QVariant(ui->spnPort->value()));

    TalkWindow *win = new TalkWindow(NULL, ui->txtServer->text(), ui->spnPort->value(), ui->txtNick->text(), ui->txtChannels->text().split(' ') );
    win->show();
    QApplication::setActiveWindow(win);

    hide();
}

void ConnectWindow::on_btnCancel_clicked()
{
    exit(1);
}



void ConnectWindow::on_btnOptions_clicked()
{
    OptionsWindow *optWin = new OptionsWindow(this);
    optWin->show();
}
