#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = HelloWorld
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \     
    servlets/helloworldservlet.cpp

HEADERS += \    
    servlets/helloworldservlet.h

QMAKE_CXXFLAGS += -std=c++11

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3


OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

unix {
    INCLUDEPATH += /usr/lib
    LIBS += -L/usr/lib -lCPPWebFramework
}

macx {
    INCLUDEPATH += /usr/local/lib
    LIBS += -L/usr/local/lib -lCPPWebFramework
}

win32 {
    INCLUDEPATH += C:/
    LIBS += -LC:/Windows/System32 -lCPPWebFramework
}
