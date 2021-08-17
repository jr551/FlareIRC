#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ConnectWindow;
}

class ConnectWindow : public QMainWindow {
    Q_OBJECT
public:
    ConnectWindow(QWidget *parent = 0);
    ~ConnectWindow();

protected:
    void changeEvent(QEvent *e);

private:

    Ui::ConnectWindow *ui;

private slots:
    void on_btnOptions_clicked();
    void on_btnCancel_clicked();
    void on_btnConnect_clicked();
};

#endif // CONNECTWINDOW_H
