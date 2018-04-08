/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <controllers/indexcontroller.h>
#include <controllers/logincontroller.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/Sessions/server");

    server.addUrlController<LoginController>("/login");
    server.addUrlController<IndexController>("/index");

    return server.start();
}
