#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T22:39:30
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

TARGET = UnitTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
CONFIG  += c++11

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
    main.cpp \
    tests/tst_configuration.cpp \
    ../CPPWebFramework/cwf/configuration.cpp \
    ../CPPWebFramework/cwf/cppwebapplication.cpp \
    ../CPPWebFramework/cwf/cppwebserver.cpp \
    ../CPPWebFramework/cwf/cppwebservlet.cpp \
    ../CPPWebFramework/cwf/cstlcompiler.cpp \
    ../CPPWebFramework/cwf/cstlcompilerattributes.cpp \
    ../CPPWebFramework/cwf/cstlcompilerfor.cpp \
    ../CPPWebFramework/cwf/cstlcompilerif.cpp \
    ../CPPWebFramework/cwf/cstlcompilerimport.cpp \
    ../CPPWebFramework/cwf/cstlcompilerobject.cpp \
    ../CPPWebFramework/cwf/filemanager.cpp \
    ../CPPWebFramework/cwf/filter.cpp \
    ../CPPWebFramework/cwf/filterchain.cpp \
    ../CPPWebFramework/cwf/httpcookie.cpp \
    ../CPPWebFramework/cwf/httpparser.cpp \
    ../CPPWebFramework/cwf/httpreadrequest.cpp \
    ../CPPWebFramework/cwf/httpservlet.cpp \
    ../CPPWebFramework/cwf/httpservletrequest.cpp \
    ../CPPWebFramework/cwf/httpservletresponse.cpp \
    ../CPPWebFramework/cwf/httpsession.cpp \
    ../CPPWebFramework/cwf/metaclassparser.cpp \
    ../CPPWebFramework/cwf/properties.cpp \
    ../CPPWebFramework/cwf/qlistobject.cpp \
    ../CPPWebFramework/cwf/requestdispatcher.cpp \
    ../CPPWebFramework/cwf/sessionidgenerator.cpp \
    ../CPPWebFramework/cwf/urlencoder.cpp \
    tests/tst_cppwebapplication.cpp \
    tests/tst_cppwebserver.cpp \
    tests/tst_cppwebservlet.cpp \
    tests/tst_cstlcompiler.cpp \
    tests/tst_cstlcompilerattributes.cpp \
    tests/tst_cstlcompilerfor.cpp \
    tests/tst_cstlcompilerif.cpp \
    tests/tst_cstlcompilerimport.cpp \
    tests/tst_cstlcompilerobject.cpp \
    tests/tst_filemanager.cpp \
    tests/tst_filter.cpp \
    tests/tst_filterchain.cpp \
    tests/tst_httpcookie.cpp \
    tests/tst_httpparser.cpp \
    tests/tst_httpreadrequest.cpp \
    tests/tst_httpservletresponse.cpp \
    tests/tst_httpsession.cpp \
    tests/tst_metaclassparser.cpp \
    tests/tst_properties.cpp \
    tests/tst_qlistobject.cpp \
    tests/tst_qmapthreadsafety.cpp \
    tests/tst_requestdispatcher.cpp \
    tests/tst_sessionidgenerator.cpp \
    tests/tst_urlencoder.cpp \
    tests/tst_httprequestmethod.cpp \
    tests/tst_httpservletrequest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tests/tst_configuration.h \
    ../CPPWebFramework/cwf/configuration.h \
    ../CPPWebFramework/cwf/cppwebapplication.h \
    ../CPPWebFramework/cwf/cppwebserver.h \
    ../CPPWebFramework/cwf/cppwebservlet.h \
    ../CPPWebFramework/cwf/cstlcompiler.h \
    ../CPPWebFramework/cwf/cstlcompilerattributes.h \
    ../CPPWebFramework/cwf/cstlcompilerfor.h \
    ../CPPWebFramework/cwf/cstlcompilerif.h \
    ../CPPWebFramework/cwf/cstlcompilerimport.h \
    ../CPPWebFramework/cwf/cstlcompilerobject.h \
    ../CPPWebFramework/cwf/filemanager.h \
    ../CPPWebFramework/cwf/filter.h \
    ../CPPWebFramework/cwf/filterchain.h \
    ../CPPWebFramework/cwf/httpcookie.h \
    ../CPPWebFramework/cwf/httpparser.h \
    ../CPPWebFramework/cwf/httpreadrequest.h \
    ../CPPWebFramework/cwf/httprequestmethod.h \
    ../CPPWebFramework/cwf/httpservlet.h \
    ../CPPWebFramework/cwf/httpservletrequest.h \
    ../CPPWebFramework/cwf/httpservletresponse.h \
    ../CPPWebFramework/cwf/httpsession.h \
    ../CPPWebFramework/cwf/metaclassparser.h \
    ../CPPWebFramework/cwf/properties.h \
    ../CPPWebFramework/cwf/qlistobject.h \
    ../CPPWebFramework/cwf/qmapthreadsafety.h \
    ../CPPWebFramework/cwf/requestdispatcher.h \
    ../CPPWebFramework/cwf/sessionidgenerator.h \
    ../CPPWebFramework/cwf/urlencoder.h \
    tests/tst_cppwebapplication.h \
    tests/tst_cppwebserver.h \
    tests/tst_cppwebservlet.h \
    tests/tst_cstlcompiler.h \
    tests/tst_cstlcompilerattributes.h \
    tests/tst_cstlcompilerfor.h \
    tests/tst_cstlcompilerif.h \
    tests/tst_cstlcompilerimport.h \
    tests/tst_cstlcompilerobject.h \
    tests/tst_filemanager.h \
    tests/tst_filter.h \
    tests/tst_filterchain.h \
    tests/tst_httpcookie.h \
    tests/tst_httpparser.h \
    tests/tst_httpreadrequest.h \
    tests/tst_httpservletresponse.h \
    tests/tst_httpsession.h \
    tests/tst_metaclassparser.h \
    tests/tst_properties.h \
    tests/tst_qlistobject.h \
    tests/tst_qmapthreadsafety.h \
    tests/tst_requestdispatcher.h \
    tests/tst_sessionidgenerator.h \
    tests/tst_urlencoder.h \
    tests/tst_httprequestmethod.h \
    tests/tst_httpservletrequest.h

INCLUDEPATH += ../CPPWebFramework/

QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS   += -g -Wall -fprofile-arcs -ftest-coverage -O0
LIBS           += -lgcov
