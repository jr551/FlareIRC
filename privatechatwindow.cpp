#include "privatechatwindow.h"
#include "ui_privatechatwindow.h"

PrivateChatWindow::PrivateChatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrivateChatWindow)
{
    ui->setupUi(this);
}

PrivateChatWindow::~PrivateChatWindow()
{
    delete ui;
}

void PrivateChatWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
