
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Xml REQUIRED)

include_directories("cwf/")

set(CPP_WebFrameWork_SRCS
    cwf/configuration.cpp
    cwf/cppwebapplication.cpp
    cwf/cppwebserver.cpp
    cwf/cstlcompiler.cpp
    cwf/cstlcompilerattributes.cpp
    cwf/cstlcompilerfor.cpp
    cwf/cstlcompilerif.cpp
    cwf/cstlcompilerimport.cpp
    cwf/filemanager.cpp
    cwf/filterchain.cpp
    cwf/filter.cpp
    cwf/httpparser.cpp
    cwf/httpreadrequest.cpp
    cwf/metaclassparser.cpp
    cwf/properties.cpp
    cwf/qlistobject.cpp
    cwf/requestdispatcher.cpp
    cwf/urlencoder.cpp
    cwf/sqlquery.cpp
    cwf/response.cpp
    cwf/request.cpp
    cwf/controller.cpp
    cwf/session.cpp
    cwf/cppwebcontroller.cpp
    cwf/sslloader.cpp
    cwf/cstlcompilerobject.h
    cwf/variant.h
    )

add_library(CPPWebFramework SHARED ${CPP_WebFrameWork_SRCS} )

target_link_libraries(
    CPPWebFramework
    Qt5::Core
    Qt5::Network
    Qt5::Xml
    Qt5::Sql

)

add_definitions(-DCPPWEBFRAMEWORK_LIBRARY)
