/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>
#include <servlets/userservlet.h>
#include <servlets/homeservlet.h>


int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/CSTLImportExample/server/"));

    server.addUrlServlet("/user", new UserServlet);
    server.addUrlServlet("/home", new HomeServlet);

    return server.start();
}
