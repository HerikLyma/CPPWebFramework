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


SOURCES += cstloutexample.cpp \     
    cwf/configuration.cpp \
    cwf/cppwebapplication.cpp \
    cwf/cppwebserver.cpp \
    cwf/cppwebservlet.cpp \
    cwf/cstlcompiler.cpp \
    cwf/cstlcompilerattributes.cpp \
    cwf/cstlcompilerfor.cpp \
    cwf/cstlcompilerif.cpp \
    cwf/cstlcompilerobject.cpp \
    cwf/filemanager.cpp \
    cwf/filter.cpp \
    cwf/filterchain.cpp \    
    cwf/httpcookie.cpp \
    cwf/httpparser.cpp \
    cwf/httpreadrequest.cpp \
    cwf/httpservlet.cpp \
    cwf/httpservletrequest.cpp \
    cwf/httpservletresponse.cpp \
    cwf/httpsession.cpp \
    cwf/metaclassparser.cpp \
    cwf/properties.cpp \
    cwf/qlistobject.cpp \
    cwf/requestdispatcher.cpp \
    cwf/sessionidgenerator.cpp \
    entities/user.cpp \
    servlets/userservlet.cpp \
    cwf/urlencoder.cpp

HEADERS += \        
    cwf/configuration.h \
    cwf/cppwebapplication.h \
    cwf/cppwebserver.h \
    cwf/cppwebservlet.h \
    cwf/cstlcompiler.h \
    cwf/cstlcompilerattributes.h \
    cwf/cstlcompilerfor.h \
    cwf/cstlcompilerif.h \
    cwf/cstlcompilerobject.h \
    cwf/filemanager.h \
    cwf/filter.h \
    cwf/filterchain.h \
    cwf/httpcookie.h \
    cwf/httpparser.h \
    cwf/httpreadrequest.h \
    cwf/httprequestmethod.h \
    cwf/httpservlet.h \
    cwf/httpservletrequest.h \
    cwf/httpservletresponse.h \
    cwf/httpsession.h \    
    cwf/metaclassparser.h \
    cwf/properties.h \
    cwf/qlistobject.h \
    cwf/qmapthreadsafety.h \
    cwf/requestdispatcher.h \
    cwf/sessionidgenerator.h \
    entities/user.h \
    servlets/userservlet.h \
    cwf/urlencoder.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/log/CPPWebServer.log \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/user.xhtml
