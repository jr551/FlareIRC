#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWebEngineView>
#include <QWebChannel>
#include <QSplitter>
#include <QScrollBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();

    addNewServer("GameChat", QIcon(":/icons/globe.png"));
    addNewServer("Gaming", QIcon(":/icons/icon_blue.png"));
    addNewServer("Social", QIcon(":/icons/icon_red.png"));

    addChannel("#general");
    addChannel("#games");
    addChannel("#help");

    messageView->setHtml("<html><body style='font-family: Arial, sans-serif; margin: 10px;'></body></html>");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(mainLayout);

    serverSidebar = new QWidget(this);
    serverSidebar->setMinimumWidth(60);
    serverSidebar->setMaximumWidth(60);
    serverSidebar->setStyleSheet("background-color: #202225;");

    QVBoxLayout *serverLayout = new QVBoxLayout(serverSidebar);
    serverLayout->setContentsMargins(5, 10, 5, 10);
    serverLayout->setSpacing(10);

    serverList = new QListWidget(serverSidebar);
    serverList->setStyleSheet(
        "QListWidget { background-color: transparent; border: none; }"
        "QListWidget::item { background-color: #36393F; border-radius: 15px; margin: 5px; }"
        "QListWidget::item:selected { background-color: #5865F2; }"
        "QListWidget::item:hover { background-color: #40444B; }"
    );
    serverList->setIconSize(QSize(36, 36));
    serverList->setSpacing(5);

    serverLayout->addWidget(serverList);
    serverLayout->addStretch();

    connect(serverList, &QListWidget::itemClicked, this, &MainWindow::onServerSelected);

    QSplitter *middleSplitter = new QSplitter(Qt::Horizontal);

    channelList = new QListWidget();
    channelList->setMinimumWidth(200);
    channelList->setMaximumWidth(240);
    channelList->setStyleSheet(
        "QListWidget { background-color: #2F3136; border: none; color: #B9BBBE; }"
        "QListWidget::item { padding: 5px; }"
        "QListWidget::item:selected { background-color: #36393F; color: white; }"
        "QListWidget::item:hover { background-color: #34363C; }"
    );

    QStringList categories;
    categories << "TEXT CHANNELS" << "VOICE CHANNELS";

    chatContainer = new QWidget();
    QVBoxLayout *chatLayout = new QVBoxLayout(chatContainer);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    chatLayout->setSpacing(0);

    messageView = new QWebEngineView();
    messageView->setUrl(QUrl("about:blank"));
    messageView->setStyleSheet("background-color: #36393F;");
    messageView->page()->setBackgroundColor(Qt::transparent);

    messageInput = new QLineEdit();
    messageInput->setPlaceholderText("Type your message...");
    messageInput->setStyleSheet(
        "QLineEdit { background-color: #40444B; color: white; border: none; padding: 10px; border-radius: 5px; }"
    );

    sendButton = new QPushButton("Send");
    sendButton->setStyleSheet(
        "QPushButton { background-color: #5865F2; color: white; border: none; padding: 8px 16px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #4752C4; }"
    );

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    chatLayout->addWidget(messageView);
    chatLayout->addLayout(inputLayout);

    middleSplitter->addWidget(channelList);
    middleSplitter->addWidget(chatContainer);
    middleSplitter->setStretchFactor(1, 1);

    connect(channelList, &QListWidget::itemClicked, this, &MainWindow::onChannelSelected);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &MainWindow::onSendMessage);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(serverSidebar);
    mainSplitter->addWidget(middleSplitter);
    mainSplitter->setStretchFactor(1, 1);

    mainLayout->addWidget(mainSplitter);

    resize(1000, 600);
}

void MainWindow::addNewServer(const QString &name, const QIcon &icon)
{
    QListWidgetItem *item = new QListWidgetItem(icon, "");
    item->setToolTip(name);
    item->setTextAlignment(Qt::AlignCenter);
    serverList->addItem(item);
}

void MainWindow::addChannel(const QString &name, bool isVoice)
{
    QListWidgetItem *item = new QListWidgetItem(name);
    item->setIcon(isVoice ? QIcon(":/icons/voice.png") : QIcon(":/icons/channel_chat.png"));
    channelList->addItem(item);
}

void MainWindow::appendMessage(const QString &author, const QString &content)
{
    QString currentHtml = messageView->page()->toHtml();
    QString newMessage = QString(
        "<div style='margin: 8px 0; padding: 0 15px;'>"
        "<span style='color: #5865F2; font-weight: bold;'>%1</span>"
        "<span style='color: #B9BBBE; margin-left: 10px;'>%2</span>"
        "</div>"
    ).arg(author).arg(content);

    QString updatedHtml = currentHtml.replace("</body>", newMessage + "</body>");
    messageView->setHtml(updatedHtml);
}

void MainWindow::onSendMessage()
{
    QString text = messageInput->text().trimmed();
    if (!text.isEmpty()) {
        appendMessage("You", text);
        messageInput->clear();
    }
}

void MainWindow::onChannelSelected(QListWidgetItem *item)
{
    messageView->setHtml("<html><body style='font-family: Arial, sans-serif; margin: 10px; color: #B9BBBE;'></body></html>");
    messageInput->setPlaceholderText("Type your message in " + item->text() + "...");
}

void MainWindow::onServerSelected(QListWidgetItem *item)
{
    channelList->clear();
    addChannel("#general");
    addChannel("#games");
    addChannel("#voice-chat", true);
}