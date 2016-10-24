#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T19:13:29
#
#-------------------------------------------------

QT       += core network xml

QT       -= gui

TARGET = CPPWebFramework
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cwf/configuration.cpp \
    cwf/cppwebserver.cpp \
    cwf/httpservlet.cpp \
    cwf/httpservletrequest.cpp \
    cwf/httpservletresponse.cpp \
    cwf/httpcookie.cpp \
    cwf/httpsession.cpp \
    cwf/httpparser.cpp \
    cwf/requestdispatcher.cpp \
    cwf/filter.cpp \
    cwf/filterchain.cpp \
    cwf/qlistobject.cpp \
    cwf/cstlcompiler.cpp \   
    cwf/properties.cpp \
    cwf/httpreadrequest.cpp \
    cwf/sessionidgenerator.cpp \
    cwf/cppwebapplication.cpp \
    cwf/filemanager.cpp \
    cwf/cppwebservlet.cpp \
    cwf/cstlcompilerattributes.cpp \
    cwf/cstlcompilerfor.cpp \
    cwf/cstlcompilerif.cpp \
    cwf/cstlcompilerobject.cpp \
    cwf/metaclassparser.cpp

HEADERS += \
    cwf/configuration.h \
    cwf/cppwebserver.h \
    cwf/httpservlet.h \
    cwf/httpservletrequest.h \
    cwf/httpservletresponse.h \
    cwf/httpcookie.h \
    cwf/httpsession.h \
    cwf/httpparser.h \
    cwf/requestdispatcher.h \
    cwf/filter.h \
    cwf/filterchain.h \
    cwf/httprequestmethod.h \
    cwf/qlistobject.h \
    cwf/qmapthreadsafety.h \
    cwf/cstlcompiler.h \
    cwf/properties.h \
    cwf/httpreadrequest.h \
    cwf/sessionidgenerator.h \
    cwf/cppwebapplication.h \
    cwf/filemanager.h \
    cwf/cppwebservlet.h \
    cwf/cstlcompilerattributes.h \
    cwf/cstlcompilerfor.h \
    cwf/cstlcompilerif.h \
    cwf/cstlcompilerobject.h \
    cwf/metaclassparser.h

QMAKE_CXXFLAGS += -std=c++11



OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log
