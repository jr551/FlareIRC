#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent, QString title, QString message, QString inputDefVal) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    setWindowTitle( title );
    ui->lblMessage->setText( message );
    ui->txtInput->setText( inputDefVal );
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::changeEvent(QEvent *e)
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

void InputDialog::on_btnOK_clicked()
{
    emit OK_Clicked( ui->txtInput->text() );
    close();
}
