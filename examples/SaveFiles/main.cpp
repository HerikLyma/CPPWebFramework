/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/savefilesservlet.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/SaveFiles/server"));

    server.addUrlServlet("/savefiles", new SaveFilesServlet);

    return server.start();
}
