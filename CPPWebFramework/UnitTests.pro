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
    cwf/configuration.cpp \
    cwf/cppwebapplication.cpp \
    cwf/cppwebserver.cpp \
    cwf/cppwebservlet.cpp \
    cwf/cstlcompiler.cpp \
    cwf/cstlcompilerattributes.cpp \
    cwf/cstlcompilerfor.cpp \
    cwf/cstlcompilerif.cpp \
    cwf/cstlcompilerimport.cpp \
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
    cwf/urlencoder.cpp \
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
    cwf/configuration.h \
    cwf/cppwebapplication.h \
    cwf/cppwebserver.h \
    cwf/cppwebservlet.h \
    cwf/cstlcompiler.h \
    cwf/cstlcompilerattributes.h \
    cwf/cstlcompilerfor.h \
    cwf/cstlcompilerif.h \
    cwf/cstlcompilerimport.h \
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
    cwf/urlencoder.h \
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

QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS   += -g -Wall -fprofile-arcs -ftest-coverage -O0
LIBS           += -lgcov
