/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/indexservlet.h>
#include <servlets/loginservlet.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/Sessions/server"));

    server.addUrlServlet("/login", new LoginServlet);
    server.addUrlServlet("/index", new IndexServlet);

    return server.start();
}
