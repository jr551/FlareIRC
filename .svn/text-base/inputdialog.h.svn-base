#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
    class InputDialog;
}

class InputDialog : public QDialog {
    Q_OBJECT
public:
    // Qt makes you *need* a constructor which can be called like this.
    InputDialog(QWidget *parent = 0, QString title = tr("null"), QString message= tr("null"), QString inputDefVal= tr("null"));
    ~InputDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::InputDialog *ui;

private slots:
    void on_btnOK_clicked();

signals:
    void OK_Clicked( QString value );
};

#endif // INPUTDIALOG_H
