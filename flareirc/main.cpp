#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("GameChat");
    QCoreApplication::setApplicationName("GameChatPro");

    MainWindow *win = new MainWindow();
    win->show();

    return a.exec();
}
