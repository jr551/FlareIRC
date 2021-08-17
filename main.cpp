#include <QtGui/QApplication>
#include "connectwindow.h"




ConnectWindow *gConnectWindow = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("John Rowe");
    QCoreApplication::setApplicationName("FlareIRC");

    gConnectWindow = new ConnectWindow();
    gConnectWindow->show();

    return a.exec();
}
