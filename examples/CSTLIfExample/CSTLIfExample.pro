#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = CSTLIfExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \     
    entities/user.cpp \
    servlets/usersservlet.cpp

HEADERS += \            
    entities/user.h \
    servlets/usersservlet.h

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../../CPPWebFramework

OTHER_FILES += \
    server/config/CPPWeb.ini \    
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/users.xhtml

LIBS += -lCPPWebFramework
