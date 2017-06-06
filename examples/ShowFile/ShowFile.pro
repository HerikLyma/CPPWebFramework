#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T11:14:10
#
#-------------------------------------------------

QT       += core network xml

TARGET = ShowFile
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \     
    servlets/showfileservlet.cpp

HEADERS += \    
    servlets/showfileservlet.h \
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
    ../../CPPWebFramework/cwf/urlencoder.h \
    ../../CPPWebFramework/cwf/cstlcompilerimport.h \
    ../../CPPWebFramework/cwf/cppwebframework_global.h

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../../CPPWebFramework

OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/showfile.xhtml

LIBS += -lCPPWebFramework
