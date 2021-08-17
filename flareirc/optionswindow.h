#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QMainWindow>

namespace Ui {
    class OptionsWindow;
}

class OptionsWindow : public QMainWindow {
    Q_OBJECT
public:
    OptionsWindow(QWidget *parent = 0);
    ~OptionsWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::OptionsWindow *ui;

private slots:
    void on_chkUseIdent_clicked();
    void on_btnSave_clicked();
    void on_btnCancel_clicked();
};

#endif // OPTIONSWINDOW_H
