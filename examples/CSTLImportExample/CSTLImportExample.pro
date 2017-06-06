#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = CSTLImportExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \         
    entities/user.cpp \
    servlets/userservlet.cpp \    
    servlets/homeservlet.cpp

HEADERS += \    
    entities/user.h \
    servlets/userservlet.h \    
    servlets/homeservlet.h

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../../CPPWebFramework

OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/user.xhtml \
    server/pages/home.xhtml \
    server/pages/footer.html \
    server/pages/header.html \
    server/pages/css/menu.css

LIBS += -lCPPWebFramework
