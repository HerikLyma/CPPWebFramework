#-------------------------------------------------
#
# Project created by QtCreator 2017-06-05T23:53:17
#
#-------------------------------------------------

QT       += network xml sql
QT       -= gui

TEMPLATE = lib

DEFINES += CPPWEBFRAMEWORK_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cwf/configuration.cpp \
    cwf/cppwebapplication.cpp \
    cwf/cppwebserver.cpp \
    cwf/cstlcompiler.cpp \
    cwf/cstlcompilerattributes.cpp \
    cwf/cstlcompilerfor.cpp \
    cwf/cstlcompilerif.cpp \
    cwf/cstlcompilerimport.cpp \
    cwf/filemanager.cpp \
    cwf/filterchain.cpp \
    cwf/httpparser.cpp \
    cwf/httpreadrequest.cpp \
    cwf/metaclassparser.cpp \
    cwf/properties.cpp \
    cwf/qlistobject.cpp \
    cwf/requestdispatcher.cpp \
    cwf/urlencoder.cpp \
    cwf/sqlquery.cpp \
    cwf/response.cpp \
    cwf/request.cpp \
    cwf/controller.cpp \
    cwf/session.cpp \
    cwf/cppwebcontroller.cpp \
    cwf/sslloader.cpp \
    cwf/filter.cpp \
    cwf/model.cpp \
    cwf/modelbasicoperation.cpp \
    cwf/sqlquerymanager.cpp

HEADERS += \
    cwf/cppwebframework_global.h \
    cwf/configuration.h \
    cwf/constants.h \
    cwf/cppwebapplication.h \
    cwf/cppwebframework_global.h \
    cwf/cppwebserver.h \
    cwf/cstlcompiler.h \
    cwf/cstlcompilerattributes.h \
    cwf/cstlcompilerfor.h \
    cwf/cstlcompilerif.h \
    cwf/cstlcompilerimport.h \
    cwf/cstlcompilerobject.h \
    cwf/filemanager.h \
    cwf/filter.h \
    cwf/filterchain.h \
    cwf/httpparser.h \
    cwf/httpreadrequest.h \
    cwf/metaclassparser.h \
    cwf/properties.h \
    cwf/qlistobject.h \
    cwf/qmapthreadsafety.h \
    cwf/requestdispatcher.h \
    cwf/urlencoder.h \
    cwf/variant.h \
    cwf/sqldatabasestorage.h \
    cwf/sqlquery.h \
    cwf/controller.h \
    cwf/request.h \
    cwf/response.h \
    cwf/session.h \
    cwf/cppwebcontroller.h \
    cwf/sslloader.h \
    cwf/model.h \
    cwf/modelbasicoperation.h \
    cwf/sqlquerymanager.h

DISTFILES += \
    server/config/ssl/my.key \
    server/config/ssl/my.cert \
    server/config/cppwebserverpages/403.view \
    server/config/cppwebserverpages/404.view \
    server/config/cppwebserverpages/index.view \
    server/config/cppwebserverpages/resources/images/logo.jpg \
    server/config/cppwebserverpages/resources/images/favicon.ico \
    server/config/cppwebserverpages/resources/css/cppweb.css \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

unix {
    headers.path   = /usr/lib/cwf
    headers.files += $$HEADERS
    target.path    = /usr/lib
    config.path    = /usr/lib/server
    config.files   = server/*
}

macx {
    headers.path   = /usr/local/lib/cwf
    headers.files += $$HEADERS
    target.path    = /usr/local/lib
    config.path    = /usr/local/lib/server
    config.files   = server/*
}

win32 {
    headers.path   = C:/cwf
    headers.files += $$HEADERS
    target.path    = C:/cwf
    config.path    = C:/cwf/server
    config.files   = server/*
}

CONFIG += debug_and_release
CONFIG += build_all

CONFIG(debug, debug|release) {
    TARGET = CPPWebFrameworkd
} else {
    TARGET = CPPWebFramework
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3
}

INSTALLS += target
INSTALLS += headers
INSTALLS += config

QMAKE_CXXFLAGS += -std=c++11

#Strongly recommended
#LIBS += -ljemalloc
