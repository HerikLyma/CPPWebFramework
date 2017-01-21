/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <servlets/usersservlet.h>
#include <cwf/cppwebapplication.h>

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/CSTLIfExample/server/"));

    server.addUrlServlet("/users", new UsersServlet);

    return server.start();
}
