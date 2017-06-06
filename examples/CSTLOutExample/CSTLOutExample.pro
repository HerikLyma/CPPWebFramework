#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = CSTLOutExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \         
    entities/user.cpp \
    servlets/userservlet.cpp


HEADERS += \            
    entities/user.h \
    servlets/userservlet.h


QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../../CPPWebFramework

OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/user.xhtml

LIBS += -lCPPWebFramework
