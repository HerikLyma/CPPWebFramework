/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <servlets/helloworldservlet.h>
#include "cwf/cppwebapplication.h"

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/HelloWorld/server"));



    server.addUrlServlet("/hello", new HelloWorldServlet);


    return server.start();
}
