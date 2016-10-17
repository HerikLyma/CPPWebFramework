/**
  @file cstloutexample.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/userservlet.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/CSTLOutExample/server"));


    server.addUrlServlet("/user", new UserServlet);

    return server.start();
}
