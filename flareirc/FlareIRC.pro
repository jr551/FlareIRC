# -------------------------------------------------
# Project created by QtCreator 2009-12-15T14:51:44
# -------------------------------------------------
QT += network \
    webengine \
    widgets
TARGET = GameChatPro
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    ircsocket.cpp
HEADERS += mainwindow.h \
    ircsocket.h
FORMS += mainwindow.ui
OTHER_FILES += FlareIRC.rc
RC_FILE = FlareIRC.rc
ICON = icon.icns
RESOURCES += flareirc.qrc
