#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QWidget>
#include <QIcon>
#include <QString>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *serverSidebar;
    QListWidget *serverList;
    QListWidget *channelList;
    QWidget *chatContainer;
    QWebEngineView *messageView;
    QLineEdit *messageInput;
    QPushButton *sendButton;

    void setupUI();
    void addNewServer(const QString &name, const QIcon &icon = QIcon());
    void addChannel(const QString &name, bool isVoice = false);
    void appendMessage(const QString &author, const QString &content);

private slots:
    void onSendMessage();
    void onChannelSelected(QListWidgetItem *item);
    void onServerSelected(QListWidgetItem *item);
};

#endif // MAINWINDOW_H