/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>
#include <controllers/showfilecontroller.h>

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/ShowFile/server/");

    server.addUrlController<ShowFileController>("/showfile");

    return server.start();
}
