/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include "cwf/cppwebapplication.h"
#include <servlets/userservlet.h>
#include <servlets/homeservlet.h>


int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/CSTLImportExample/server"));

    server.addUrlServlet("/user", new UserServlet);
    server.addUrlServlet("/home", new HomeServlet);

    return server.start();
}
