#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T20:29:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nethaqt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nethackscene.cpp \
    tileset.cpp \
    telnet.cpp

HEADERS  += mainwindow.h \
    nethackscene.h \
    tileset.h \
    telnet.h

FORMS    += mainwindow.ui

RESOURCES += \
    tileset.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libtelnet/release/ -ltelnet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libtelnet/debug/ -ltelnet
else:unix: LIBS += -L$$PWD/../libtelnet/ -ltelnet

INCLUDEPATH += $$PWD/../libtelnet
DEPENDPATH += $$PWD/../libtelnet

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libtelnet/release/libtelnet.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libtelnet/debug/libtelnet.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libtelnet/release/telnet.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libtelnet/debug/telnet.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libtelnet/libtelnet.a

INCLUDEPATH += $$PWD/../spdlog/include
