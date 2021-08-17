#include "optionswindow.h"
#include "ui_optionswindow.h"
#include <QSettings>


OptionsWindow::OptionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);
    setWindowIcon (QIcon(":/icons/edit.png"));

    QSettings settings;
    ui->txtDefaultNick->setText( settings.value ( tr("DefaultNick"), QVariant(tr("MrNoNickName221")) ).toString() );
    ui->txtFullName->setText( settings.value ( tr("FullName"), QVariant(tr("FlareIRC C++ Client")) ).toString() );
    ui->txtPartMessage->setText( settings.value ( tr("PartMessage"), QVariant(tr("FlareIRC C++ Client")) ).toString() );
    ui->txtQuitMessage->setText( settings.value ( tr("QuitMessage"), QVariant(tr("FlareIRC C++ Client")) ).toString() );
    ui->chkInformChatClose->setChecked( settings.value ( tr("InformChatClose"), QVariant(true) ).toBool() );
    ui->txtIdentUsername->setText( settings.value ( tr("IdentUsername"), QVariant(tr("")) ).toString() );
    ui->txtIdentPassword->setText( settings.value ( tr("IdentPassword"), QVariant(tr("")) ).toString() );    
    ui->chkUseIdent->setChecked( settings.value ( tr("Use_Ident"), QVariant(false) ).toBool() );
    ui->chkNotifyChannelMsg->setChecked( settings.value ( tr("NotifyChanMsg"), QVariant(false) ).toBool() );
    ui->chkNotifyPrivMsg->setChecked( settings.value ( tr("NotifyPrivMsg"), QVariant(false) ).toBool() );
    ui->chkSoundChannelMsg->setChecked( settings.value ( tr("SoundChanMsg"), QVariant(false) ).toBool() );
    ui->chkSoundPrivMsg->setChecked( settings.value ( tr("SoundPrivMsg"), QVariant(false) ).toBool() );

    if (ui->chkUseIdent->isChecked())
        ui->grpIdent->setEnabled(true);
    else
        ui->grpIdent->setEnabled(false);
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::changeEvent(QEvent *e)
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

void OptionsWindow::on_btnCancel_clicked()
{
    close();
}

void OptionsWindow::on_btnSave_clicked()
{
    QSettings settings;

    settings.setValue( tr("DefaultNick"), QVariant( ui->txtDefaultNick->text() ) );
    settings.setValue( tr("FullName"), QVariant( ui->txtFullName->text() ) );
    settings.setValue( tr("PartMessage"), QVariant( ui->txtPartMessage->text() ) );
    settings.setValue( tr("QuitMessage"), QVariant( ui->txtQuitMessage->text() ) );
    settings.setValue( tr("InformChatClose"), QVariant( ui->chkInformChatClose->checkState() ) );
    settings.setValue( tr("IdentUsername"), QVariant( ui->txtIdentUsername->text() ) );
    settings.setValue( tr("IdentPassword"), QVariant(  ui->txtIdentPassword->text() ) );
    settings.setValue( tr("Use_Ident"), QVariant( ui->chkUseIdent->isChecked() ) );
    settings.setValue( tr("NotifyChanMsg"), QVariant( ui->chkNotifyChannelMsg->isChecked() ) );
    settings.setValue( tr("NotifyPrivMsg"), QVariant( ui->chkNotifyPrivMsg->isChecked() ) );
    settings.setValue( tr("SoundChanMsg"), QVariant( ui->chkSoundChannelMsg->isChecked() ) );
    settings.setValue( tr("SoundPrivMsg"), QVariant( ui->chkSoundPrivMsg->isChecked() ) );

    close();
}

void OptionsWindow::on_chkUseIdent_clicked()
{
    if (ui->chkUseIdent->isChecked())
        ui->grpIdent->setEnabled(true);
    else
        ui->grpIdent->setEnabled(false);

}
