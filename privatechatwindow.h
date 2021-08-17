#ifndef PRIVATECHATWINDOW_H
#define PRIVATECHATWINDOW_H

#include <QDialog>

namespace Ui {
    class PrivateChatWindow;
}

class PrivateChatWindow : public QDialog {
    Q_OBJECT
public:
    PrivateChatWindow(QWidget *parent = 0);
    ~PrivateChatWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PrivateChatWindow *ui;
};

#endif // PRIVATECHATWINDOW_H
