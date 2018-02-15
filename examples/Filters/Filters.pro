#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = Filters
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    servlets/loginservlet.cpp \
    servlets/indexservlet.cpp \
    entities/user.cpp \
    filter/loginfilter.cpp

HEADERS += \    
    servlets/loginservlet.h \
    servlets/indexservlet.h \
    entities/user.h \
    filter/loginfilter.h 

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3



OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/log/CPPWebServer.log \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/index.xhtml \
    server/pages/login.xhtml


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
