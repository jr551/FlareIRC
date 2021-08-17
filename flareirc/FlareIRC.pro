# -------------------------------------------------
# Project created by QtCreator 2009-12-15T14:51:44
# -------------------------------------------------
QT += network \
    webkit \
    script
TARGET = FlareIRC
TEMPLATE = app
SOURCES += main.cpp \
    connectwindow.cpp \
    ircsocket.cpp \
    talkwindow.cpp \
    chattab.cpp \
    privatemessagetab.cpp \
    servertab.cpp \
    talkwindowtab.cpp \
    inputdialog.cpp \
    optionswindow.cpp \
    scriptmanager.cpp
HEADERS += connectwindow.h \
    ircsocket.h \
    talkwindow.h \
    chattab.h \
    privatemessagetab.h \
    servertab.h \
    talkwindowtab.h \
    inputdialog.h \
    optionswindow.h \
    scriptmanager.h
FORMS += connectwindow.ui \
    talkwindow.ui \
    chattab.ui \
    privatemessagetab.ui \
    servertab.ui \
    inputdialog.ui \
    optionswindow.ui
OTHER_FILES += FlareIRC.rc
RC_FILE = FlareIRC.rc
ICON = icon.icns
RESOURCES += flareirc.qrc
