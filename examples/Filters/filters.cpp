/**
  @file filters.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/indexservlet.h>
#include <servlets/loginservlet.h>
#include <servlets/configurationservlet.h>
#include <filter/loginfilter.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/Filters/server"),
                                  new LoginFilter);

    server.addUrlServlet("/login", new LoginServlet);
    server.addUrlServlet("/index", new IndexServlet);
    server.addUrlServlet("/configuration", new ConfigurationServlet);

    return server.start();
}
