/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/usersservlet.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/CSTLForExample/server"));


    server.addUrlServlet("/users", new UsersServlet);

    return server.start();
}
