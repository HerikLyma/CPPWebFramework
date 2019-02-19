QT -= gui
QT += xml network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp

OTHER_FILES += \
    server/config/CPPWeb.ini \
    server/config/log/CPPWebServer.log

DISTFILES += \
    server/pages/savefiles.xhtml


unix {
    INCLUDEPATH += /usr/lib
    debug {
        LIBS += -L/usr/lib -lCPPWebFrameworkd
    }
    release {
        LIBS += -L/usr/lib -lCPPWebFramework
    }
}

macx {
    INCLUDEPATH += /usr/local/lib
    debug {
        LIBS += -L/usr/local/lib -lCPPWebFrameworkd
    }
    release {
        LIBS += -L/usr/local/lib -lCPPWebFramework
    }
}

win32 {
    INCLUDEPATH += C:/
    debug {
        LIBS += -LC:/cwf -lCPPWebFrameworkd
    }
    release {
        LIBS += -LC:/cwf -lCPPWebFramework
    }
}

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3
}

#Strongly recommended
#LIBS += -ljemalloc
