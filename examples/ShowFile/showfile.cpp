/**
  @file showfile.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/showfileservlet.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/ShowFile/server"));

    server.addUrlServlet("/showfile", new ShowFileServlet);

    return server.start();
}
