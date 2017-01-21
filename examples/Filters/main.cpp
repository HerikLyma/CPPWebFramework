/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <filter/loginfilter.h>
#include <cwf/cppwebapplication.h>
#include <servlets/indexservlet.h>
#include <servlets/loginservlet.h>

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/Filters/server/"),
                                  new LoginFilter);

    server.addUrlServlet("/login", new LoginServlet);
    server.addUrlServlet("/index", new IndexServlet);

    return server.start();
}
