#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = SaveFiles
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../CPPWebFramework/cwf/configuration.cpp \
    ../../CPPWebFramework/cwf/cppwebapplication.cpp \
    ../../CPPWebFramework/cwf/cppwebserver.cpp \
    ../../CPPWebFramework/cwf/cppwebservlet.cpp \
    ../../CPPWebFramework/cwf/cstlcompiler.cpp \
    ../../CPPWebFramework/cwf/cstlcompilerattributes.cpp \
    ../../CPPWebFramework/cwf/cstlcompilerfor.cpp \
    ../../CPPWebFramework/cwf/cstlcompilerif.cpp \
    ../../CPPWebFramework/cwf/cstlcompilerobject.cpp \
    ../../CPPWebFramework/cwf/filemanager.cpp \
    ../../CPPWebFramework/cwf/filter.cpp \
    ../../CPPWebFramework/cwf/filterchain.cpp \
    ../../CPPWebFramework/cwf/httpcookie.cpp \
    ../../CPPWebFramework/cwf/httpparser.cpp \
    ../../CPPWebFramework/cwf/httpreadrequest.cpp \
    ../../CPPWebFramework/cwf/httpservlet.cpp \
    ../../CPPWebFramework/cwf/httpservletrequest.cpp \
    ../../CPPWebFramework/cwf/httpservletresponse.cpp \
    ../../CPPWebFramework/cwf/httpsession.cpp \
    ../../CPPWebFramework/cwf/metaclassparser.cpp \
    ../../CPPWebFramework/cwf/properties.cpp \
    ../../CPPWebFramework/cwf/qlistobject.cpp \
    ../../CPPWebFramework/cwf/requestdispatcher.cpp \
    ../../CPPWebFramework/cwf/sessionidgenerator.cpp \
    servlets/savefilesservlet.cpp \
    ../../CPPWebFramework/cwf/urlencoder.cpp \
    ../../CPPWebFramework/cwf/cstlcompilerimport.cpp

HEADERS += \    
    ../../CPPWebFramework/cwf/constants.h \
    ../../CPPWebFramework/cwf/configuration.h \
    ../../CPPWebFramework/cwf/cppwebapplication.h \
    ../../CPPWebFramework/cwf/cppwebserver.h \
    ../../CPPWebFramework/cwf/cppwebservlet.h \
    ../../CPPWebFramework/cwf/cstlcompiler.h \
    ../../CPPWebFramework/cwf/cstlcompilerattributes.h \
    ../../CPPWebFramework/cwf/cstlcompilerfor.h \
    ../../CPPWebFramework/cwf/cstlcompilerif.h \
    ../../CPPWebFramework/cwf/cstlcompilerobject.h \
    ../../CPPWebFramework/cwf/filemanager.h \
    ../../CPPWebFramework/cwf/filter.h \
    ../../CPPWebFramework/cwf/filterchain.h \
    ../../CPPWebFramework/cwf/httpcookie.h \
    ../../CPPWebFramework/cwf/httpparser.h \
    ../../CPPWebFramework/cwf/httpreadrequest.h \    
    ../../CPPWebFramework/cwf/httpservlet.h \
    ../../CPPWebFramework/cwf/httpservletrequest.h \
    ../../CPPWebFramework/cwf/httpservletresponse.h \
    ../../CPPWebFramework/cwf/httpsession.h \
    ../../CPPWebFramework/cwf/metaclassparser.h \
    ../../CPPWebFramework/cwf/properties.h \
    ../../CPPWebFramework/cwf/qlistobject.h \
    ../../CPPWebFramework/cwf/qmapthreadsafety.h \
    ../../CPPWebFramework/cwf/requestdispatcher.h \
    ../../CPPWebFramework/cwf/sessionidgenerator.h \
    servlets/savefilesservlet.h \
    ../../CPPWebFramework/cwf/urlencoder.h \
    ../../CPPWebFramework/cwf/cstlcompilerimport.h

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../../CPPWebFramework

OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/savefiles.xhtml
